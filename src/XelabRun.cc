#include "XelabRun.hh"

XelabRunAction::XelabRunAction()
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  // Creating a ROOT Ntuple to store true information
  man->CreateNtuple("Photons", "Photons");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");
  man->CreateNtupleDColumn("fT");
  man->FinishNtuple(0); // 1st Ntuple (index 0)

  // Creating a ROOT Ntuple to store measured/reconstructed information
  man->CreateNtuple("Hits", "Hits");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");
  man->FinishNtuple(1); // 2nd Ntuple (index 1)

  // Creating a ROOT Ntuple to store deposited energy
  man->CreateNtupleDColumn("fEdep");
  man->FinishNtuple(2); // 3rd Ntuple (index 2)
};

XelabRunAction::~XelabRunAction(){};

void XelabRunAction::BeginOfRunAction(const G4Run *run)
{
  G4int runID = run->GetRunID();
  std::stringstream strRunID;
  strRunID << runID;

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->OpenFile("output" + strRunID.str() + ".root");
};

void XelabRunAction::EndOfRunAction(const G4Run *)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile("output.root");
};
