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

  const G4double FT_size_X = 640.0 * mm;
  const G4double FT_size_Y = 670.0 * mm;

  const G4double DC_size_XY = 1186.0 * mm;

  const G4double Detector_size_Z = 20.0 * mm;

  // FT detector
  auto solidFT1 = new G4Box("FT1", 0.5 * FT_size_X, 0.5 * FT_size_Y, 0.5 * Detector_size_Z);
  logicFT1 = new G4LogicalVolume(solidFT1, detector_mat, "FT1");
  auto physFT1 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -9.0 * m), logicFT1, "FT1", logicWorld, false, 0, true);

  auto solidFT2 = new G4Box("FT2", 0.5 * FT_size_X, 0.5 * FT_size_Y, 0.5 * Detector_size_Z);
  logicFT2 = new G4LogicalVolume(solidFT2, detector_mat, "FT2");
  auto physFT2 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -8.0 * m), logicFT2, "FT2", logicWorld, false, 0, true);

  
  // DC detector
  auto solidDC1 = new G4Box("DC1", 0.5 * DC_size_XY, 0.5 * DC_size_XY, 0.5 * Detector_size_Z);
  logicDC1 = new G4LogicalVolume(solidDC1, detector_mat, "DC1");
  auto physDC1 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -0.85 * m), logicDC1, "DC1", logicWorld, false, 0, true);

  auto solidDC2 = new G4Box("DC2", 0.5 * DC_size_XY, 0.5 * DC_size_XY, 0.5 * Detector_size_Z);
  logicDC2 = new G4LogicalVolume(solidDC2, detector_mat, "DC2");
  auto physDC2 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, 0.15 * m), logicDC2, "DC2", logicWorld, false, 0, true);

  // RICH detector
  auto solidRICH = new G4Box("RICH", 0.5 * DC_size_XY, 0.5 * DC_size_XY, 0.5 * Detector_size_Z);
  logicRICH = new G4LogicalVolume(solidRICH, detector_mat, "RICH");
  auto physRICH = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, 0.25 * m), logicRICH, "RICH", logicWorld, false, 0, true);

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
  MySensitiveDetector *sensFT1 = new MySensitiveDetector("FT1");
  logicFT1->SetSensitiveDetector(sensFT1);
  
  MySensitiveDetector *sensFT2 = new MySensitiveDetector("FT2");
  logicFT2->SetSensitiveDetector(sensFT2);

  MySensitiveDetector *sensDC1 = new MySensitiveDetector("DC1");
  logicDC1->SetSensitiveDetector(sensDC1);

  MySensitiveDetector *sensDC2 = new MySensitiveDetector("DC2");
  logicDC2->SetSensitiveDetector(sensDC2);

  MySensitiveDetector *sensRICH = new MySensitiveDetector("RICH");
  logicRICH->SetSensitiveDetector(sensRICH);
}