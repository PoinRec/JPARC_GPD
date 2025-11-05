#include "Generator.hh"

MyGenerator::MyGenerator() {
  fParticleGun = new G4ParticleGun(1);
}

MyGenerator::~MyGenerator() {
  delete fParticleGun;
}

void MyGenerator::GeneratePrimaries(G4Event * anEvent) {
  auto particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -9.5 * m));
  fParticleGun->SetParticleEnergy(20.0 * GeV);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
