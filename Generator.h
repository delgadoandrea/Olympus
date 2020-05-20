#ifndef GENERATOR_H
#define GENERATOR_H
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"

class G4Event;
class G4ParticleGun;
class ep_Kinematics;

class Generator : public G4VUserPrimaryGeneratorAction {

public:

	Generator();

	~Generator();

	void GeneratePrimaries(G4Event * event);

	G4ThreeVector Target_Distribution();

	G4double setEbeam(G4double);
	G4double getEbeam();

	G4int setBeamCharge(G4int);
	G4int getBeamCharge();

	G4double setepThetaMin(G4double);
	G4double getepThetaMin();

	G4double setepThetaMax(G4double);
	G4double getepThetaMax();

	G4double setepPhiMin(G4double);
	G4double getepPhiMin();

	G4double setepPhiMax(G4double);
	G4double getepPhiMax();

	void Print();

private:

	G4ParticleGun* particleGun;

	G4double Ebeam;
	G4int BeamCharge;
	G4bool ep_Elastic;
	ep_Kinematics* epKin;

	G4double epTheta_Min;
	G4double epTheta_Max;
	G4double cos_epThMin;
	G4double cos_epThMax;
	G4double epPhi_Min;
	G4double epPhi_Max;

};

class ep_Kinematics {

public:

	ep_Kinematics(G4double Ebeam);

	~ep_Kinematics();

	void for_e_angle(G4double theta3, G4double & E3, G4double & E4,
	                        G4double & Q2, G4double & theta4);

	void Print();


private:

	G4double E1;
	G4double p1;
	G4double beta;
	G4double E3cmbyG;
};

G4double epCrossSection(const G4double & E, const G4double & theta3,
                          const G4double & Ep, const G4double & Q2);
#endif
