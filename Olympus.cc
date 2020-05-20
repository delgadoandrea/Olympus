
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIsession.hh"
#include "G4UIQt.hh"
//#include "G4UIXm.hh"
//#include "G4UIXaw.hh"
#include "G4UIterminal.hh"
//#include "G4UItcsh.hh"
#include "G4UIExecutive.hh"


#include "Detector.h"
#include "Physics.h"
#include "Generator.h"
#include "RunAction.h"
#include "EventAction.h"

using namespace std;

int main(int argc, char** argv) {
	// Detect interactive mode (if no arguments) and define UI session
	//
	G4UIExecutive* ui = 0;
	if (argc == 1) {
		ui = new G4UIExecutive(argc, argv);
	}

	G4RunManager * runManager = new G4RunManager;
	
	runManager->SetUserInitialization(new Detector);
	
	runManager->SetUserInitialization(new Physics);
	
	runManager->SetUserAction(new Generator);

	runManager->SetUserAction(new RunAction);

	runManager->SetUserAction(new EventAction);

	runManager->Initialize();

    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //
    if (!ui) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else {
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted 
    // in the main() program !

    delete visManager;
    delete runManager;

	
}
