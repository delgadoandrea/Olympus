#ifndef GN_MESSENGER_H
#define GN_MESSENGER_H

#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

class Generator;

class GN_Messenger : public G4UImessenger {

public:

	static GN_Messenger * Instance();

	void setGNptr(Generator * ptr);

	void SetNewValue(G4UIcommand * command, G4String newValues);

	G4String GetCurrentValue(G4UIcommand * command);
	
private:

	GN_Messenger();

	GN_Messenger(GN_Messenger const&) {}

	GN_Messenger & operator = (GN_Messenger const&);

	static GN_Messenger * m_pInstance;

	Generator * pGN;             //!< Pointer to Generator class.
	G4UIdirectory* GNdir;       //!< Pointer to Gen UI structure.

	G4UIcmdWithADoubleAndUnit * GNsetEbeam;      //!< Beam kinetic energy.
	G4UIcmdWithoutParameter * GNgetEbeam;      //!< Beam kinetic energy.
	G4UIcmdWithAnInteger * GNsetBeamCharge; //!< Beam charge.
	G4UIcmdWithoutParameter * GNgetBeamCharge; //!< Beam charge.
	G4UIcmdWithADoubleAndUnit * GNsetepThetaMin; //!< epTheta_Min.
	G4UIcmdWithoutParameter * GNgetepThetaMin; //!< epTheta_Min.
	G4UIcmdWithADoubleAndUnit * GNsetepThetaMax; //!< epTheta_Max.
	G4UIcmdWithoutParameter* GNgetepThetaMax; //!< epTheta_Max.
	G4UIcmdWithADoubleAndUnit* GNsetepPhiMin;   //!< epPhi_Min.
	G4UIcmdWithoutParameter* GNgetepPhiMin;   //!< epPhi_Min.
	G4UIcmdWithADoubleAndUnit* GNsetepPhiMax;   //!< epPhi_Max.
	G4UIcmdWithoutParameter* GNgetepPhiMax;   //!< epPhi_Max.
};
#endif
