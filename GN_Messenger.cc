#include "GN_Messenger.h"
#include "Generator.h"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

GN_Messenger * GN_Messenger::m_pInstance = 0;

using namespace std;

GN_Messenger * GN_Messenger::Instance() {

	if (m_pInstance == 0) {
		m_pInstance = new GN_Messenger();
	}
	return m_pInstance;
}

GN_Messenger::GN_Messenger() {

	GNdir = new G4UIdirectory("/Olympus/GN/");
	GNdir->SetGuidance("OLYMPUS Generator user commands.");
}

void GN_Messenger::setGNptr(Generator * ptr) {

	pGN = ptr;

	GNsetEbeam = new
		 G4UIcmdWithADoubleAndUnit("/Olympus/GN/setEbeam", this);
	GNsetEbeam->SetDefaultUnit("MeV");
	GNsetEbeam->SetGuidance("Set beam kinetic energy.");
	GNsetEbeam->SetParameterName("energy", false);
	GNsetEbeam->SetRange("energy > 0.0");
	GNsetEbeam->AvailableForStates(G4State_Idle);

	GNgetEbeam = new
		 G4UIcmdWithoutParameter("/Olympus/GN/getEbeam", this);
	GNgetEbeam->SetGuidance("Get beam kinetic energy.");

	GNsetBeamCharge = new
		G4UIcmdWithAnInteger("/Olympus/GN/setBeamCharge", this);
	GNsetBeamCharge->SetGuidance("Set beam charge.");
	GNsetBeamCharge->SetParameterName("q", false);
	GNsetBeamCharge->SetRange("q = 1 || q = -1");
	GNsetBeamCharge->AvailableForStates(G4State_Idle);

	GNgetBeamCharge = new
		G4UIcmdWithoutParameter("/Olympus/GN/getBeamCharge", this);

	GNgetBeamCharge->SetGuidance("Get beam charge.");

	GNsetepThetaMin = new
		G4UIcmdWithADoubleAndUnit("/Olympus/GN/setepThetaMin", this);
	GNsetepThetaMin->SetDefaultUnit("degree");
	GNsetepThetaMin->SetGuidance("Set ep Theta min.");
	GNsetepThetaMin->SetParameterName("theta", false);
	GNsetepThetaMin->SetRange("theta >= 0.0 && theta <= 180.0");
	GNsetepThetaMin->AvailableForStates(G4State_Idle);

	GNgetepThetaMin = new
	       G4UIcmdWithoutParameter("/Olympus/GN/getepThetaMin", this);
	GNgetepThetaMin->SetGuidance("Get ep Theta min.");

	GNsetepThetaMax = new
		G4UIcmdWithADoubleAndUnit("/Olympus/GN/setepThetaMax", this);
	GNsetepThetaMax->SetDefaultUnit("degree");
	GNsetepThetaMax->SetGuidance("Set ep Theta min.");
	GNsetepThetaMax->SetParameterName("theta", false);
	GNsetepThetaMax->SetRange("theta >= 0.0 && theta <= 180.0");
	GNsetepThetaMax->AvailableForStates(G4State_Idle);

	GNgetepThetaMax = new
		 G4UIcmdWithoutParameter("/Olympus/GN/getepThetaMax", this);
	GNgetepThetaMax->SetGuidance("Get ep Theta min.");

	GNsetepPhiMin = new
		G4UIcmdWithADoubleAndUnit("/Olympus/GN/setepPhiMin", this);
	GNsetepPhiMin->SetDefaultUnit("degree");
	GNsetepPhiMin->SetGuidance("Set ep Phi min.");
	GNsetepPhiMin->SetParameterName("phi", false);
	GNsetepPhiMin->SetRange("phi >= -90.0 && phi < 90.0");
	GNsetepPhiMin->AvailableForStates(G4State_Idle);

	GNgetepPhiMin = new
	G4UIcmdWithoutParameter("/Olympus/GN/getepPhiMin", this);
	GNgetepPhiMin->SetGuidance("Get ep Phi min.");

	GNsetepPhiMax = new
		G4UIcmdWithADoubleAndUnit("/Olympus/GN/setepPhiMax", this);
	GNsetepPhiMax->SetDefaultUnit("degree");
	GNsetepPhiMax->SetGuidance("Set ep Phi min.");
	GNsetepPhiMax->SetParameterName("phi", false);
	GNsetepPhiMax->SetRange("phi > -90.0 && phi <= 90.0");
	GNsetepPhiMax->AvailableForStates(G4State_Idle);

	GNgetepPhiMax = new
		G4UIcmdWithoutParameter("/Olympus/GN/getepPhiMax", this);
	GNgetepPhiMax->SetGuidance("Get ep Phi min.");

}

void GN_Messenger::SetNewValue(G4UIcommand * command, G4String newValue) {

	if (command == GNsetEbeam) {
		pGN->setEbeam(GNsetEbeam->GetNewDoubleValue(newValue));
		G4cout << "Beam kinetic energy = " << newValue << G4endl;
	}
	else if (command == GNgetEbeam) {
		G4cout << "Beam kinetic energy = " << pGN->getEbeam() / MeV
		<< " [MeV]" << G4endl;
	}

	else if (command == GNsetBeamCharge) {
		pGN->setBeamCharge(GNsetBeamCharge->GetNewIntValue(newValue));
		G4cout << "Beam charge = " << newValue << G4endl;
	}
	else if (command == GNgetBeamCharge) {
		G4cout << "Beam charge = " << pGN->getBeamCharge() << G4endl;
	}

	else if (command == GNsetepThetaMin) {
		pGN->setepThetaMin(GNsetepThetaMin->GetNewDoubleValue(newValue));
		G4cout << "ep Theta min = " << newValue << G4endl;
	}
	else if (command == GNgetepThetaMin) {
		G4cout << "ep Theta min = " << pGN->getepThetaMin() / degree
			 << " [degree]" << G4endl;
	}
	else if (command == GNsetepThetaMax) {
		pGN->setepThetaMax(GNsetepThetaMax->GetNewDoubleValue(newValue));
		G4cout << "ep Theta max = " << newValue << G4endl;
	}
	else if (command == GNgetepThetaMax) {
		G4cout << "ep Theta max = " << pGN->getepThetaMax() / degree
			 << " [degree]" << G4endl;
	}
    else if (command == GNsetepPhiMin) {
		pGN->setepPhiMin(GNsetepPhiMin->GetNewDoubleValue(newValue));
		G4cout << "ep Phi min = " << newValue << G4endl;
	}
	else if (command == GNgetepPhiMin) {
		G4cout << "ep Phi min = " << pGN->getepPhiMin() / degree
			   << " [degree]" << G4endl;
	}
    else if (command == GNsetepPhiMax) {
		pGN->setepPhiMax(GNsetepPhiMax->GetNewDoubleValue(newValue));
		G4cout << "ep Phi max = " << newValue << G4endl;
	}
	else if (command == GNgetepPhiMax) {
		G4cout << "ep Phi max = " << pGN->getepPhiMax() / degree
			<< " [degree]" << G4endl;
	}
}

G4String GN_Messenger::GetCurrentValue(G4UIcommand * command) {
	G4String cv;
	return cv;
}