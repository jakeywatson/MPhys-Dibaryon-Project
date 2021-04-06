/// \file dibaryonModellerActionInitialization.hh
/// \brief Definition of the dibaryonModellerActionInitialization class

#ifndef dibaryonModellerActionInitialization_h
#define dibaryonModellerActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class dibaryonModellerDetectorConstruction;

/// Action initialization class.
///

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class dibaryonModellerActionInitialization : public G4VUserActionInitialization
{
  public:
    dibaryonModellerActionInitialization(dibaryonModellerDetectorConstruction*);
    virtual ~dibaryonModellerActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

private:
	dibaryonModellerDetectorConstruction* fDetConstruction;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
