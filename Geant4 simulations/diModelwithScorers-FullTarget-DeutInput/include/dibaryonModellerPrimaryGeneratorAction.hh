/// \file dibaryonModellerPrimaryGeneratorAction.hh
/// \brief Definition of the dibaryonModellerPrimaryGeneratorAction class

#ifndef dibaryonModellerPrimaryGeneratorAction_h
#define dibaryonModellerPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gun.

class dibaryonModellerPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    dibaryonModellerPrimaryGeneratorAction();    
    virtual ~dibaryonModellerPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
