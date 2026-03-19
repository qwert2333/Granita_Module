#include "physics.hh"


#include "G4EmParameters.hh"

#include "G4OpticalPhysics.hh"



//
  // INCL : cf INCLXXPhysicsListHelper.icc  in /cvmfs/geant4.cern.ch/geant4/11.3/share/source/physics_lists/lists/include

MyPhysicsList::MyPhysicsList()
{


 std::cout << std::endl << " ------ MANU: enter in MyPhysicsList::MyPhysicsList() ----- " << std::endl << std::endl ;

/*
    //RegisterPhysics (new G4EmStandardPhysics());
    //RegisterPhysics (new G4OpticalPhysics());
    //RegisterPhysics (new G4StoppingPhysics());
    //RegisterPhysics (new G4StoppingPhysicsFritiofWithBinaryCascade());
    
    
    // EM Physics
    //RegisterPhysics( new G4EmStandardPhysics());
     //RegisterPhysics( new G4EmStandardPhysicsWVI() );
    //RegisterPhysics( new G4EmStandardPhysics_option4() );
    RegisterPhysics( new G4EmStandardPhysicsSS () ) ;

    // Synchroton Radiation & GN Physics
    //RegisterPhysics( new G4EmExtraPhysics());

    // Decays 
    RegisterPhysics( new G4DecayPhysics());    // otherwise segmentation fault happens...

    // Hadron Elastic scattering
    //RegisterPhysics( new G4HadronElasticPhysics());

    // Hadron Physics
    //RegisterPhysics( new G4HadronPhysicsFTFP_BERT());

    // Stopping Physics    - was uncommented 
     //RegisterPhysics( new G4StoppingPhysics() );

    // Ion Physics
    //RegisterPhysics( new G4IonPhysics());
  
    // Neutron tracking cut
    //RegisterPhysics( new G4NeutronTrackingCut());
*/


  int ver = 0;

    // EM Physics
     //RegisterPhysics (new G4EmStandardPhysics());
     RegisterPhysics( new G4EmStandardPhysics_option4() );
     //RegisterPhysics( new G4EmStandardPhysicsSS () ) ;
      //RegisterPhysics( new G4EmLowEPPhysics() );

  // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4EmExtraPhysics(ver) );

  // Decays
  RegisterPhysics( new G4DecayPhysics(ver) );

   // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysics(ver) );

   // Hadron Physics
  //RegisterPhysics(  new G4HadronPhysicsFTFP_BERT(ver));
  // INCL :
  //RegisterPhysics( new G4HadronPhysicsINCLXX(G4String(1,static_cast<char>(ver)),true,false,true)); 

  // Hadron Physics, BERT :
   RegisterPhysics(  new G4HadronPhysicsFTFP_BERT(ver));

  // Stopping Physics, BERT :
   RegisterPhysics( new G4StoppingPhysics(ver) );
  // Stopping Physics, INCL :
  // RegisterPhysics( new G4StoppingPhysicsWithINCLXX(ver) );
  // BERT, with BIC :
  //RegisterPhysics( new G4StoppingPhysicsFritiofWithBinaryCascade(ver) );

  // Ion Physics, BERT :
   RegisterPhysics( new G4IonPhysics(ver));
  // INCL:
  //RegisterPhysics( new G4IonINCLXXPhysics(ver));

  // Neutron tracking cut
  RegisterPhysics( new G4NeutronTrackingCut(ver));


auto opticalPhysics = new G4OpticalPhysics();
//opticalPhysics->SetScintillationYieldFactor(1.0);
//opticalPhysics->SetScintillationExcitationRatio(1.0);
RegisterPhysics(opticalPhysics);

//runManager->SetUserInitialization(physicsList);



  // customised parameters :
     G4EmParameters* param = G4EmParameters::Instance();
     param->SetMscThetaLimit(0.2);
     //param -> SetMscMuHadRangeFactor( 0.002) ;
   
     //param -> SetLowestMuHadEnergy( 100 * CLHEP::eV );

 std::cout << std::endl << " ------ MANU: exit from MyPhysicsList::MyPhysicsList() ----- " << std::endl << std::endl ;


}

MyPhysicsList::~MyPhysicsList(){}

