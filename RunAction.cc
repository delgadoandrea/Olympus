#include "G4Timer.hh"
#include "RunAction.h"
#include "G4Run.hh"
#include "Randomize.hh"
#include "TFile.h"
#include "TTree.h"
#include <ctime>

using namespace std;

G4Timer * RunAction::Timer = new G4Timer();
TFile * RunAction::File = 0;
TTree* RunAction::Tree = 0;
RunAction::RunAction() {}
RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run * run) {

	Timer->Start();

	time_t DateTime = time(NULL);

	CLHEP::HepRandom::setTheSeed(DateTime);

	struct tm* GMTDateTime = gmtime(&DateTime);

	G4cout << "Start of run " << run->GetRunID() << "\n"
	<< "   Number of events requested "
	<< run->GetNumberOfEventToBeProcessed() << " "
	<< "   Number of events processed "
	<< run->GetNumberOfEvent() << "\n"
	<< "   GMT time " << asctime(GMTDateTime)
	<< "   Random seed " << DateTime << "\n"
	<< G4endl;

	File = new TFile("MCData.root", "RECREATE",
	                      "OLYMPUS MC data file");

	// Create a TTree to hold the MC data.

	Tree = new TTree("Tree", "OLYMPUS MC TTree");
}

void RunAction::EndOfRunAction(const G4Run * run) {

	time_t DateTime = time(NULL);

	struct tm* GMTDateTime = gmtime(&DateTime);

	long seed = CLHEP::HepRandom::getTheSeed();

	Timer->Stop();

	G4cout << "\n\nEnd of run " << run->GetRunID() << "\n"
	<< "   Number of events requested "
	<< run->GetNumberOfEventToBeProcessed() << " "
	<< "   Number of events processed "
	<< run->GetNumberOfEvent() << "\n"
	<< "   GMT time " << asctime(GMTDateTime)
	<< "   Random seed " << seed << "\n\n"
	<< *Timer
	<< G4endl;

	Tree->Print();

	File->Write();

	File->Close();
}
