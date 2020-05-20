#ifndef DET_MESSENGER_H
#define DET_MESSENGER_H

#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

class Detector;

class DET_Messenger : public G4UImessenger {

public:

	static DET_Messenger * Instance();

	void setDETptr(Detector * det);

	void SetNewValue(G4UIcommand * command, G4String newValues);

	G4String GetCurrentValue(G4UIcommand * command);

private:

	DET_Messenger();

	DET_Messenger(DET_Messenger const&) {}

	DET_Messenger & operator = (DET_Messenger const&);

private:

	static DET_Messenger * m_pInstance;//!< Instance of DET_Messenger class.

	G4UIdirectory * OLYMPUSdir;        //!< Pointer to OLYMPUS UI structure.

	Detector * pDET;                   //!< Pointer to Detector class.

	G4UIdirectory* DETdir;            //!< Pointer to DET UI structure.

};
#endif
