#include "analysis.hh"
#include "G4UnitsTable.hh"


MyRunAction::MyRunAction()
{

    std::cout << " \n " << std::endl;
    std::cout << " -------  ENTER in MyRunAction::MyRunAction()  " << std::endl;
    std::cout << " \n " << std::endl;


    G4AnalysisManager *man2 = G4AnalysisManager::Instance(); 


    // event-wise ntuple
    man2->CreateNtuple("eventTree", "eventTree");
    man2->CreateNtupleIColumn("eventID");
    man2->CreateNtupleDColumn("MCtruth_energy");
    man2->CreateNtupleDColumn("EdepCrystal");
    man2->CreateNtupleDColumn("EdepFiberCore");
    man2->CreateNtupleDColumn("EdepFiberClad");
    man2->CreateNtupleIColumn("Nph_Cherenkov");
    man2->CreateNtupleIColumn("Nph_Scintillation");
    man2->CreateNtupleDColumn("Edep_Layer", Edep_Layer);
    man2->CreateNtupleIColumn("Nph_Cherenkov_Layer", Nph_Cherenkov_Layer);
    man2->CreateNtupleIColumn("Nph_Scint_Layer", Nph_Scint_Layer);
    man2->CreateNtupleIColumn("vecCellID", vecCellID );
    man2->CreateNtupleDColumn("vecEdep", vecEdep );
    man2->CreateNtupleIColumn("vecNChren", vecNChren );
    man2->CreateNtupleIColumn("vecNScint", vecNScint );

    man2->FinishNtuple(0);    

/*
    // step-wise ntuple
    man2->CreateNtuple("steps","steps") ;
    man2->CreateNtupleIColumn("eventID");
    man2->CreateNtupleIColumn("trackID");
    man2->CreateNtupleSColumn("particleName");
    man2->CreateNtupleDColumn("kineticEnergy");
    man2->CreateNtupleSColumn("processName");
    man2->CreateNtupleSColumn("CreatorprocessName");
    man2->CreateNtupleDColumn("stepEnergyDeposit");
    man2->CreateNtupleDColumn("preStepPositionX");
    man2->CreateNtupleDColumn("preStepPositionY");
    man2->CreateNtupleDColumn("preStepPositionZ");
    man2->CreateNtupleDColumn("postStepPositionX");
    man2->CreateNtupleDColumn("postStepPositionY");
    man2->CreateNtupleDColumn("postStepPositionZ");
    man2->CreateNtupleDColumn("deltaEnergy");
    man2->CreateNtupleDColumn("time");
    man2->CreateNtupleDColumn("stepLength");
    man2->CreateNtupleDColumn("trackLength");
    man2->CreateNtupleDColumn("dEdx");
    man2->CreateNtupleDColumn("nonIonizingEnergyDeposit");
    man2->CreateNtupleIColumn("parentID");
    man2->CreateNtupleIColumn("nSecondaries") ;
    man2->CreateNtupleDColumn("EnergySecondaries");
    man2->CreateNtupleIColumn("counter_Cerenkov");
    man2->CreateNtupleIColumn("counter_Scintillation");
    man2->CreateNtupleSColumn("preVol");
    man2->CreateNtupleSColumn("postVol");
    man2->CreateNtupleDColumn("xvtx");
    man2->CreateNtupleDColumn("yvtx");
    man2->CreateNtupleDColumn("zvtx");
    man2->CreateNtupleDColumn("ax");
    man2->CreateNtupleDColumn("ay");
    man2->CreateNtupleDColumn("az");
    
    man2->FinishNtuple(1);
*/    

}

MyRunAction::MyRunAction(MyPrimaryGenerator *PG): fPrimaryGen(PG)
{
    std::cout << " \n " << std::endl;
    std::cout << " -------  ENTER in MyRunAction::MyRunAction()  " << std::endl;
    std::cout << " -------  Read PrimaryGenerator for MC truth Info.  " << std::endl;
    std::cout << " \n " << std::endl;

    G4AnalysisManager *man2 = G4AnalysisManager::Instance();


    // event-wise ntuple
    man2->CreateNtuple("eventTree", "eventTree");
    man2->CreateNtupleIColumn("eventID");
    man2->CreateNtupleDColumn("MCtruth_energy");
    man2->CreateNtupleDColumn("EdepCrystal");
    man2->CreateNtupleDColumn("EdepFiberCore");
    man2->CreateNtupleDColumn("EdepFiberClad");
    man2->CreateNtupleIColumn("Nph_Cherenkov");
    man2->CreateNtupleIColumn("Nph_Scintillation");
    man2->CreateNtupleDColumn("Edep_Layer", Edep_Layer);
    man2->CreateNtupleIColumn("Nph_Cherenkov_Layer", Nph_Cherenkov_Layer);
    man2->CreateNtupleIColumn("Nph_Scint_Layer", Nph_Scint_Layer);
    man2->CreateNtupleIColumn("vecCellID", vecCellID );
    man2->CreateNtupleDColumn("vecEdep", vecEdep );
    man2->CreateNtupleIColumn("vecNChren", vecNChren );
    man2->CreateNtupleIColumn("vecNScint", vecNScint );

    man2->FinishNtuple(0);
}

MyRunAction::~MyRunAction(){ fPrimaryGen = nullptr; }

void MyRunAction::BeginOfRunAction(const G4Run* run)
{

    std::cout << " \n " << std::endl;
    std::cout << " -------  ENTER in MyRunAction::BeginOfRunAction " << std::endl;
    std::cout << " \n " << std::endl;

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;
    G4AnalysisManager *man3 = G4AnalysisManager::Instance();

    // set the location of the ntuples:
    man3->OpenFile("test_event.root");

/*
    //Create the output Ntuple file
    G4String rootFileName = "calo_" + fPrimaryGen->GetParticleGun()->GetParticleDefinition()->GetParticleName() + "_";
    rootFileName += G4BestUnit(fPrimaryGen->GetParticleGun()->GetParticleMomentum(), "Energy"); // GetParticleEnergy()
    rootFileName += "_Run" + std::to_string(run->GetRunID()) + ".root";
    while (rootFileName.find(" ") != G4String::npos)
    {
        rootFileName.erase(rootFileName.find(" "), 1);
    }
    fileRun = TFile::Open(rootFileName, "RECREATE");

*/
}

void MyRunAction::EndOfRunAction(const G4Run*)
{

    std::cout << " \n " << std::endl;
    std::cout << " -------  ENTER in MyRunAction::EndOfRunAction " << std::endl;
    std::cout << " \n " << std::endl;

    //treeEvt->Write();
    //delete treeEvt;
    //fileRun->Close();
    //delete fileRun;

    G4AnalysisManager *man4 = G4AnalysisManager::Instance();
    man4->Write();
    man4->CloseFile();
}

void MyRunAction::ResetEventData()
{
  eventID = 0;
  MCtruth_energy = 0.;
  EdepCrystal = 0.;
  EdepFiberCore = 0.;
  EdepFiberClad = 0.;
  Nph_Cherenkov = 0;
  Nph_Scint = 0;

  Edep_Layer.clear();
  Nph_Cherenkov_Layer.clear();
  Nph_Scint_Layer.clear();
  vecCellID.clear();
  vecEdep.clear();
  vecNChren.clear();
  vecNScint.clear();
}

