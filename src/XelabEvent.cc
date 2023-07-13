// =============================================================================
//  Title: XelabEvent.cc
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#include "XelabEvent.hh"

XelabEventAction::XelabEventAction(XelabRunAction *)
{
  fEdep = 0.;
};

XelabEventAction::~XelabEventAction(){};

void XelabEventAction::BeginOfEventAction(const G4Event *)
{
  fEdep = 0.;
}

void XelabEventAction::EndOfEventAction(const G4Event *)
{
  G4cout << "Energy deposition: " << fEdep << G4endl;

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(2, 0, fEdep);
  man->AddNtupleRow(2);
}
