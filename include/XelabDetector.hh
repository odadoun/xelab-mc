#ifndef XELABDETECTOR_HH
#define XELABDETECTOR_HH

#include <G4VSensitiveDetector.hh>
#include <G4RunManager.hh>
#include <g4root.hh>
#include <G4SystemOfUnits.hh>

class XelabSensitiveDetector : public G4VSensitiveDetector
{
public:
  XelabSensitiveDetector(G4String);
  ~XelabSensitiveDetector();

private:
  virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
