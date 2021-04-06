/// \file dibaryonModellerRunAction.hh
/// \brief Definition of the dibaryonModellerRunAction class

#ifndef dibaryonModellerRunAction_h
#define dibaryonModellerRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Parameter.hh"
#include "globals.hh"

/// Run action class
class dibaryonModellerDetectorConstruction;

class dibaryonModellerRunAction : public G4UserRunAction
{
  public:
    dibaryonModellerRunAction(dibaryonModellerDetectorConstruction*);
    virtual ~dibaryonModellerRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
	  dibaryonModellerDetectorConstruction* fDet;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

