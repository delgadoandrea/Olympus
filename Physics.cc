#include "Physics.h"
#include "globals.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"
#include "G4Decay.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicsConstructor.hh"
#include "G4VUserPhysicsList.hh"


Physics::Physics() : G4VUserPhysicsList() {

	defaultCutValue = 1.0 * cm;
	SetVerboseLevel(0);
	
}

Physics::~Physics() {}

void Physics::ConstructParticle() {

	ConstructBosons();
	ConstructLeptons();
	ConstructMesons();
	ConstructBaryons();
}

void Physics::ConstructBosons() {
	 G4Geantino::GeantinoDefinition();
	 G4ChargedGeantino::ChargedGeantinoDefinition();

	 G4Gamma::GammaDefinition();
	
}

void Physics::ConstructLeptons() {
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();

	G4MuonPlus::MuonPlusDefinition();
	G4MuonMinus::MuonMinusDefinition();

	G4NeutrinoE::NeutrinoEDefinition();
	G4AntiNeutrinoE::AntiNeutrinoEDefinition();

	G4NeutrinoMu::NeutrinoMuDefinition();
	G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
	
}

void Physics::ConstructMesons() {

	G4PionPlus::PionPlusDefinition();
	G4PionMinus::PionMinusDefinition();
	G4PionZero::PionZeroDefinition();

	G4Eta::EtaDefinition();
	G4EtaPrime::EtaPrimeDefinition();

	G4KaonPlus::KaonPlusDefinition();
	G4KaonMinus::KaonMinusDefinition();
	G4KaonZero::KaonZeroDefinition();
	G4AntiKaonZero::AntiKaonZeroDefinition();
	G4KaonZeroLong::KaonZeroLongDefinition();
	G4KaonZeroShort::KaonZeroShortDefinition();

}

void Physics::ConstructBaryons() {

	G4Proton::ProtonDefinition();
	G4AntiProton::AntiProtonDefinition();

	G4Neutron::NeutronDefinition();
	G4AntiNeutron::AntiNeutronDefinition();

}

void Physics::ConstructProcess() {
	AddTransportation();
	ConstructEM();
	ConstructGeneral();
	
}

void Physics::ConstructGeneral() {

	G4Decay * theDecayProcess = new G4Decay();
	auto theParticleIterator = GetParticleIterator();
	theParticleIterator->reset();

	while ((*theParticleIterator)()) {

		G4ParticleDefinition * particle = theParticleIterator->value();
		G4ProcessManager * pmanager = particle->GetProcessManager();

		if (theDecayProcess->IsApplicable(*particle)) {
			pmanager->AddProcess(theDecayProcess);
			pmanager->SetProcessOrdering(theDecayProcess, idxPostStep);
			pmanager->SetProcessOrdering(theDecayProcess, idxAtRest);
			
		}
		
	}
	
}

void Physics::ConstructEM() {
	auto theParticleIterator = GetParticleIterator();
	theParticleIterator->reset();

	while ((*theParticleIterator)()) {
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();

		if (particleName == "gamma") {
			pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
			pmanager->AddDiscreteProcess(new G4ComptonScattering);
			pmanager->AddDiscreteProcess(new G4GammaConversion);

		}
		else if (particleName == "e-") {
			pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4eIonisation, -1, 2, 2);
			pmanager->AddProcess(new G4eBremsstrahlung, -1, -3, 3);

		}
		else if (particleName == "e+") {
			pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4eIonisation, -1, 2, 2);
			pmanager->AddProcess(new G4eBremsstrahlung, -1, -3, 3);
			pmanager->AddProcess(new G4eplusAnnihilation, 0, -1, 4);

		}
		else if (particleName == "mu+" || particleName == "mu-") {
			pmanager->AddProcess(new G4MuMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4MuIonisation, -1, 2, 2);
			pmanager->AddProcess(new G4MuBremsstrahlung, -1, -3, 3);
			pmanager->AddProcess(new G4MuPairProduction, -1, -4, 4);

		}
		else if (!(particle->IsShortLived()) &&
			particle->GetPDGCharge() != 0.0 &&
			particle->GetParticleName() != "chargedgeantino") {
			pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
			pmanager->AddProcess(new G4hIonisation, -1, 2, 2);
			pmanager->AddProcess(new G4MuBremsstrahlung, -1, -3, 3);
			pmanager->AddProcess(new G4MuPairProduction, -1, -4, 4);

		}
		
	}
	
}

void Physics::SetCuts() {

	SetCutsWithDefault();

	if (verboseLevel > 0) DumpCutValuesTable();
	
}
