#ifndef XELABRUN_HH
#define XELABRUN_HH

#include <G4UserRunAction.hh>
#include <G4Run.hh>
#include <g4root.hh>

class XelabRunAction : public G4UserRunAction
{
public:
  XelabRunAction();
  ~XelabRunAction();

  virtual void BeginOfRunAction(const G4Run *);
  virtual void EndOfRunAction(const G4Run *);
};

#endif
