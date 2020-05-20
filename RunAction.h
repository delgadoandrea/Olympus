#ifndef RUNACTION_H
#define RUNACTION_H

#include "G4UserRunAction.hh"

class G4Timer;
class G4Run;
class TFile;
class TTree;

class RunAction : public G4UserRunAction {

public:

	RunAction();

	~RunAction();

	void BeginOfRunAction(const G4Run * run);

	void EndOfRunAction(const G4Run * run);

private:

	friend class EventAction;

	static G4Timer * Timer;      //!< Timer to record duration of run.

	static TFile * File;       //!< Pointer to file for MC data.

	static TTree * Tree;       //!< Pointer to TTree for MC data.

};
#endif
