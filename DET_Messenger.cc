#include "DET_Messenger.h"
#include "Detector.h"
#include "G4UIdirectory.hh"
DET_Messenger * DET_Messenger::m_pInstance = 0;

using namespace std;

DET_Messenger * DET_Messenger::Instance() {
	if (m_pInstance == 0) {
		m_pInstance = new DET_Messenger();
	}
	return m_pInstance;
}

DET_Messenger::DET_Messenger() {
	
	OLYMPUSdir = new G4UIdirectory("/Olympus/");
	OLYMPUSdir->SetGuidance("OLYMPUS Monte Carlo user commands.");
}
void DET_Messenger::setDETptr(Detector * det) {
	pDET = det;

	DETdir = new G4UIdirectory("/Olympus/DET/");
	DETdir->SetGuidance("OLYMPUS Detector user commands.");
}

void DET_Messenger::SetNewValue(G4UIcommand * command, G4String newValue) {}

G4String DET_Messenger::GetCurrentValue(G4UIcommand * command) {
	G4String cv;
	return cv;
}
