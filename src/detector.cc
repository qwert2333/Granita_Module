#include "detector.hh"

// Local parameters.
bool stopAndKillTracks = false;



MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name), fHitCollection(nullptr), fHitIndex(0), fHitCID(-1) {
  collectionName.insert("hits");
}

MySensitiveDetector::~MySensitiveDetector(){}

void MySensitiveDetector::Initialize(G4HCofThisEvent *hitsCE){
  fHitCollection = new EcalHitsCollection();
  if (fHitCID < 0)
  {
      fHitCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  hitsCE->AddHitsCollection(fHitCID, fHitCollection);
  fHitIndex = 0;
  cellIDCol.clear();
}


G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

    G4int eventID   = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4double edep = aStep->GetTotalEnergyDeposit(); 
    G4Track *aTrack = aStep->GetTrack(); 
    G4String particleName = aTrack->GetParticleDefinition()->GetParticleName();

    const    G4VProcess*  theprocess = aTrack->GetCreatorProcess();
    G4String CreatorprocessName = "None" ;
    if (theprocess != 0) 
      CreatorprocessName = theprocess->GetProcessName();


    if (stopAndKillTracks == true){
        aTrack->SetTrackStatus(fStopAndKill);
        aTrack->SetTrackStatus(fKillTrackAndSecondaries);
    }

    G4int trackID = aTrack->GetTrackID(); 
    G4int parentID = aTrack->GetParentID();    
    std::cout << " enter in MySensitiveDetector::ProcessHits  event = " << eventID << " trackID = " << trackID << std::endl;
    std::cout << " Step particle name: " << particleName << ", process name " << CreatorprocessName << std::endl;

    G4int copyNo = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(0);
    std::cout << "  Hit copy number: "<<copyNo << std::endl;

    EcalHit* hit = nullptr;
    if(cellIDCol.find(copyNo) != cellIDCol.end()){
      hit = (*fHitCollection)[cellIDCol[copyNo]];
      hit->addEdep(edep);
      if(particleName=="opticalphoton"){
        if(CreatorprocessName=="Cerenkov") hit->addNphChren(1); 
        else hit->addNphScint(1);
      }
    }
    else{
      hit = new EcalHit(copyNo);
      hit->setEdep(edep);
      if(particleName=="opticalphoton"){
        if(CreatorprocessName=="Cerenkov") hit->addNphChren(1);
        else hit->addNphScint(1);
      }      

      fHitCollection->insert(hit);
      cellIDCol.insert(std::make_pair(copyNo, fHitIndex));
      fHitIndex++;
    }

    std::cout <<"  Hit created. Current hit size: " << fHitCollection->entries() << std::endl;
    std::cout << " exit from MySensitiveDetector::ProcessHits " << std::endl;
    return true;
}

