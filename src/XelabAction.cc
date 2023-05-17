#include "XelabAction.hh"

XelabActionInitialization::XelabActionInitialization(){};

XelabActionInitialization::~XelabActionInitialization(){};

void XelabActionInitialization::BuildForMaster() const
{
  XelabRunAction *runAction = new XelabRunAction();
  SetUserAction(runAction);
};

void XelabActionInitialization::Build() const
{
  XelabPrimaryGenerator *generator = new XelabPrimaryGenerator();
  SetUserAction(generator);

  // XelabRunAction *runAction = new XelabRunAction();
  // SetUserAction(runAction);
  //
  // XelabEventAction *eventAction = new XelabEventAction(runAction);
  // SetUserAction(eventAction);

  // XelabSteppingAction *steppingAction = new XelabSteppingAction(eventAction);
  // SetUserAction(steppingAction);
};
