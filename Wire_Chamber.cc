#include "Wire_Chamber.h"
#include "WC_SD.h"

#include "G4VPhysicalVolume.hh"
#include "G4Trap.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"

using namespace std;

Wire_Chamber::Wire_Chamber() {}

Wire_Chamber::~Wire_Chamber() {}

void Wire_Chamber::Build(G4VPhysicalVolume * World_phys) {

	cout << "Building the Wire_Chamber.\n" << flush;

	G4double TDz = 105.2866 / 2.0 * cm;
	G4double TTheta = 31.72 * degree;
	G4double TPhi = 90.00 * degree;
	G4double TDYn = 147.6676 / 2.0 * cm;
	G4double TDXnn = 57.6334 / 2.0 * cm;
	G4double TDXnp = 22.9713 / 2.0 * cm;
	G4double TAlphan = 0.0;
	G4double TDYp = 311.6788 / 2.0 * cm;
	G4double TDXpn = 143.4856 / 2.0 * cm;
	G4double TDXpp = 70.3245 / 2.0 * cm;
	G4double TAlphap = 0.0;

	G4Trap * WC_solid = new G4Trap("WC_solid", TDz, TTheta, TPhi,
	                                    TDYn, TDXnn, TDXnp, TAlphan,
	                                    TDYp, TDXpn, TDXpp, TAlphap);

	G4LogicalVolume* WC_log = new
		G4LogicalVolume(WC_solid, G4Material::GetMaterial("G4_AIR"),
                         "WC_log", 0, 0, 0, true);

	WC_log->SetVisAttributes(G4VisAttributes(false, G4Colour()));
	
	// Define the inner or gas volume WC trapezoid parameters.

	TDz = (105.2866 + 0.025) / 2.0 * cm;     // Add extra to break edges.
	TTheta = 31.72 * degree;
	TPhi = 90.00 * degree;
	TDYn = 137.2776 / 2.0 * cm;
	TDXnn = 52.8602 / 2.0 * cm;
	TDXnp = 20.6370 / 2.0 * cm;
	TAlphan = 0.0;
	TDYp = 301.2888 / 2.0 * cm;
	TDXpn = 121.7356 / 2.0 * cm;
	TDXpp = 51.0140 / 2.0 * cm;
	TAlphap = 0.0;

	// Create the inner or gas WC volume.

	G4Trap * WC_gas_solid = new G4Trap("WC_gas_solid", TDz, TTheta, TPhi,
                                        TDYn, TDXnn, TDXnp, TAlphan,
                                        TDYp, TDXpn, TDXpp, TAlphap);

    G4LogicalVolume * WC_gas_log = new
       G4LogicalVolume(WC_gas_solid, G4Material::GetMaterial("WC_gas"),
                        "WC_gas_log", 0, 0, 0, true);

	WC_gas_log->SetVisAttributes(G4VisAttributes(false, G4Colour()));
	
	// Create the WC frame solid as the difference between WC and inner (gas).

	G4SubtractionSolid * WC_frame_solid = new
	G4SubtractionSolid("WC_frame_solid", WC_solid, WC_gas_solid);

	G4LogicalVolume * WC_frame_log = new
	G4LogicalVolume(WC_frame_solid, G4Material::GetMaterial("G4_Al"),
                        "WC_frame_log", 0, 0, 0, true);

	WC_frame_log->SetVisAttributes(
       G4VisAttributes(true, G4Colour(0.8, 0.8, 0)));
	
	// Define planes at the centre of the three chambers to be sensitive.

	// First sensitive plane.

	G4double ZC = 22.0107 / 2.0 * cm;

	G4double nTDz = 0.1000 / 2.0 * cm;
	G4double scalen = (ZC - nTDz) / TDz / 2.0;
	G4double scalep = (ZC + nTDz) / TDz / 2.0;
	
	G4double nTDYn = TDYn + (TDYp - TDYn) * scalen;
	G4double nTDXnn = TDXnn + (TDXpn - TDXnn) * scalen;
	G4double nTDXnp = TDXnp + (TDXpp - TDXnp) * scalen;
	G4double nTDYp = TDYn + (TDYp - TDYn) * scalep;
	G4double nTDXpn = TDXnn + (TDXpn - TDXnn) * scalep;
	G4double nTDXpp = TDXnp + (TDXpp - TDXnp) * scalep;

	// Create the first WC sensitive plane
	G4Trap * WC_p1 = new G4Trap("WC_p1", nTDz, TTheta, TPhi,
                                 nTDYn, nTDXnn, nTDXnp, TAlphan,
                                 nTDYp, nTDXpn, nTDXpp, TAlphap);

	G4LogicalVolume * WC_p1_log = new
		G4LogicalVolume(WC_p1, G4Material::GetMaterial("WC_gas"),
                        "WC_p1_log", 0, 0, 0, true);

	WC_p1_log->SetVisAttributes(G4VisAttributes(false, G4Colour()));

	new G4PVPlacement(0, G4ThreeVector(0.0,
	                                         (ZC - TDz) * sin(TTheta),
	                                         ZC - TDz),
                       WC_p1_log, "WC_p1_phys", WC_gas_log, false, 0, false);

	// Second sensitive plane.
	ZC = (22.0107 + 14.6 + 32.1 / 2.0) * cm;
	
	scalen = (ZC - nTDz) / TDz / 2.0;
	scalep = (ZC + nTDz) / TDz / 2.0;
	
	nTDYn = TDYn + (TDYp - TDYn) * scalen;
    nTDXnn = TDXnn + (TDXpn - TDXnn) * scalen;
    nTDXnp = TDXnp + (TDXpp - TDXnp) * scalen;
    nTDYp = TDYn + (TDYp - TDYn) * scalep;
    nTDXpn = TDXnn + (TDXpn - TDXnn) * scalep;
    nTDXpp = TDXnp + (TDXpp - TDXnp) * scalep;

    // Create the second WC sensitive plane.
	G4Trap * WC_p2 = new G4Trap("WC_p2", nTDz, TTheta, TPhi,
                                   nTDYn, nTDXnn, nTDXnp, TAlphan,
                                   nTDYp, nTDXpn, nTDXpp, TAlphap);
	
	G4LogicalVolume* WC_p2_log = new
       G4LogicalVolume(WC_p2, G4Material::GetMaterial("WC_gas"),
                        "WC_p2_log", 0, 0, 0, true);

	WC_p2_log->SetVisAttributes(G4VisAttributes(false, G4Colour()));
	
	new G4PVPlacement(0, G4ThreeVector(0.0,
	                                         (ZC - TDz) * sin(TTheta),
	                                         ZC - TDz),
	                       WC_p2_log, "WC_p2_phys", WC_gas_log, false, 1, false);
	
	 // Third sensitive plane.

	ZC = (22.0107 + 14.6 + 32.1 + 14.6 + 21.9761 / 2.0) * cm;
	
	scalen = (ZC - nTDz) / TDz / 2.0;
    scalep = (ZC + nTDz) / TDz / 2.0;

	nTDYn = TDYn + (TDYp - TDYn) * scalen;
	nTDXnn = TDXnn + (TDXpn - TDXnn) * scalen;
	nTDXnp = TDXnp + (TDXpp - TDXnp) * scalen;
	nTDYp = TDYn + (TDYp - TDYn) * scalep;
	nTDXpn = TDXnn + (TDXpn - TDXnn) * scalep;
	nTDXpp = TDXnp + (TDXpp - TDXnp) * scalep;

	// Create the third WC sensitive plane.
	G4Trap * WC_p3 = new G4Trap("WC_p3", nTDz, TTheta, TPhi,
                                nTDYn, nTDXnn, nTDXnp, TAlphan,
                                 nTDYp, nTDXpn, nTDXpp, TAlphap);

	G4LogicalVolume * WC_p3_log = new
	       G4LogicalVolume(WC_p3, G4Material::GetMaterial("WC_gas"),
	                        "WC_p3_log", 0, 0, 0, true);

	WC_p3_log->SetVisAttributes(G4VisAttributes(false, G4Colour()));

	new G4PVPlacement(0, G4ThreeVector(0.0,
                                         (ZC - TDz) * sin(TTheta),
                                         ZC - TDz),
	                       WC_p3_log, "WC_p3_phys", WC_gas_log, false, 2, false);

	// Create the sensitive detectors.

	WC_SD * SD = new WC_SD("OLYMPUS/WC");

	G4SDManager::GetSDMpointer()->AddNewDetector(SD);

    WC_p1_log->SetSensitiveDetector(SD);
    WC_p2_log->SetSensitiveDetector(SD);
    WC_p3_log->SetSensitiveDetector(SD);

	// Place WC_frame in WC logical volume.
    new G4PVPlacement(0, G4ThreeVector(), WC_frame_log, "WC_frame_phys",
	                       WC_log, false, 0, false);
	// Place WC_gas in WC logical volume.
    new G4PVPlacement(0, G4ThreeVector(), WC_gas_log, "WC_gas_phys",
	                       WC_log, false, 0, false);

	// Place the wire chamber in the mother volume.
    // Define a rotation matrix for the left sector.

	// NOTE after these rotations the local WC coordinate system has Z pointing
	// away from the target, X is vertically up, and Y points downstream.
    G4RotationMatrix * RotationL = new G4RotationMatrix;
	
    RotationL->rotateY(-90.0 * degree);
    RotationL->rotateZ(-90.0 * degree);
    RotationL->rotateX(16.46 * degree);

	// Centre of chamber.
    G4double R = 157.11 * cm;
    G4double Theta = 42.20 * degree;
	
	// Calculate some trig. functions.

    G4double costheta = cos(Theta);
    G4double sintheta = sin(Theta);
    G4double cosphi = cos(0.0 * degree);
    G4double sinphi = sin(0.0 * degree);

	// Create the WC physical volume and place it in the left sector.
    new G4PVPlacement(RotationL,
                       G4ThreeVector(R * sintheta * cosphi,
                                      R * sintheta * sinphi,
                                      R * costheta),
                       "WC_phys", WC_log, World_phys, false, 0, false);

	 // Define a new rotation matrix for the right sector.
		
	// NOTE after these rotations the local WC coordinate system has Z pointing
	// away from the target, X is vertically down, and Y points downstream.
    G4RotationMatrix * RotationR = new G4RotationMatrix;
	
	RotationR->rotateY(90.0 * degree);
	RotationR->rotateZ(90.0 * degree);
	RotationR->rotateX(16.46 * degree);
	
	// Calculate some trig. functions.
    cosphi = cos(180.0 * degree);
    sinphi = sin(180.0 * degree);

	// Create the WC physical volume and place it in the world volume.
		
    new G4PVPlacement(RotationR,
                    G4ThreeVector(R * sintheta * cosphi,
                                      R * sintheta * sinphi,
                                      R * costheta),
                       "WC_phys", WC_log, World_phys, false, 1, false);

	cout << "     Done.\n" << endl << flush;
}
