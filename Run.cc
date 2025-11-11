#include "Run.hh"

MyRunAction::MyRunAction() {
}

MyRunAction::~MyRunAction() {
}

void MyRunAction::BeginOfRunAction(const G4Run *) {
  G4AnalysisManager *manager = G4AnalysisManager::Instance();
  manager->OpenFile("output_JAM2.root");
  manager->CreateNtuple("ParticleData", "Track and Energy");
  manager->CreateNtupleIColumn("EventID");
  manager->CreateNtupleIColumn("PDGCode");
  manager->CreateNtupleIColumn("TrackID");
  // Position at sensitive detector entrance (mm)
  manager->CreateNtupleDColumn("x_mm");
  manager->CreateNtupleDColumn("y_mm");
  manager->CreateNtupleDColumn("z_mm");
  // Momentum at sensitive detector entrance (GeV/c)
  manager->CreateNtupleDColumn("px_GeV");
  manager->CreateNtupleDColumn("py_GeV");
  manager->CreateNtupleDColumn("pz_GeV");
  manager->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run *) {
  G4AnalysisManager *manager = G4AnalysisManager::Instance();
  manager->Write();
  manager->CloseFile();
}