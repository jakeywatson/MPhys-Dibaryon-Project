/// \file dibaryonModellerPrimaryGeneratorAction.cc
/// \brief Implementation of the dibaryonModellerPrimaryGeneratorAction class

#include "dibaryonModellerPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerPrimaryGeneratorAction::dibaryonModellerPrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction(),
	fParticleGun(0)
{
	G4int nofParticles = 1;
	fParticleGun = new G4ParticleGun(nofParticles);

	// default particle kinematic
	//
	G4ParticleDefinition* particleDefinition
		= G4ParticleTable::GetParticleTable()->FindParticle("gamma");
	fParticleGun->SetParticleDefinition(particleDefinition);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	fParticleGun->SetParticleEnergy(570.*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerPrimaryGeneratorAction::~dibaryonModellerPrimaryGeneratorAction()
{
	delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// This function is called at the begining of event

	// In order to avoid dependence of PrimaryGeneratorAction
	// on DetectorConstruction class we get world volume
	// from G4LogicalVolumeStore
	//
	G4double worldZHalfLength = 0;
	G4LogicalVolume* worlLV
		= G4LogicalVolumeStore::GetInstance()->GetVolume("World");
	G4Box* worldBox = 0;
	if (worlLV) worldBox = dynamic_cast< G4Box*>(worlLV->GetSolid());
	if (worldBox) {
		worldZHalfLength = worldBox->GetZHalfLength();
	}
	else {
		G4ExceptionDescription msg;
		msg << "World volume of box not found." << G4endl;
		msg << "Perhaps you have changed geometry." << G4endl;
		msg << "The gun will be place in the center.";
		G4Exception("dibaryonModellerPrimaryGeneratorAction::GeneratePrimaries()",
			"MyCode0002", JustWarning, msg);
	}

	// Set gun position
	fParticleGun
		->SetParticlePosition(G4ThreeVector(0., 0., -worldZHalfLength));

	fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

