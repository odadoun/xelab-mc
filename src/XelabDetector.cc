// =============================================================================
//  Title: XelabDetector.cc
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#include "XelabDetector.hh"

XelabSensitiveDetector::XelabSensitiveDetector(G4String name) : G4VSensitiveDetector(name){};

XelabSensitiveDetector::~XelabSensitiveDetector(){};

G4bool XelabSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  // Get tracks entering the sensitive volume
  G4Track *track = aStep->GetTrack();

  // Kill tracks once they enter the detector
  // track->SetTrackStatus(fStopAndKill);

  // ---------------------------------------------------------------------------
  // Photon true information

  // Info when tracks enter/leave the sensitive volume
  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();

  // Get position when entering the detector
  G4ThreeVector posPhoton = preStepPoint->GetPosition();

  // Get photon wavelength
  G4ThreeVector momPhoton = preStepPoint->GetMomentum();

  // Get time information
  G4double time = preStepPoint->GetGlobalTime();

  // ---------------------------------------------------------------------------
  // Photon reconstructed information

  // Get the index of the detector where a photon interacted
  const G4VTouchable *touchable = preStepPoint->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber();

  // Get the position of the detector where a photon interacted
  G4VPhysicalVolume *physVol = touchable->GetVolume();
  G4ThreeVector posDetector = physVol->GetTranslation();

  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // Output for photon true information
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleIColumn(0, 0, evt);
  man->FillNtupleDColumn(0, 1, posPhoton[0]); // x
  man->FillNtupleDColumn(0, 2, posPhoton[1]); // y
  man->FillNtupleDColumn(0, 3, posPhoton[2]); // z
  man->FillNtupleDColumn(0, 4, time);
  man->AddNtupleRow(0);

  // Output for photon reconstructed information depending on efficiency
  man->FillNtupleIColumn(1, 0, evt);
  man->FillNtupleDColumn(1, 1, posDetector[0]); // x
  man->FillNtupleDColumn(1, 2, posDetector[1]); // y
  man->FillNtupleDColumn(1, 3, posDetector[2]); // z
  man->AddNtupleRow(1);

  return true;
};
