#ifndef XELABEVENT_HH
#define XELABEVENT_HH

#include <G4UserEventAction.hh>
#include <G4Event.hh>
#include <g4root.hh>

#include "XelabRun.hh"

class XelabEventAction : public G4UserEventAction
{
public:
  XelabEventAction(XelabRunAction *);
  ~XelabEventAction();

  virtual void BeginOfEventAction(const G4Event *);
  virtual void EndOfEventAction(const G4Event *);

  void AddEdep(G4double edep) { fEdep += edep; }

private:
  G4double fEdep;
};

#endif
