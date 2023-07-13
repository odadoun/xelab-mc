// =============================================================================
//  Title: XelabGenerator.cc
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#include "XelabGenerator.hh"

XelabPrimaryGenerator::XelabPrimaryGenerator()
{
  // 1 primary particle per event here
  fParticleGun = new G4ParticleGun(1);

  // Particle settings
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
  fParticleGun->SetParticleDefinition(particle);

  // Particle generated in the centre (0, 0, 0)
  G4ThreeVector pos(0., 0., 0.);
  fParticleGun->SetParticlePosition(pos);

  // Particle generated with a momentum in the z direction
  G4ThreeVector mom(0., 0., 1.);
  fParticleGun->SetParticleMomentumDirection(mom);

  // Particle generated with a momentum of 100 GeV
  fParticleGun->SetParticleMomentum(0. * GeV);
};

XelabPrimaryGenerator::~XelabPrimaryGenerator()
{
  delete fParticleGun;
};

void XelabPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
  if (particle == G4Geantino::Geantino())
  {
    // Cobalt-60 source
    G4int Z = 27;
    G4int A = 60;
    G4double charge = 0. * eplus;
    G4double energy = 0. * keV;
    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
  }
  fParticleGun->GeneratePrimaryVertex(anEvent);
};
