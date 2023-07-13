// =============================================================================
//  Title: XelabPhysics.cc
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#include "XelabPhysics.hh"

XelabPhysicsList::XelabPhysicsList()
{
  // Electromagnetic interactions
  RegisterPhysics(new G4EmStandardPhysics());

  // Optical photons
  RegisterPhysics(new G4OpticalPhysics());

  // Decay particles
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive (ions) decay particles
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

XelabPhysicsList::~XelabPhysicsList() {}
