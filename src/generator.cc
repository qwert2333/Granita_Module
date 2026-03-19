#include "generator.hh"
#include "G4RandomDirection.hh"
#include <math.h>

// Local parameters. 
//G4double xposition = -100.*mm; // -100.
G4double xposition = -1.*m; 
const double twopi  = 2 * M_PI;



MyPrimaryGenerator::MyPrimaryGenerator()
{
    G4int numberOfShotFromParticleGun = 1; // Conventional to assume one primary paricle per one event.

    fParticleGun    = new G4ParticleGun(numberOfShotFromParticleGun);
    //fParticleGun    = new G4GeneralParticleSource(  );

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="anti_proton"; //"proton","neutron","gamma","e-","e+"
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

// Called by SetUserAction(generator) in action.cc
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ThreeVector pos = G4ThreeVector(0., 0., xposition);
    fParticleGun->SetParticlePosition(pos);

    G4ThreeVector dir = G4ThreeVector(0., 0., 1.); 
    fParticleGun->SetParticleMomentumDirection(dir);    // for G4Gun
    const int numberOfPrimaries = 1;
    for (int i = 0; i < numberOfPrimaries; i++){
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}



