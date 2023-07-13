// =============================================================================
//  Title: XelabGenerator.hh
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#ifndef XELABGENERATOR_HH
#define XELABGENERATOR_HH

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleTable.hh>
#include <G4IonTable.hh>
#include <G4Geantino.hh>

class XelabPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  XelabPrimaryGenerator();
  ~XelabPrimaryGenerator();

  virtual void GeneratePrimaries(G4Event *);

private:
  G4ParticleGun *fParticleGun;
};

#endif
