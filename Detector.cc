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
  if (pdgCode < 10000) {
  manager->FillNtupleIColumn(0, eventID);
  manager->FillNtupleIColumn(1, pdgCode);
  manager->FillNtupleIColumn(2, trackID);
  manager->AddNtupleRow();
  }
  return true;
}
