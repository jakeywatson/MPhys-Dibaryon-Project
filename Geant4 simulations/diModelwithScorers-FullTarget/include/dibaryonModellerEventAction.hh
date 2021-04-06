/// \file dibaryonModellerEventAction.hh
/// \brief Definition of the dibaryonModellerEventAction class

#ifndef dibaryonModellerEventAction_h
#define dibaryonModellerEventAction_h 1

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "globals.hh"

/// Event action class
///
/// In EndOfEventAction(), it stores the accumulated quantities of the energy 
/// deposited in each layer in the hit collections
class dibaryonModellerPrimaryGeneratorAction;

class dibaryonModellerEventAction : public G4UserEventAction
{
public:
  dibaryonModellerEventAction(dibaryonModellerPrimaryGeneratorAction*);
  virtual ~dibaryonModellerEventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
    
private:
  // methods
  G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                          const G4Event* event) const;
  G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
  
  // data members                   
  G4int	 fSciEdepHCID;

  dibaryonModellerPrimaryGeneratorAction* fPri;

};
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
