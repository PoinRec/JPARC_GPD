#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "Action.hh"

#include "QBBC.hh"

int main(int argc, char** argv) {
  G4RunManager *runManager = new G4RunManager();
  
  runManager->SetUserInitialization(new MyDetectorConstruction());

  G4VModularPhysicsList *physicsList = new QBBC;
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new MyActionInitialization());
  
  runManager->Initialize();

  runManager->BeamOn(10000);

  delete runManager;
  return 0;
}