#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"

#include "Run.hh"

class MySensitiveDetector : public G4VSensitiveDetector {
  public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
  private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    G4int fNtupleID;  // Ntuple IDs: 0-FT1, 1-FT2, 2-DC1, 3-DC2, 4-RICH
};

#endif