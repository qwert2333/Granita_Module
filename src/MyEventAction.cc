//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//

#include "MyEventAction.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ios.hh"


#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"


// -- for MSC debug
#include "G4WentzelOKandVIxSection.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4AntiProton.hh"
#include "construction.hh"
#include "G4EmParameters.hh"
#include "G4SDManager.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyEventAction::BeginOfEventAction(const G4Event* event) {

  ResetEventData();
  const MyDetectorConstruction *detector = static_cast<const MyDetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  if (fHitCollID < 0)
  {
      auto sdManager = G4SDManager::GetSDMpointer();
      fHitCollID = sdManager->GetCollectionID("GrainModule/hits");
  }

  if(!fRunAction)
    fRunAction = static_cast<MyRunAction *>(const_cast<G4UserRunAction *>(G4RunManager::GetRunManager()->GetUserRunAction()));
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyEventAction::EndOfEventAction(const G4Event* event)
{


  // get number of stored trajectories
  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  std::size_t n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // periodic printing

  G4int eventID = event->GetEventID();
  if (eventID < 100 || eventID % 100 == 0) {
    G4cout << ">>> Event: " << eventID << G4endl;
  }

  //Get hit info
  G4HCofThisEvent *hitsCE = event->GetHCofThisEvent();
  EcalHitsCollection *HitCollection = nullptr;
  if (hitsCE)
    HitCollection = (EcalHitsCollection *)(hitsCE->GetHC(fHitCollID));

  if(HitCollection){
    size_t n_hit = HitCollection->entries();
    for(size_t i=0; i<n_hit; i++){
      G4int cellID = (*HitCollection)[i]->GetCellID();
      EdepSum += (*HitCollection)[i]->GetEdep();
      Nph_Cherenkov += (*HitCollection)[i]->GetNphChren();
      Nph_Scint += (*HitCollection)[i]->GetNphScint();

      fRunAction->Fill_vecCellID( (*HitCollection)[i]->GetCellID() );
      fRunAction->Fill_vecEdep( (*HitCollection)[i]->GetEdep() );
      fRunAction->Fill_vecNChren( (*HitCollection)[i]->GetNphChren() );
      fRunAction->Fill_vecNScint( (*HitCollection)[i]->GetNphScint() );
    }
  }

   // fill the ntuple 
   G4AnalysisManager *man5 = G4AnalysisManager::Instance();
   G4int ntupleID = 0;
   int idx = 0;

   //std::cout << " ==== FILL ntuple  event =  " << eventID << " " << captured << " " << backscattered << " " << traversed << std::endl;
   man5->FillNtupleIColumn( ntupleID, idx, eventID);  idx ++;
   man5->FillNtupleDColumn( ntupleID, idx, MCtruth_energy);  idx ++;
   man5->FillNtupleDColumn( ntupleID, idx, EdepSum);  idx ++;
   man5->FillNtupleIColumn( ntupleID, idx, Nph_Cherenkov); idx ++;
   man5->FillNtupleIColumn( ntupleID, idx, Nph_Scint);  idx ++;

   man5->AddNtupleRow( ntupleID);

   //std::cout << " ------ EXIT MyEventAction::EndOfEventAction ---- " << std::endl;
}

void MyEventAction::ResetEventData()
{
  eventID = 0;
  MCtruth_energy = 0.;
  EdepSum = 0.;
  Nph_Cherenkov = 0;
  Nph_Scint = 0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

