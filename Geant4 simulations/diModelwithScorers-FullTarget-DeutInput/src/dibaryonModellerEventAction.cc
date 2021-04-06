// \file dibaryonModellerEventAction.cc
// \brief Implementation of the dibaryonModellerEventAction class

#include "dibaryonModellerEventAction.hh"
#include "dibaryonModellerAnalysis.hh"
#include "dibaryonModellerDetectorConstruction.hh"
#include "dibaryonModellerPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include <map>
#include "Randomize.hh"
#include <iomanip>

#define pi 3.14159265359

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerEventAction::dibaryonModellerEventAction(dibaryonModellerPrimaryGeneratorAction* kin)
 : G4UserEventAction(),
   fSciEdepHCID(-1),
   fPri(kin)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerEventAction::~dibaryonModellerEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>* 
dibaryonModellerEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  G4THitsMap<G4double>* hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("dibaryonModellerEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double dibaryonModellerEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4int sumValue = 0;
  std::map<G4int, G4double*>::iterator it;
  for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
    sumValue += *(it->second);
  }
  return sumValue;  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerEventAction::EndOfEventAction(const G4Event* event)
{  
	//Get primary vertex position
	G4double z_pos = event->GetPrimaryVertex()->GetZ0() / mm;

	//Find target/deuterium/scintillator thicknesses
	G4double targetZHalfLength = 0;
	G4LogicalVolume* targetLV
		= G4LogicalVolumeStore::GetInstance()->GetVolume("Target");
	G4Tubs* Target = 0;
	if (targetLV) Target = dynamic_cast<G4Tubs*>(targetLV->GetSolid());
	if (Target) {
		targetZHalfLength = Target->GetZHalfLength();
	}

	G4double scintillatorThickness = 0;
	G4double deutThickness = 0;

	G4LogicalVolume* deutLV
		= G4LogicalVolumeStore::GetInstance()->GetVolume("deutLV");
	G4Tubs* deutTube = 0;
	if (deutLV) deutTube = dynamic_cast< G4Tubs*>(deutLV->GetSolid());
	if (deutTube) {
		deutThickness = 2 * (deutTube->GetZHalfLength());
	}

	G4LogicalVolume* sciLV
		= G4LogicalVolumeStore::GetInstance()->GetVolume("sciLV");
	G4Tubs* scintillatorTube = 0;
	if (sciLV) scintillatorTube = dynamic_cast< G4Tubs*>(sciLV->GetSolid());
	if (scintillatorTube) {
		scintillatorThickness = 2 * (scintillatorTube->GetZHalfLength());
	}

   // Get hist collections IDs
  if ( fSciEdepHCID < 0 ) {
	fSciEdepHCID
		= G4SDManager::GetSDMpointer()->GetCollectionID("sciSD/Edep");
  }

  // Get array of layer energy deposits
  //
  G4THitsMap<G4double>* sciEdep = GetHitsCollection(fSciEdepHCID, event);

  // get analysis manager
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // fill ntuples
  //  
  G4ThreeVector inc = fPri->GetParticleGun()->GetParticleMomentumDirection();
  G4double dot_product = inc.z();
  G4double inc_mag = std::sqrt(inc.x()*inc.x() + inc.y()*inc.y() + inc.z()*inc.z());
  G4double angle = std::acos(dot_product / inc_mag);

  G4double incident_angle = (180.0 / pi)*(angle);
  analysisManager->FillNtupleDColumn(0, incident_angle);

  G4double incident_energy = fPri->GetParticleGun()->GetParticleEnergy();
  analysisManager->FillNtupleDColumn(1, incident_energy);

  G4double layer_of_production = (z_pos + targetZHalfLength + (0.5*deutThickness)) / (deutThickness + scintillatorThickness);
  int layer_number = (int)(layer_of_production + 0.5);
  analysisManager->FillNtupleDColumn(2, layer_number);

  std::map<G4int, G4double*>::iterator itS;

  for (itS = sciEdep->GetMap()->begin(); itS != sciEdep->GetMap()->end(); itS++) {
	  G4int layer_number = (itS->first);
	  G4double energy_deposited = (*(itS->second))/MeV;
	  analysisManager->FillNtupleDColumn((layer_number+3), energy_deposited);
	}

  analysisManager->AddNtupleRow(); 

  //print per event (modulo n)  
  //
  G4int eventID = event->GetEventID();
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
