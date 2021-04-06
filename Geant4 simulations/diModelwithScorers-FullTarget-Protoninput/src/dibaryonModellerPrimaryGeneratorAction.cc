/// \file dibaryonModellerPrimaryGeneratorAction.cc
/// \brief Implementation of the dibaryonModellerPrimaryGeneratorAction class

#include "dibaryonModellerPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include <chrono>
#include <random>
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerPrimaryGeneratorAction::dibaryonModellerPrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction(),
	fParticleGun(0)
{
	G4int nofParticles = 1;
	fParticleGun = new G4ParticleGun(nofParticles);

	G4ParticleDefinition* particleDefinition
		= G4ParticleTable::GetParticleTable()->FindParticle("proton");
	fParticleGun->SetParticleDefinition(particleDefinition);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
	fParticleGun->SetParticleEnergy(100.0*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerPrimaryGeneratorAction::~dibaryonModellerPrimaryGeneratorAction()
{
	delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// This function is called at the beginning of event

	// In order to avoid dependence of PrimaryGeneratorAction
	// on DetectorConstruction class we get world volume
	// from G4LogicalVolumeStore
	//
	G4double targetZHalfLength = 0;
	G4LogicalVolume* targetLV
		= G4LogicalVolumeStore::GetInstance()->GetVolume("Target");
	G4Tubs* Target = 0;
	if (targetLV) Target = dynamic_cast<G4Tubs*>(targetLV->GetSolid());
	if (Target) {
		targetZHalfLength = Target->GetZHalfLength();
	}
	else {
		G4ExceptionDescription msg;
		msg << "World volume of box not found." << G4endl;
		msg << "Perhaps you have changed geometry." << G4endl;
		msg << "The gun will be place in the center.";
		G4Exception("dibaryonModellerPrimaryGeneratorAction::GeneratePrimaries()",
			"MyCode0002", JustWarning, msg);
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
		scintillatorThickness = 2*(scintillatorTube->GetZHalfLength());
	}

	G4double layerThickness = scintillatorThickness + deutThickness;

	// default particle kinematic
	//

	//Sample from uniform distribution, Mersenne Twister random 
	//engine, with seed being the high resolution system time.

	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	//Four different distributions:
	//flat_distribution: chooses scattering angle in radians for deuteron
	//layer_distribution: chooses layer of production for deuterons from uniform distribution
	//sqrt_distribution: chooses whether the sqrt of the determinant in the quadratic formula 
	//is positive or negative.
	//zerotoone: any real number between 0 and 1.

	std::uniform_real_distribution<double> flat_distribution(0.0, 0.4);
	std::uniform_real_distribution<double> zerototwopi(0, (2*3.14159265359));
	std::uniform_int_distribution<int> layer_distribution(1, 5);
	std::uniform_int_distribution<int> sqrt_distribution(0, 1);
	std::uniform_real_distribution<double> minusonetoone(-1.0, 1.0);
	std::uniform_real_distribution<double> probability(0.0, 1.0);

	int test_pos_neg_sqrt = sqrt_distribution(generator);
	double test_scattering_angle = flat_distribution(generator);
	int layer_of_production = layer_distribution(generator);

	double c = 299792458;
	double proton_mass = 938.272046;			//MeV/C^2

	double x;
	double x_increment = 0.4 / 4000;
	double CDF;

	double test_probability = probability(generator);
	x = 0;
	CDF = ((-(x*x*x) - 0.0348397*x) / ((x*x*x*x) + 0.0696794*(x*x) + 0.000140565) - 6.01335*atan(3.84615*x) + 12.3568*atan(21.9298*x)) / 10.0;

	for (int i = 0; i < 4000; i++) {
		if (CDF <= test_probability && test_probability <= (((-((x + x_increment)*(x + x_increment)*(x + x_increment)) - 0.0348397*(x + x_increment)) / (((x + x_increment)*(x + x_increment)*(x + x_increment)*(x + x_increment)) + 0.0696794*((x + x_increment)*(x + x_increment)) + 0.000140565) - 6.01335*atan(3.84615*(x + x_increment)) + 12.3568*atan(21.9298*(x + x_increment))) / 10.0)) {
			break;
		}
		x = x + x_increment;
		CDF = ((-(x*x*x) - 0.0348397*x) / ((x*x*x*x) + 0.0696794*(x*x) + 0.000140565) - 6.01335*atan(3.84615*x) + 12.3568*atan(21.9298*x)) / 10.0;
	}

	G4double proton_momentum = x * 1000;						//Quasi-Free formula is in GeV so I need in MeVs
	G4double proton_energy = sqrt(proton_momentum*proton_momentum + proton_mass*proton_mass) - proton_mass;

	double test_for_theta = minusonetoone(generator);
	double theta = acos((-1)*test_for_theta);
	double phi = zerototwopi(generator);

	G4double zcomponent = cos(theta);
	G4double ycomponent = sin(phi)*sin(theta);
	G4double xcomponent = sin(theta)*cos(phi);

	G4double gun_z = -targetZHalfLength + ((layer_of_production - 0.5)*deutThickness + (layer_of_production)*scintillatorThickness);

	// Set gun position
	fParticleGun
		->SetParticlePosition(G4ThreeVector(0., 0., gun_z));
	fParticleGun
		->SetParticleMomentumDirection(G4ThreeVector(xcomponent, ycomponent, zcomponent));
	fParticleGun
		->SetParticleEnergy(proton_energy*MeV);
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

