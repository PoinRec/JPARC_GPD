#include "DetectorConstruction.hh"
#include "Detector.hh"

MyDetectorConstruction::MyDetectorConstruction() {
}

MyDetectorConstruction::~MyDetectorConstruction() {
}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
  G4NistManager *nist = G4NistManager::Instance();

  G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4double world_size_X = 5.0 * m;
  G4double world_size_Y = 5.0 * m;
  G4double world_size_Z = 20.0 * m;

  auto solidWorld = new G4Box("World", 0.5 * world_size_X, 0.5 * world_size_Y, 0.5 * world_size_Z);
  auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, true);

  G4Material *detector_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4double FT1_size_X = 640.0 * mm;
  G4double FT1_size_Y = 670 * mm;

  G4double Detector_size_Z = 20 * mm;

  auto solidDetector_FT1 = new G4Box("FT1_Detector", 0.5 * FT1_size_X, 0.5 * FT1_size_Y, 0.5 * Detector_size_Z);
  logicDetector = new G4LogicalVolume(solidDetector_FT1, detector_mat, "FT1_Detector");
  auto physDetector = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -9.5 * m), logicDetector, "FT1_Detector", logicWorld, false, 0, true);

  MySensitiveDetector *senstiveDetector_FT1 = new MySensitiveDetector("SensitiveDetector");
  logicDetector->SetSensitiveDetector(senstiveDetector_FT1);

  return physWorld;
}