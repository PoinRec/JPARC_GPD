#include "Detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name): G4VSensitiveDetector(name) {
  // Determine ntuple ID based on detector name
  if (name == "FT1") {
    fNtupleID = 0;
  } else if (name == "FT2") {
    fNtupleID = 1;
  } else if (name == "DC1") {
    fNtupleID = 2;
  } else if (name == "DC2") {
    fNtupleID = 3;
  } else if (name == "RICH") {
    fNtupleID = 4;
  } else {
    fNtupleID = 0;  // Default to FT1
  }
}

MySensitiveDetector::~MySensitiveDetector() {
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
  G4AnalysisManager *manager = G4AnalysisManager::Instance();
  G4Track *track = aStep->GetTrack();

  G4ParticleDefinition *particle = track->GetDefinition();
  G4int pdgCode = particle->GetPDGEncoding();
  G4int trackID = track->GetTrackID();
  G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  
  // Only record the situation where the primary particles (ParentID == 0) enter the detector boundary for the first time.
  auto pre = aStep->GetPreStepPoint();
  if (track->GetParentID() == 0 && 
      pdgCode < 10000 && pdgCode > -10000 &&
      pre->GetStepStatus() == fGeomBoundary) {
    // Fill the appropriate ntuple based on detector ID
    manager->FillNtupleIColumn(fNtupleID, 0, eventID);
    manager->FillNtupleIColumn(fNtupleID, 1, pdgCode);
    manager->FillNtupleIColumn(fNtupleID, 2, trackID);
    // position at the entrance (mm)
    const auto &pos = pre->GetPosition();
    manager->FillNtupleDColumn(fNtupleID, 3, pos.x());
    manager->FillNtupleDColumn(fNtupleID, 4, pos.y());
    manager->FillNtupleDColumn(fNtupleID, 5, pos.z());
    // momentum at the entrance (convert MeV->GeV)
    const auto &p = track->GetMomentum();
    const double MeV_to_GeV = 1.0e-3;
    manager->FillNtupleDColumn(fNtupleID, 6, p.x() * MeV_to_GeV);
    manager->FillNtupleDColumn(fNtupleID, 7, p.y() * MeV_to_GeV);
    manager->FillNtupleDColumn(fNtupleID, 8, p.z() * MeV_to_GeV);
    manager->AddNtupleRow(fNtupleID);
  }
  return true;
}
