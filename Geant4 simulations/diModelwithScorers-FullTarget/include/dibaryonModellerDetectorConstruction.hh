/// \file dibaryonModellerDetectorConstruction.hh
/// \brief Definition of the dibaryonModellerDetectorConstruction class

#ifndef dibaryonModellerDetectorConstruction_h
#define dibaryonModellerDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.
///
/// Crystals are positioned in Ring, with an appropriate rotation matrix. 
/// Several copies of Ring are placed in the full detector.

class dibaryonModellerDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    dibaryonModellerDetectorConstruction();
    virtual ~dibaryonModellerDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();

  private:

    void DefineMaterials();
	G4VPhysicalVolume* DefineVolumes();

    G4bool  fCheckOverlaps;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

