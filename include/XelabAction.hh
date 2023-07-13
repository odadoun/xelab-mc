// =============================================================================
//  Title: XelabAction.hh
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#ifndef XELABACTION_HH
#define XELABACTION_HH

#include <G4VUserActionInitialization.hh>

#include "XelabGenerator.hh"
#include "XelabRun.hh"
#include "XelabEvent.hh"
// #include "XelabStepping.hh"

class XelabActionInitialization : public G4VUserActionInitialization
{
public:
  XelabActionInitialization();
  ~XelabActionInitialization();

  virtual void Build() const;
  virtual void BuildForMaster() const;
};

#endif
