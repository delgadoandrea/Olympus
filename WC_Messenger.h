#ifndef WC_MESSENGER_H
#define WC_MESSENGER_H

#include "G4UImessenger.hh"
 #include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

class WC_SD;

class WC_Messenger : public G4UImessenger {

public:
	static WC_Messenger * Instance();
	
	void setWC_SDptr(WC_SD*);

	void SetNewValue(G4UIcommand * command, G4String newValues);

	G4String GetCurrentValue(G4UIcommand * command);

private:

	WC_Messenger();
	
	WC_Messenger(WC_Messenger const&) {}
	
	WC_Messenger & operator = (WC_Messenger const&);

private:

	static WC_Messenger * m_pInstance; //!< Instance of WC_Messenger class.

	G4UIdirectory * WCdir;        //!< Pointer to WC UI structure.

	WC_SD * pWC_SD;               //!< Pointer to WC_SD class.
	G4UIdirectory* WC_SDdir;     //!< Pointer to WC_SD UI structure.
	
    G4UIcmdWithADoubleAndUnit* WC_SDsetThreshold;    //!< Set threshold.
	G4UIcmdWithoutParameter* WC_SDgetThreshold;      //!< Get threshold.
	G4UIcmdWithADoubleAndUnit* WC_SDsetXresol;       //!< Set X resolution.
	G4UIcmdWithoutParameter* WC_SDgetXresol;         //!< Get X resolution.
	G4UIcmdWithADoubleAndUnit* WC_SDsetYresol;       //!< Set Y resolution.
	G4UIcmdWithoutParameter* WC_SDgetYresol;         //!< Get Y resolution.
	
		
};
#endif
