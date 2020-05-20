#ifndef EVENTACTION_H
#define EVENTACTION_H

#include "G4UserEventAction.hh"

#include "GN_Data.h"
//00026 #include "EV_Data.h"
//00027 #include "GT_Data.h"
#include "WC_Data.h"
//00029 #include "TF_Data.h"
//00030 #include "LM_Data.h"
//00031 #include "MW_Data.h"
//00032 #include "SM_Data.h"

class G4Event;

class EventAction : public G4UserEventAction {

public:

	EventAction();

	~EventAction();

	void BeginOfEventAction(const G4Event * event);

	void EndOfEventAction(const G4Event * event);
	
	void Print(const G4Event * event);

private:

	//friend class GT_SD;
	friend class WC_SD;
	//00070      friend class TF_SD;
	//00071      friend class LM_SD;
	//00072      friend class MW_SD;
	//00073      friend class SM_SD;

	static GN_Data * gndata;      //!< Pointer to MC data.
	//00076      static EV_Data * evdata;      //!< Pointer to EV data.
	//00077      static GT_Data * gtdata;      //!< Pointer to GT data.
	static WC_Data* wcdata;      //!< Pointer to WC data.
	//00079      static TF_Data* tfdata;      //!< Pointer to TF data.
	//00080      static LM_Data* lmdata;      //!< Pointer to LM data.
	//00081      static MW_Data* mwdata;      //!< Pointer to MW data.
	//00082      static SM_Data* smdata;      //!< Pointer to MW data.

};
#endif
