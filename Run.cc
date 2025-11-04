#include "Run.hh"

MyRunAction::MyRunAction() {
}

MyRunAction::~MyRunAction() {
}

void MyRunAction::BeginOfRunAction(const G4Run *) {
  G4AnalysisManager *manager = G4AnalysisManager::Instance();
  manager->OpenFile("output.root");
  manager->CreateNtuple("ParticleData", "Track and Energy");
  manager->CreateNtupleIColumn("EventID");
  manager->CreateNtupleIColumn("PDGCode");
  manager->CreateNtupleIColumn("TrackID");
  manager->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run *) {
  G4AnalysisManager *manager = G4AnalysisManager::Instance();
  manager->Write();
  manager->CloseFile();
}