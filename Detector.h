#ifndef DETECTOR_H
#define DETECTOR_H

#include "G4VUserDetectorConstruction.hh"
#include "G4MagneticField.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UImessenger.hh"

class Wire_Chamber;

class Detector : public G4VUserDetectorConstruction {
public:
	Detector();
	~Detector();

	G4VPhysicalVolume* Construct();

private:

	Wire_Chamber* pWC;

};

#endif