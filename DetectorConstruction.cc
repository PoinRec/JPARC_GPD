#include "DetectorConstruction.hh"

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
  G4double FT1_size_Y = 670.0 * mm;

  G4double Detector_size_Z = 20.0 * mm;

  auto solidDetector = new G4Box("Detector", 0.5 * FT1_size_X, 0.5 * FT1_size_Y, 0.5 * Detector_size_Z);
  logicDetector = new G4LogicalVolume(solidDetector, detector_mat, "Detector");
  auto physDetector = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -9.0 * m), logicDetector, "Detector", logicWorld, false, 0, true);

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  logicDetector->SetSensitiveDetector(sensDet);
}