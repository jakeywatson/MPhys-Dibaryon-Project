/// \file dibaryonModellerActionInitialization.cc
/// \brief Implementation of the dibaryonModellerActionInitialization class

#include "dibaryonModellerActionInitialization.hh"
#include "dibaryonModellerEventAction.hh"
#include "dibaryonModellerRunAction.hh"
#include "dibaryonModellerPrimaryGeneratorAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerActionInitialization::dibaryonModellerActionInitialization(dibaryonModellerDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
	fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

dibaryonModellerActionInitialization::~dibaryonModellerActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerActionInitialization::BuildForMaster() const
{
  SetUserAction(new dibaryonModellerRunAction(fDetConstruction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void dibaryonModellerActionInitialization::Build() const
{
	dibaryonModellerPrimaryGeneratorAction* kin = new dibaryonModellerPrimaryGeneratorAction();
	SetUserAction(kin);
	SetUserAction(new dibaryonModellerRunAction(fDetConstruction));
	SetUserAction(new dibaryonModellerEventAction(kin));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
