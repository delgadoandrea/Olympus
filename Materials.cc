#include "Materials.h"

#include "G4Material.hh"
#include "G4NistManager.hh"

void Materials(G4bool output) {

	G4NistManager * Nist_man = G4NistManager::Instance();
	
	Nist_man->FindOrBuildMaterial("G4_Be");
	
	Nist_man->FindOrBuildMaterial("G4_C");
	
	Nist_man->FindOrBuildMaterial("G4_Al");
	
    Nist_man->FindOrBuildMaterial("G4_Cu");

	Nist_man->FindOrBuildMaterial("G4_Fe");
	
	Nist_man->FindOrBuildMaterial("G4_Si");
	
	Nist_man->FindOrBuildMaterial("G4_W");
	
	Nist_man->FindOrBuildMaterial("G4_Pb");
	
	Nist_man->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
	
	Nist_man->FindOrBuildMaterial("G4_KAPTON");
	
	Nist_man->FindOrBuildMaterial("G4_MYLAR");
	
	Nist_man->FindOrBuildMaterial("G4_BAKELITE");
	
	Nist_man->FindOrBuildMaterial("G4_CONCRETE");
	
	Nist_man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	
	Nist_man->FindOrBuildMaterial("G4_WATER");
	
	Nist_man->FindOrBuildMaterial("G4_GLASS_PLATE");
	
	Nist_man->FindOrBuildMaterial("G4_Galactic");
	
	Nist_man->FindOrBuildMaterial("G4_PbWO4");
	
	Nist_man->FindOrBuildMaterial("G4_GLASS_LEAD");
	
	G4Material * STP_Air = Nist_man->FindOrBuildMaterial("G4_AIR");

	G4Element * el_H = Nist_man->FindOrBuildElement("H");
	
	G4Element* el_C = Nist_man->FindOrBuildElement("C");
	
	G4Element* el_N = Nist_man->FindOrBuildElement("N");
	
	G4Element* el_O = Nist_man->FindOrBuildElement("O");
	
	G4Element* el_Al = Nist_man->FindOrBuildElement("Al");
	
	G4Element* el_Si = Nist_man->FindOrBuildElement("Si");
	
	G4Element* el_Ar = Nist_man->FindOrBuildElement("Ar");
	
	G4Element * el_Mn = Nist_man->FindOrBuildElement("Mn");
	
	G4Element * el_Cr = Nist_man->FindOrBuildElement("Cr");
	
	G4Element * el_Mo = Nist_man->FindOrBuildElement("Mo");
	
	G4Element* el_Ni = Nist_man->FindOrBuildElement("Ni");

	G4Element * el_P = Nist_man->FindOrBuildElement("P");
	
	G4Element * el_S = Nist_man->FindOrBuildElement("S");
	
	G4Element * el_Fe = Nist_man->FindOrBuildElement("Fe");
	
	G4Element * el_F = Nist_man->FindOrBuildElement("F");
	
	G4Element * el_Pb = Nist_man->FindOrBuildElement("Pb");
	
	G4Material * G10 = new G4Material( "NemaG10",                          // Name.
		          1.700 * g / cm3,                      // Density.
	          4);                                // # of components.

	G10->AddElement(el_Si, 1);              // Add 1 atom of Si.
	G10->AddElement(el_O, 2);              // Add 2 atoms of O.
	G10->AddElement(el_C, 3);              // Add 3 atoms of C.
	G10->AddElement(el_H, 3);              // Add 3 atoms of H.
	
	G4Material * AlN = new G4Material(
	          "AlN",                              // Name.
	          3.3 * g / cm3,                        // Density.
	          2);                                // # of components.
	
	AlN->AddElement(el_Al, 1);              // 1 atom Al.
	AlN->AddElement(el_N, 1);              // 1 atom N.

	G4Material* SST316 = new G4Material("SST316", 8.0 * g / cm3, 9);
	
	SST316->AddElement(el_Fe, 65.345 * perCent);
	SST316->AddElement(el_Cr, 17.000 * perCent);
	SST316->AddElement(el_Ni, 12.000 * perCent);
	SST316->AddElement(el_Mo, 2.500 * perCent);
	SST316->AddElement(el_Mn, 2.000 * perCent);
	SST316->AddElement(el_Si, 1.000 * perCent);
	SST316->AddElement(el_C, 0.080 * perCent);
	SST316->AddElement(el_P, 0.045 * perCent);
	SST316->AddElement(el_S, 0.030 * perCent);
	

	G4Material * WC_gas
			= new G4Material(
	          "WC_gas",                          // Name.
	          1.70 * mg / cm3,                      // Density.
	          3,                                  // # of components.
          kStateGas,                          // State.
          293.15 * kelvin,                    // Temperature.
          1.0 * atmosphere);                 // Pressure.

	WC_gas->AddElement(el_Ar, 7);           // 70% Ar by volume.
	WC_gas->AddElement(el_O, 6);           // 30% CO2 by volume.
	WC_gas->AddElement(el_C, 3);           // 30% CO2 by volume.
	
	G4Material * TPC_gas
		= new G4Material(
	          "TPC_gas",                          // Name.
	          1.6756 * mg / cm3 * 273.15 / 293.15,  // Density.
	          3,                                  // # of components.
	          kStateGas,                          // State.
	          293.15 * kelvin,                    // Temperature.
	          1.0 * atmosphere);                 // Pressure.
	
	TPC_gas->AddElement(el_Ar, 9);          // 90% Ar by volume.
	TPC_gas->AddElement(el_H, 4);          // 10% CH4 by volume.
	TPC_gas->AddElement(el_C, 1);          // 10% CH4 by volume.

	G4Material* Air
	 = new G4Material(
	          "Air",                              // Name.
	          1.2931 * mg / cm3 * 273.15 / 293.15,  // Density.
	          1,                                  // # of components.
	          kStateGas,                          // State.
	          293.15 * kelvin,                    // Temperature.
	          1.0 * atmosphere);                 // Pressure.

	Air->AddMaterial(STP_Air, 1.0);         // 100% STP_Air.
	
	G4Material * Beam_gas
		 = new G4Material(
	          "Beam_gas",                         // Name.
	          1.2931E-11 * mg / cm3 * 273.15 / 293.15,   // Density.
	          1,                                  // # of components.
	          kStateGas,                          // State.
	          293.15 * kelvin,                    // Temperature.
	          1.0E-11 * atmosphere);             // Pressure.

	Beam_gas->AddMaterial(STP_Air, 1.0);    // 100% STP_Air.
	
	G4Material * PbF2
			 = new G4Material(
	          "PbF2",                             // Name.
	          7.77 * g / cm3,                       // Density.
	          2);                                // # of components.
	
	PbF2->AddElement(el_Pb, 1);             // Add 1 atom of Pb.
	PbF2->AddElement(el_F, 2);             // Add 2 atoms of F.
	
    // Output the table of materials.

    if (output) G4cout << "\n\nThe materials defined are:\n\n"
	 << *(G4Material::GetMaterialTable())
	<< G4endl;
}