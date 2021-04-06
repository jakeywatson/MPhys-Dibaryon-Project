/// \file dibaryonModellerDetectorConstruction.cc
/// \brief Implementation of the dibaryonModellerDetectorConstruction class

#include "dibaryonModellerDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerDetectorConstruction::dibaryonModellerDetectorConstruction()
: G4VUserDetectorConstruction(),
 fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerDetectorConstruction::~dibaryonModellerDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* dibaryonModellerDetectorConstruction::Construct()
{
	// Define materials 
	DefineMaterials();

	// Define volumes
	return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerDetectorConstruction::DefineMaterials()
{
  G4NistManager* man = G4NistManager::Instance();

  G4double a;
  G4double z;
  G4double density;
  G4double weightRatio;
  G4String name;
  G4String symbol;
  G4int nElem;
  G4int iz, ia;
  G4Isotope* isotope;
  G4double RelativeAbundance;

  //Vacuum

  new G4Material("Galactic", z = 1., a = 1.01*g / mole, density = universe_mean_density,
	  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  //Plastic Scintillator
  G4Material* Vinyltoluene = man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

  //Deuterated Plastic

  // Carbon
  a = 12.01*g / mole;
  G4Element* elC = new G4Element(name = "Carbon", symbol = "C", z = 6., a);

  //Deuterium
  G4Element* elD = new G4Element(name = "Deuterium", symbol = "D", 1);
  isotope = new G4Isotope(name = "H2", iz = 1, ia = 2, a = 2.01410178*g / mole);
  RelativeAbundance = 1.0;
  elD->AddIsotope(isotope, RelativeAbundance);

  // CD2 target
  density = 1.105*g / cm3;
  G4Material* CD2 = new G4Material(name = "CD2", density, nElem = 2);
  CD2->AddElement(elC, weightRatio = 0.75);
  CD2->AddElement(elD, weightRatio = 0.25);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* dibaryonModellerDetectorConstruction::DefineVolumes() {
	// Geometry parameters

	G4int nOfComLayers = 5;
	G4int nOfBackLayers = 4;

	G4int nOfScintillatorLayers = nOfComLayers + nOfBackLayers + 1;

	G4double deuThickness = 1.*mm;
	G4double sciThickness = 4.*mm;
	G4double innerRadius = 0.*cm;
	G4double outerRadius = 2.*cm;
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;

	G4double targetThickness = ((deuThickness + sciThickness)*nOfComLayers) + ((nOfBackLayers + 1)*sciThickness);

	G4double worldSizeXY = 1.2 * (2*outerRadius);
	G4double worldSizeZ = 1.2 * targetThickness;

	// Get materials
	G4Material* scintillatorMaterial = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	G4Material* deuteratedMaterial = G4Material::GetMaterial("CD2");
	G4Material* defaultMaterial = G4Material::GetMaterial("Galactic");

	if (!defaultMaterial || !scintillatorMaterial) {
		G4ExceptionDescription msg;
		msg << "Cannot retrieve materials already defined.";
		G4Exception("B4DetectorConstruction::DefineVolumes()",
			"MyCode0001", FatalException, msg);
	}

	//     
	// World
	//
	G4VSolid* worldS
		= new G4Box("World",           // its name
			worldSizeXY, worldSizeXY, worldSizeZ); // its size

	G4LogicalVolume* worldLV
		= new G4LogicalVolume(
			worldS,           // its solid
			defaultMaterial,  // its material
			"World");         // its name

	G4VPhysicalVolume* worldPV
		= new G4PVPlacement(
			0,                // no rotation
			G4ThreeVector(),  // at (0,0,0)
			worldLV,          // its logical volume                         
			"World",          // its name
			0,                // its mother  volume
			false,            // no boolean operation
			0,                // copy number
			fCheckOverlaps);  // checking overlaps 

							  //                               
							  // Target
							  //  
	G4Tubs* targetS
		= new G4Tubs("Target",     // its name
			innerRadius, outerRadius, targetThickness/2, startAngle, spanningAngle); // its size

	G4LogicalVolume* targetLV
		= new G4LogicalVolume(
			targetS,     // its solid
			defaultMaterial,  // its material
			"Target");   // its name

	new G4PVPlacement(
		0,                // no rotation
		G4ThreeVector(),  // at (0,0,0)
		targetLV,          // its logical volume                         
		"Target",    // its name
		worldLV,          // its mother  volume
		false,            // no boolean operation
		0,                // copy number
		fCheckOverlaps);  // checking overlaps 

						  //                               
						  // Deuterated Layer
						  //  
	G4Tubs* deutS
		= new G4Tubs("Deuterated",     // its name
			innerRadius, outerRadius, deuThickness / 2, startAngle, spanningAngle); // its size

	G4LogicalVolume* deutLV
		= new G4LogicalVolume(
			deutS,     // its solid
			deuteratedMaterial,  // its material
			"deutLV");   // its name

						  //                               
						  // Scintillator Layer
						  //  
	G4Tubs* sciS
		= new G4Tubs("Scintillator",     // its name
			innerRadius, outerRadius, sciThickness / 2, startAngle, spanningAngle); // its size

	G4LogicalVolume* sciLV
		= new G4LogicalVolume(
			sciS,     // its solid
			scintillatorMaterial,  // its material
			"sciLV");   // its name

	//Placing layers of scintillator within deuterated volume

	G4ThreeVector deuteratedLayer(0, 0, deuThickness);
	G4ThreeVector sciLayer(0, 0, sciThickness);

	//Place first layer of scintillator

	new G4PVPlacement(
		0,
		G4ThreeVector(0, 0, (0.5*sciThickness) - (targetThickness*0.5)),
		sciLV,		//logical volume
		"Sci_Layer", //name
		targetLV, //mother volume
		false,
		0);
 
	for (int layerIdx = 1; layerIdx < nOfComLayers + 1 ; ++layerIdx)
	{
		G4ThreeVector positionD = (((layerIdx - 1) + 0.5)*deuteratedLayer) + ((layerIdx)*sciLayer);

		positionD = positionD - G4ThreeVector(
			0, 
			0, 
			targetThickness*0.5);//Position is w.r.t. center of mother volume: the targetLV

		new G4PVPlacement(
			0,
			positionD,
			deutLV,		//logical volume
			"Deut_Layer", //name
			targetLV, //mother volume
			false,
			layerIdx);

		G4ThreeVector positionS = ((layerIdx)*deuteratedLayer) + ((layerIdx + 0.5)*sciLayer);

		positionS = positionS - G4ThreeVector(
			0,
			0,
			targetThickness*0.5);//Position is w.r.t. center of mother volume: the targetLV

		new G4PVPlacement(
			0,
			positionS, 
			sciLV,		//logical volume
			"Sci_Layer", //name
			targetLV, //mother volume
			false, 
			layerIdx);
	}

	for (int layerIdx = nOfComLayers + 1; layerIdx < (nOfBackLayers + nOfComLayers + 1); ++layerIdx)
	{
		G4ThreeVector position = nOfComLayers*(sciLayer + deuteratedLayer) + sciLayer + (layerIdx - (nOfComLayers + 1) + 0.5)*sciLayer;

		position -= G4ThreeVector(
			0,
			0,
			targetThickness / 2);//Position is w.r.t. center of mother volume: the targetLV

		new G4PVPlacement(
			0,
			position,
			sciLV,		//logical volume
			"Sci_Layer", //name
			targetLV, //mother volume
			false,
			layerIdx);
	}



							  //
							  // print parameters
							  //
	G4cout
		<< G4endl
		<< "------------------------------------------------------------" << G4endl
		<< "---> The target is " << nOfComLayers << " layers of: [ "
		<< deuThickness / mm << "mm of " << deuteratedMaterial->GetName()
		<< " + "
		<< sciThickness / mm << "mm of " << scintillatorMaterial->GetName() << " ] " << G4endl
		<< "With " << nOfBackLayers / mm << "mm of" << scintillatorMaterial->GetName() 
		<< " at the back of the target + 1 layer of " << sciThickness / mm << "mm at the front." << G4endl
		<< "------------------------------------------------------------" << G4endl;

	//                                        
	// Visualization attributes
	//
	//worldLV->SetVisAttributes (G4VisAttributes::Invisible);

	G4VisAttributes* worldAttributes =
		new G4VisAttributes(G4Colour::White());
	worldAttributes->SetVisibility(false);
	worldLV->SetVisAttributes(worldAttributes);

	G4Colour red(1.0, 0.0, 0.0);
	G4Colour blue(0.0, 0.0, 1.0);
	G4Colour white(1.0, 1.0, 1.0);

	G4VisAttributes* targetVisAtt = new  G4VisAttributes(white);
	targetVisAtt->SetForceWireframe(false);
	targetLV->SetVisAttributes(targetVisAtt);

	G4VisAttributes* deutVisAtt = new  G4VisAttributes(red);
	deutVisAtt->SetForceSolid(true);
	deutLV->SetVisAttributes(deutVisAtt);

	G4VisAttributes* sciVisAtt = new G4VisAttributes(blue);
	sciVisAtt->SetForceSolid(true);
	sciLV->SetVisAttributes(sciVisAtt);


	//
	// Always return the physical World
	//
	return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerDetectorConstruction::ConstructSDandField()
{
	G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

	// declare scint as MultiFunctionalDetector scorer
	// 

	//Second argument of primitive is called the 'depth'. This denotes which volumes' 
	//copy number is used as the key of the G4THitsMap. As the deuterated and scintillator
	//volumes are defined uniquely to the Layer volume, which is replicated, then the copy number 
	//of the Layer volume must be used.

	G4MultiFunctionalDetector* sciDetector
		= new G4MultiFunctionalDetector("sciSD");

	G4VPrimitiveScorer* primitiveS;
	primitiveS = new G4PSEnergyDeposit("Edep");
	sciDetector->RegisterPrimitive(primitiveS);

	SetSensitiveDetector("sciLV", sciDetector);

	G4cout << "Finished defining SD" << G4endl;

}