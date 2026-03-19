#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "tracking.hh"
#include "action.hh"
#include "G4AnalysisManager.hh"
#include "Randomize.hh"  // For G4RandomDirection()
#include "G4RandomTools.hh"  // ✅ this is the correct header
#include <string>  // ✅ Add this to the top


MyTrackingAction::MyTrackingAction(MyEventAction* eventAction)
    : G4UserTrackingAction(), fEventAction(eventAction) {}

MyTrackingAction::~MyTrackingAction() {}

void MyTrackingAction::PreUserTrackingAction(const G4Track* track) {
    G4int pdg = track->GetDefinition()->GetPDGEncoding();

   //std::cout << " ===========   Enter in MyTrackingAction::PreUserTrackingAction " << std::endl;

/*
    // ----- for pbars annihilations...

    if (track->GetParentID() == 1&& track->GetCreatorProcess()) {
    const G4VProcess* creator = track->GetCreatorProcess();
    G4String procName = creator->GetProcessName();
    if (procName == "hINCLXXCaptureAtRest") {
            // Your actual direction randomization
       G4Track* modTrack = const_cast<G4Track*>(track);
       modTrack->SetMomentumDirection(G4RandomDirection());
        }
     }

    // Retrieve initial momentum

    G4ThreeVector momentum = track->GetMomentum();

    // Retrieve other relevant information
    int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    int trackID = track->GetTrackID();
    int parentID = track->GetParentID();
    int PDGCode = track->GetDefinition()->GetPDGEncoding();
    
    double energy = track->GetKineticEnergy() / MeV;
    G4ThreeVector position = track->GetVertexPosition();
*/

    //fEventAction->RecordParticle(eventID, trackID, parentID, PDGCode, energy, position, momentum);
}

