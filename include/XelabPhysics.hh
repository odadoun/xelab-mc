// =============================================================================
//  Title: XelabPhysics.hh
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#ifndef XELABPHYSICS_HH
#define XELABPHYSICS_HH

#include <G4DecayPhysics.hh>
#include <G4EmStandardPhysics.hh>
#include <G4OpticalPhysics.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4VModularPhysicsList.hh>

class XelabPhysicsList : public G4VModularPhysicsList
{
public:
  XelabPhysicsList();
  ~XelabPhysicsList();
};

#endif
