#include <iostream>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "construction.hh"

#include "FTFP_BERT.hh" // PhysicsList used in HEP applications
#include "G4VModularPhysicsList.hh"
#include "G4StepLimiterPhysics.hh"
#include "QBBC.hh"      // PhysicsList used in example B1
#include "Shielding.hh"
#include "physics.hh" // Your own PhysicsList inheriting from G4VModularPhysicsList.hh


#include "action.hh"

#include "G4SystemOfUnits.hh" // 
#include <string.h>  // 
#include <math.h>    // G4math.h doesn't exist.
//using namespace std; // not recommended

// Local parameters. 
//std::string particleType    = "proton" ;
//std::string particleType    = "mu-" ;
//std::string particleType = "e-";
//std::string particleType = "gamma" ;
std::string particleType = "mu-";
//std::string particleType = "pi-"  ;

double productionCut        = 1e-1;           // mm, 0.7 by default, 1e-3

G4double kineticEnergy      = 10;  // GeV
//G4double kineticEnergy      = 25;  // GeV


//bool visualization          = true; 
bool visualization          = false;

//bool generalParticleSource  = false;   // unused I think...

G4int initialNumberOfEvents = 1; 
//G4int initialNumberOfEvents = 10 ;
//G4int initialNumberOfEvents = 1000 ;
//G4int initialNumberOfEvents = 10000;
//G4int initialNumberOfEvents = 100000;   // used for most simulations

//std::string numberOfThreads = "/run/numberOfThreads 4";
std::string numberOfThreads = "/run/numberOfThreads 1";
std::string runVerbosity    = "/run/verbose 1";

std::string eventVerbosity  = "/event/verbose 0";
std::string trackVerbosity  = "/tracking/verbose 0";
std::string stepVerbosity   = "/stepping/verbose 0";

/*
std::string eventVerbosity  = "/event/verbose 1";
std::string trackVerbosity  = "/tracking/verbose 1";
std::string stepVerbosity   = "/stepping/verbose 1";
*/




// main
int main(int argc, char** argv)
{ 

   //G4Random::setTheEngine(new CLHEP::RanecuEngine());
   G4long seed = time(NULL);
   std::cout << " Random seed used = " << seed ;
   G4Random::setTheSeed(seed);


    #ifdef G4MULTITHREADED
        G4MTRunManager* runManager = new G4MTRunManager;  // RunManager for multithread option
    #else    
        G4RunManager* runManager = new G4RunManager;  // RunManager for non-multithread option
    #endif

    runManager->SetUserInitialization(new MyDetectorConstruction());

   //G4VModularPhysicsList* physicsList = new FTFP_BERT_EMZ_HP();
   G4VModularPhysicsList* stepLimiter_physicsList = new FTFP_BERT();

   // comment the line below in order to DISABLE  optical processes :
   // stepLimiter_physicsList ->RegisterPhysics( new G4OpticalPhysics );

   // in case one needs to customise the physics list, use instead :
   // G4VModularPhysicsList* stepLimiter_physicsList = new MyPhysicsList() ;


    stepLimiter_physicsList->RegisterPhysics(new G4StepLimiterPhysics()); // THIS HAS TO BE APPLIED TO THE PHYSICSLIST OF YOUR INTEREST WHEN SETTING G4UserLimits.hh TO ANY LOGICAL VOLUME!
    runManager->SetUserInitialization(stepLimiter_physicsList);
    runManager->SetUserInitialization(new MyActionInitialization());

    G4UIExecutive* ui;



    if (visualization == true){
        ui =  new G4UIExecutive(argc, argv);
    }

    G4VisManager* visManager  =  new G4VisExecutive();
    visManager                -> Initialize();
    G4UImanager*   UImanager  =  G4UImanager::GetUIpointer();
    UImanager                 -> ApplyCommand(numberOfThreads);
    UImanager                 -> ApplyCommand("/run/initialize"); // Separated from vis.mac
    UImanager                 -> ApplyCommand(runVerbosity);
    UImanager                 -> ApplyCommand(eventVerbosity);
    UImanager                 -> ApplyCommand(trackVerbosity);
    UImanager                 -> ApplyCommand(stepVerbosity);



    if (visualization == true){
        std::cout << " before ApplyCommand  macro/vis.mac" << std::endl;
        UImanager->ApplyCommand("/control/execute macro/vis.mac");
        std::cout << " after ApplyCommand  macro/vis.mac" << std::endl;
    }


        UImanager->ApplyCommand("/gun/particle " + particleType);
        UImanager->ApplyCommand("/gun/energy " + std::to_string(kineticEnergy) + " GeV");
        //UImanager->ApplyCommand("/gun/position 0 0 -100 cm");
        UImanager->ApplyCommand("/gun/direction 0 0 1");

        std::cout << " ==== ENERGY " <<  "/gun/energy " + std::to_string(kineticEnergy) + " GeV" << std::endl;

 
        //UImanager->ApplyCommand("/process/optical/setTrackSecondariesFirst Cerenkov" ) ;

        UImanager->ApplyCommand("/run/setCut " + std::to_string(productionCut)); 


        std::cout << " before beamOn " << std::endl ;
        UImanager->ApplyCommand("/run/beamOn " + std::to_string(initialNumberOfEvents)); 
        std::cout << " after beamOn " << std::endl;

    if (ui){
        ui->SessionStart();
    }

    //delete runManager;
    return 0;
}
