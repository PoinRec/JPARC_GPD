#include "DetectorConstruction.hh"

#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "E16ANA_MagneticFieldMap.hh"

#include <memory>
#include <string>

// Define a small class in an anonymous namespace to avoid header file declaration
namespace {
  class E16FieldAdapter : public G4MagneticField {
  public:
    explicit E16FieldAdapter(const std::string &binaryPath) {
      fMap = std::make_unique<E16ANA_MagneticFieldMap3D>(binaryPath);
      fMap->Initialize_binary();
      E16ANA_MagneticFieldMap::SetGlobalPointer(fMap.get());
    }

    void GetFieldValue(const G4double point[4], G4double * Bfield) const override {
      static bool magnetic_field_flag = true;

      if (!magnetic_field_flag) {
        Bfield[0] = Bfield[1] = Bfield[2] = 0.;
        return;
      }

      double G4_pos[3] = {point[0], point[1], point[2]};  // Geant4 unit is mm

      double E16_pos[3];
      E16_pos[0] = G4_pos[0];
      E16_pos[1] = G4_pos[1];
      E16_pos[2] = G4_pos[2] + 5900 * mm;

      double B_T[3] = {0., 0., 0.};
      bool ok = fMap->GetFieldValue_Tesla(E16_pos, B_T, 0);   // Unit is Tesla
      if (!ok) {
        Bfield[0] = Bfield[1] = Bfield[2] = 0.;
        return;
      }

      Bfield[0] = tesla * B_T[0];
      Bfield[1] = tesla * B_T[1];
      Bfield[2] = tesla * B_T[2];
    }

  private:
    std::unique_ptr<E16ANA_MagneticFieldMap3D> fMap;
  };
}


MyDetectorConstruction::MyDetectorConstruction()
  : logicFT1(nullptr),
    logicFT2(nullptr),
    logicDC1(nullptr),
    logicDC2(nullptr),
    logicRICH(nullptr),
    logicMagRegion(nullptr),
    fMagRegionField(nullptr),
    fMagRegionFieldManager(nullptr) {
}

MyDetectorConstruction::~MyDetectorConstruction() = default;

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
  G4NistManager *nist = G4NistManager::Instance();

  G4Material *air_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4double world_size_X = 5.0 * m;
  G4double world_size_Y = 5.0 * m;
  G4double world_size_Z = 20.0 * m;

  auto solidWorld = new G4Box("World", 0.5 * world_size_X, 0.5 * world_size_Y, 0.5 * world_size_Z);
  auto logicWorld = new G4LogicalVolume(solidWorld, air_mat, "World");
  auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, true);

  const G4double FT_size_X = 640.0 * mm;
  const G4double FT_size_Y = 670.0 * mm;

  const G4double DC_size_XY = 4000.0 * mm;

  const G4double Detector_size_Z = 20.0 * mm;

  // FT detector
  auto solidFT1 = new G4Box("FT1", 0.5 * FT_size_X, 0.5 * FT_size_Y, 0.5 * Detector_size_Z);
  logicFT1 = new G4LogicalVolume(solidFT1, air_mat, "FT1");
  auto physFT1 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -9.0 * m), logicFT1, "FT1", logicWorld, false, 0, true);

  auto solidFT2 = new G4Box("FT2", 0.5 * FT_size_X, 0.5 * FT_size_Y, 0.5 * Detector_size_Z);
  logicFT2 = new G4LogicalVolume(solidFT2, air_mat, "FT2");
  auto physFT2 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -8.0 * m), logicFT2, "FT2", logicWorld, false, 0, true);

  
  // DC detector
  auto solidDC1 = new G4Box("DC1", 0.5 * DC_size_XY, 0.5 * DC_size_XY, 0.5 * Detector_size_Z);
  logicDC1 = new G4LogicalVolume(solidDC1, air_mat, "DC1");
  auto physDC1 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -0.85 * m), logicDC1, "DC1", logicWorld, false, 0, true);

  auto solidDC2 = new G4Box("DC2", 0.5 * DC_size_XY, 0.5 * DC_size_XY, 0.5 * Detector_size_Z);
  logicDC2 = new G4LogicalVolume(solidDC2, air_mat, "DC2");
  auto physDC2 = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, 0.15 * m), logicDC2, "DC2", logicWorld, false, 0, true);

  // RICH detector
  auto solidRICH = new G4Box("RICH", 0.5 * DC_size_XY, 0.5 * DC_size_XY, 0.5 * Detector_size_Z);
  logicRICH = new G4LogicalVolume(solidRICH, air_mat, "RICH");
  auto physRICH = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, 0.25 * m), logicRICH, "RICH", logicWorld, false, 0, true);

  // E16 MagRegion Volume
  const G4double MagRegion_size_X = 3.95 * m;
  const G4double MagRegion_size_Y = 3.45 * m;
  const G4double MagRegion_size_Z = 6.95 * m;
  
  auto solidMagRegion = new G4Box("MagRegion", 0.5 * MagRegion_size_X, 0.5 * MagRegion_size_Y, 0.5 * MagRegion_size_Z);
  logicMagRegion = new G4LogicalVolume(solidMagRegion, air_mat, "MagRegion");
  new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, -4.425 * m), logicMagRegion, "MagRegion", logicWorld, false, 0, true);
                  
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

  if (!fMagRegionFieldManager && logicMagRegion) {
    auto field = std::make_unique<E16FieldAdapter>("/home/zhihao/JPARC_E16_GPD/project/Bmap-SKS-block-far-191218-2450A-rev1.binary");
    auto fm = new G4FieldManager();
    fm->SetDetectorField(field.get());
    fm->CreateChordFinder(field.get());
    logicMagRegion->SetFieldManager(fm, true);

    fMagRegionField = std::move(field);
    fMagRegionFieldManager = fm;
  }
}