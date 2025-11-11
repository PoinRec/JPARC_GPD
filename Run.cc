#include "Run.hh"

MyRunAction::MyRunAction() {
}

MyRunAction::~MyRunAction() {
}

void MyRunAction::BeginOfRunAction(const G4Run *) {
  G4AnalysisManager *manager = G4AnalysisManager::Instance();
  manager->OpenFile("output_JAM2.root");
  
  // FT1 ntuple
  manager->CreateNtuple("FT1", "FT1 Track and Energy");
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
  
  // FT2 ntuple
  manager->CreateNtuple("FT2", "FT2 Track and Energy");
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

  // DC1 ntuple
  manager->CreateNtuple("DC1", "DC1 Track and Energy");
  manager->CreateNtupleIColumn("EventID");
  manager->CreateNtupleIColumn("PDGCode");
  manager->CreateNtupleIColumn("TrackID");
  manager->CreateNtupleDColumn("x_mm");
  manager->CreateNtupleDColumn("y_mm");
  manager->CreateNtupleDColumn("z_mm");
  manager->CreateNtupleDColumn("px_GeV");
  manager->CreateNtupleDColumn("py_GeV");
  manager->CreateNtupleDColumn("pz_GeV");
  manager->FinishNtuple();

  // DC2 ntuple
  manager->CreateNtuple("DC2", "DC2 Track and Energy");
  manager->CreateNtupleIColumn("EventID");
  manager->CreateNtupleIColumn("PDGCode");
  manager->CreateNtupleIColumn("TrackID");
  manager->CreateNtupleDColumn("x_mm");
  manager->CreateNtupleDColumn("y_mm");
  manager->CreateNtupleDColumn("z_mm");
  manager->CreateNtupleDColumn("px_GeV");
  manager->CreateNtupleDColumn("py_GeV");
  manager->CreateNtupleDColumn("pz_GeV");
  manager->FinishNtuple();

  // RICH ntuple
  manager->CreateNtuple("RICH", "RICH Track and Energy");
  manager->CreateNtupleIColumn("EventID");
  manager->CreateNtupleIColumn("PDGCode");
  manager->CreateNtupleIColumn("TrackID");
  manager->CreateNtupleDColumn("x_mm");
  manager->CreateNtupleDColumn("y_mm");
  manager->CreateNtupleDColumn("z_mm");
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