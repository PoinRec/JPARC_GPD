#include "Detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name): G4VSensitiveDetector(name) {
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
    manager->FillNtupleIColumn(0, eventID);
    manager->FillNtupleIColumn(1, pdgCode);
    manager->FillNtupleIColumn(2, trackID);
    // position at the entrance (mm)
    const auto &pos = pre->GetPosition();
    manager->FillNtupleDColumn(3, pos.x());
    manager->FillNtupleDColumn(4, pos.y());
    manager->FillNtupleDColumn(5, pos.z());
    // momentum at the entrance (convert MeV->GeV)
    const auto &p = track->GetMomentum();
    const double MeV_to_GeV = 1.0e-3;
    manager->FillNtupleDColumn(6, p.x() * MeV_to_GeV);
    manager->FillNtupleDColumn(7, p.y() * MeV_to_GeV);
    manager->FillNtupleDColumn(8, p.z() * MeV_to_GeV);
    manager->AddNtupleRow();
  }
  return true;
}
