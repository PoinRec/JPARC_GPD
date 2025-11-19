#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"

#include "Detector.hh"

#include <memory>

class G4MagneticField;
class G4FieldManager;

class MyDetectorConstruction: public G4VUserDetectorConstruction {
  public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

  private:
    G4LogicalVolume *logicFT1;
    G4LogicalVolume *logicFT2;
    G4LogicalVolume *logicDC1;
    G4LogicalVolume *logicDC2;
    G4LogicalVolume *logicRICH;
    G4LogicalVolume *logicMagRegion;

    std::unique_ptr<G4MagneticField> fMagRegionField;
    G4FieldManager *fMagRegionFieldManager;

    virtual void ConstructSDandField();
};

#endif