#include "EventAction.h"
#include "RunAction.h"
#include "GN_Data.h"
//00020 #include "EV_Data.h"
//00021 #include "GT_Data.h"
#include "WC_Data.h"
//00023 #include "TF_Data.h"
//00024 #include "LM_Data.h"
//00025 #include "MW_Data.h"
//00026 #include "SM_Data.h"
#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include <iomanip>

#include "TTree.h"

GN_Data * EventAction::gndata = new GN_Data();
//00046 EV_Data * EventAction::evdata = new EV_Data();
//00047 GT_Data * EventAction::gtdata = new GT_Data();
WC_Data* EventAction::wcdata = new WC_Data();
//00049 TF_Data* EventAction::tfdata = new TF_Data();
//00050 LM_Data * EventAction::lmdata = new LM_Data();
//00051 MW_Data * EventAction::mwdata = new MW_Data();
//00052 SM_Data * EventAction::smdata = new SM_Data();

EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event * event) {

	G4int id = event->GetEventID();

	if (id == 0) G4cout << "\nEvent processing status. One dot = 100 events."
	 << endl;
	if (id % 5000 == 0) G4cout << "\nEvent " << setw(10) << id << " " << flush;
	else if (id % 1000 == 0) G4cout << "|" << flush;
	else if (id % 500 == 0) G4cout << "+" << flush;
	else if (id % 100 == 0) G4cout << "." << flush;

}
void EventAction::EndOfEventAction(const G4Event* event) {

	TTree * Tree = RunAction::Tree;

	if (!Tree->GetBranchStatus("GN")) Tree->Branch("GN", "GN_Data", &gndata);

	//if (!Tree->GetBranchStatus("EV")) Tree->Branch("EV", "EV_Data", &evdata);
	
	//	00109    if (!Tree->GetBranchStatus("GT")) Tree->Branch("GT", "GT_Data", &gtdata);
	
	if (!Tree->GetBranchStatus("WC")) Tree->Branch("WC", "WC_Data", &wcdata);
    //if (!Tree->GetBranchStatus("TF")) Tree->Branch("TF", "TF_Data", &tfdata);
    //if (!Tree->GetBranchStatus("LM")) Tree->Branch("LM", "LM_Data", &lmdata);
	//if (!Tree->GetBranchStatus("MW")) Tree->Branch("MW", "MW_Data", &mwdata);
	//if (!Tree->GetBranchStatus("SM")) Tree->Branch("SM", "SM_Data", &smdata);

	//evdata->Reset();
	//evdata->nEV = event->GetEventID();

	gndata->Reset();

	G4int nPrim = event->GetNumberOfPrimaryVertex();

	gndata->nGN = nPrim;

	G4PrimaryVertex * vertex;
	G4PrimaryParticle * particle;
	G4ParticleDefinition * definition;

	for (G4int i = 0; i < nPrim; ++i) {

		vertex = event->GetPrimaryVertex(i);

		particle = vertex->GetPrimary();

		definition = particle->GetG4code();

		gndata->id.push_back(particle->GetPDGcode());
		gndata->q.push_back(particle->GetCharge());
		gndata->tr.push_back(particle->GetTrackID());

		gndata->x.push_back(vertex->GetX0() / cm);
		gndata->y.push_back(vertex->GetY0() / cm);
		gndata->z.push_back(vertex->GetZ0() / cm);

		gndata->px.push_back(particle->GetPx() / GeV);
		gndata->py.push_back(particle->GetPy() / GeV);
		gndata->pz.push_back(particle->GetPz() / GeV);
	}

	RunAction::Tree->Fill();

}

void EventAction::Print(const G4Event * event) {

	G4int nPrim = event->GetNumberOfPrimaryVertex();
	G4PrimaryVertex * vertex;
	G4PrimaryParticle * particle;
	G4ParticleDefinition * definition;

	G4cout << "   Number of primary vertices " << nPrim << "\n" << G4endl;

	for (G4int i = 0; i < nPrim; ++i) {

		vertex = event->GetPrimaryVertex(i);

		particle = vertex->GetPrimary();

		definition = particle->GetG4code();

		G4cout << "   Vertex " << i
		<< " PDG ID " << particle->GetPDGcode()
		<< " Charge " << particle->GetCharge()
		<< " Name " << definition->GetParticleName()
		<< G4endl;

		G4cout << "      Origin "
		<< vertex->GetX0() / cm << " "
		<< vertex->GetY0() / cm << " "
		<< vertex->GetZ0() / cm << " [cm]" << G4endl;

		G4cout << "      Momentum "
		<< particle->GetPx() / GeV << " "
		<< particle->GetPy() / GeV << " "
		<< particle->GetPz() / GeV << " [GeV/c]\n" << G4endl;
		
	}
	
}
