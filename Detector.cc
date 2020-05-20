#include "Detector.h"
#include "Materials.h"
//#include "Magnetic_Field.h"
//#include "Toroid_Magnet.h"
#include "Wire_Chamber.h"
#include "DET_Messenger.h"

#include "G4VPhysicalVolume.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"

Detector::Detector() :
	pWC(0) {
	//pMF(0), pTC(0), pBP(0), pTM(0), pGT(0), pWC(0), pTF(0), pLM(0),
	//	pMW(0), pSM(0) {
	
	DET_Messenger::Instance()->setDETptr(this);

}

Detector::~Detector() {
	//delete pMF;
	//delete pTC;
	//delete pBP;
	//delete pTM;
	//delete pGT;
	delete pWC;
	//delete pTF;
	//delete pLM;
	//delete pMW;
	//delete pSM;
}

G4VPhysicalVolume* Detector::Construct() {
	Materials(false);

	//G4cout << "Initializing the magnetic field.\n" << flush;
	
	//pMF = new Magnetic_Field("detector/magneticfield/OLYMPUS.grid", 1.0);

	//G4FieldManager * FieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	//FieldMgr->SetDetectorField(pMF);
	//FieldMgr->CreateChordFinder(pMF);

	//G4cout << "     done.\n" << G4endl << flush;
	
	// Define the World volume as a box 10 x 10 x 10 m^3.
	G4cout << "Building the world volume.\n" << G4endl;
	
	G4Box * World_solid = new G4Box("World_solid", 5.0 * m, 5.0 * m, 5.0 * m);
	G4LogicalVolume * World_log = new
	G4LogicalVolume(World_solid, G4Material::GetMaterial("G4_AIR"),"World_log", 0, 0, 0, false);
	World_log->SetVisAttributes(G4VisAttributes(false, G4Color()));
	
	G4PVPlacement * World_phys = new
	G4PVPlacement(0, G4ThreeVector(), "World_phys",World_log, 0, false, 0, false);
	
	G4cout << "     done.\n" << G4endl;
	// Other components are defined in separate routines and positioned in the 
	// World volume. These can be commented out to remove a component from
	// consideration and thus simplify the simulation if desired.
	// The routine first checks whether or not the component already exists,
	// deletes it if it does and then create an instance of the component and
	// builds it.
	// Build the target chamber, collimator and target cell.

	// Build the beampipe.
	
	// Build the TOROID magnet.
		
	//if (pTM) delete pTM;
	//pTM = new Toroid_Magnet();
	//pTM->Build(World_phys);

	// Build the GEM Tracker Detector.

	// Build the Wire Chambers.
    if (pWC) delete pWC;
	pWC = new Wire_Chamber();
	pWC->Build(World_phys);
	
	// Build the Time of Flight Detector.
	//if (pTF) delete pTF;
	//pTF = new Time_of_Flight();
	//pTF->Build(World_phys);

	// Build the Luminosity Monitor.

	// Build the MWPC.

	// Build the Symmetric_Moeller detector.

	// Return pointer to the world physical volume.
	return World_phys;

}