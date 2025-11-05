#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"

class MyGenerator : public G4VUserPrimaryGeneratorAction {
  public:
    MyGenerator();
    ~MyGenerator();

    virtual void GeneratePrimaries(G4Event*);
  private:
    G4ParticleGun *fParticleGun;
};

#endif