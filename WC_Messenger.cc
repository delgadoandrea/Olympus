#include "WC_Messenger.h"
#include "WC_SD.h"
#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

WC_Messenger * WC_Messenger::m_pInstance = 0;

using namespace std;

WC_Messenger * WC_Messenger::Instance() {
	if (m_pInstance == 0) {
		m_pInstance = new WC_Messenger();
	}
	return m_pInstance;
	
}

WC_Messenger::WC_Messenger() {

	WCdir = new G4UIdirectory("/Olympus/WC/");
	WCdir->SetGuidance("OLYMPUS Wire Chamber user commands.");

}

void WC_Messenger::setWC_SDptr(WC_SD * ptr) {
	pWC_SD = ptr;
	WC_SDdir = new G4UIdirectory("/Olympus/WC/SD/");
	WC_SDdir->SetGuidance("Wire Chamber Sensitive Detector commands.");

	WC_SDsetThreshold = new
	G4UIcmdWithADoubleAndUnit("/Olympus/WC/SD/setThreshold", this);
	WC_SDsetThreshold->SetDefaultUnit("eV");
	WC_SDsetThreshold->SetGuidance("Set hit threshold.");
	WC_SDsetThreshold->SetParameterName("energy", false);
	WC_SDsetThreshold->SetRange("energy >= 0.0");
	WC_SDsetThreshold->AvailableForStates(G4State_Idle);

	WC_SDgetThreshold = new
	G4UIcmdWithoutParameter("/Olympus/WC/SD/getThreshold", this);
	WC_SDgetThreshold->SetGuidance("Get hit threshold.");

	WC_SDsetXresol = new
	G4UIcmdWithADoubleAndUnit("/Olympus/WC/SD/setXresol", this);
	WC_SDsetXresol->SetDefaultUnit("um");
	WC_SDsetXresol->SetGuidance("Set X resolution.");
	WC_SDsetXresol->SetParameterName("x", false);
	WC_SDsetXresol->SetRange("x >= 0.0");
	WC_SDsetXresol->AvailableForStates(G4State_Idle);

	WC_SDgetXresol = new
	G4UIcmdWithoutParameter("/Olympus/WC/SD/getXresol", this);
	WC_SDgetXresol->SetGuidance("Get X resolution.");

	WC_SDsetYresol = new
	G4UIcmdWithADoubleAndUnit("/Olympus/WC/SD/setYresol", this);
	WC_SDsetYresol->SetDefaultUnit("um");
	WC_SDsetYresol->SetGuidance("Set Y resolution.");
	WC_SDsetYresol->SetParameterName("y", false);
	WC_SDsetYresol->SetRange("y >= 0.0");
	 WC_SDsetYresol->AvailableForStates(G4State_Idle);

	 WC_SDgetYresol = new
		G4UIcmdWithoutParameter("/Olympus/WC/SD/getYresol", this);
	WC_SDgetYresol->SetGuidance("Get Y resolution.");

}

void WC_Messenger::SetNewValue(G4UIcommand * command, G4String newValue) {

	if (command == WC_SDsetThreshold) {
		pWC_SD->setThreshold(WC_SDsetThreshold->GetNewDoubleValue(newValue));
		G4cout << "WC_SD threshold = " << newValue << G4endl;
		
	}
	else if (command == WC_SDgetThreshold) {
		G4cout << "WC_SD threshold = " << pWC_SD->getThreshold() / eV
			<< " [eV]" << G4endl;
		
	}
	else if (command == WC_SDsetXresol) {
		pWC_SD->setXresol(WC_SDsetXresol->GetNewDoubleValue(newValue));
		G4cout << "WC_SD X resolution = " << newValue << G4endl;
		
	}
	else if (command == WC_SDgetXresol) {
		G4cout << "WC_SD X resolution = " << pWC_SD->getXresol() / um
		<< " [um]" << G4endl;
		
	}
	else if (command == WC_SDsetYresol) {
		pWC_SD->setYresol(WC_SDsetYresol->GetNewDoubleValue(newValue));
		G4cout << "WC_SD Y resolution = " << newValue << G4endl;
		
	}
	else if (command == WC_SDgetYresol) {
		G4cout << "WC_SD Y resolution = " << pWC_SD->getYresol() / um
			   << " [um]" << G4endl;
		
	}

}
G4String WC_Messenger::GetCurrentValue(G4UIcommand * command) {
	G4String cv;
	return cv;
	
}
