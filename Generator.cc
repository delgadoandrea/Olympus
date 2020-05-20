#include "Generator.h"
#include "GN_Messenger.h"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>

using namespace std;

Generator::Generator() {

	Ebeam = 2.0 * GeV;

	BeamCharge = -1;

	ep_Elastic = true;

	GN_Messenger::Instance()->setGNptr(this);

	epKin = new ep_Kinematics(Ebeam);

	epTheta_Min = 15.0 * degree;
	epTheta_Max = 90.0 * degree;

	cos_epThMin = cos(epTheta_Min);
	cos_epThMax = cos(epTheta_Max);

	epPhi_Min = -20.0 * degree;

	epPhi_Max = 20.0 * degree;

	particleGun = new G4ParticleGun(1);

}

Generator::~Generator() {

	delete epKin;

	delete particleGun;
	
}

void Generator::GeneratePrimaries(G4Event* event) {

	// Generate ep elastic scattering events with an isotropic distribution.

	G4double theta3 = acos(CLHEP::RandFlat::shoot() *
                           (cos_epThMax - cos_epThMin) + cos_epThMin);

	G4double phi = CLHEP::RandFlat::shoot() * (epPhi_Max - epPhi_Min) + epPhi_Min;

	if (CLHEP::RandFlat::shoot() > 0.5) phi += CLHEP::pi;

	G4double cosTH3 = cos(theta3);
	G4double sinTH3 = sin(theta3);
	G4double cosPH = cos(phi);
	 G4double sinPH = sin(phi);

	 G4double E3, E4, Q2, theta4;

	 epKin->for_e_angle(theta3, E3, E4, Q2, theta4);

	 G4double cosTH4 = cos(theta4);

	 G4double sinTH4 = sin(theta4);

	 G4ThreeVector vertex = Target_Distribution();

	 static G4ParticleTable * particletable = G4ParticleTable::GetParticleTable();

	 if (BeamCharge == -1) {
		 particleGun->SetParticleDefinition(particletable->FindParticle("e-"));
		
	}
	else {
	       particleGun->SetParticleDefinition(particletable->FindParticle("e+"));
		
	}
	particleGun->SetParticleEnergy(E3 - CLHEP::electron_mass_c2);
	particleGun->SetParticlePosition(vertex);
	particleGun->SetParticleMomentumDirection(
	G4ThreeVector(sinTH3 * cosPH, sinTH3 * sinPH, cosTH3));

	particleGun->GeneratePrimaryVertex(event);

	particleGun->SetParticleDefinition(particletable->FindParticle("proton"));
	particleGun->SetParticleEnergy(E4 - CLHEP::proton_mass_c2);
	particleGun->SetParticlePosition(vertex);
	particleGun->SetParticleMomentumDirection(
	G4ThreeVector(-sinTH4 * cosPH, -sinTH4 * sinPH, cosTH4));

	particleGun->GeneratePrimaryVertex(event);

}

G4ThreeVector Generator::Target_Distribution() {

	static G4double Half_Target_Length = 60.0 * cm / 2.0;

	G4double x, y, z, rand;

	x = CLHEP::RandGauss::shoot(0.0, 0.1 * cm);

	y = CLHEP::RandGauss::shoot(0.0, 0.1 * cm);

	rand = CLHEP::RandFlat::shoot();

	if (rand < 0.5) z = Half_Target_Length * (sqrt(2.0 * rand) - 1.0);
	else z = Half_Target_Length * (1.0 - sqrt(2.0 * (1.0 - rand)));

	return G4ThreeVector(x, y, z);
	
}

G4double Generator::setEbeam(G4double energy) {
	Ebeam = energy;
	delete epKin;
	epKin = new ep_Kinematics(Ebeam);
	return Ebeam;
}

double Generator::getEbeam() { return Ebeam; }

G4int Generator::setBeamCharge(G4int q) {
	if (q == 1 || q == -1) BeamCharge = q;
	return BeamCharge;
	
}
G4int Generator::getBeamCharge() { return BeamCharge; }

G4double Generator::setepThetaMin(G4double min) {
	epTheta_Min = min;
	cos_epThMin = cos(epTheta_Min);
	return epTheta_Min;
	
}
G4double Generator::getepThetaMin() { return epTheta_Min; }

G4double Generator::setepThetaMax(G4double max) {
	epTheta_Max = max;
	cos_epThMax = cos(epTheta_Max);
	return epTheta_Max;
	
}
G4double Generator::getepThetaMax() { return epTheta_Max; }
G4double Generator::setepPhiMin(G4double min) { return epPhi_Min = min; }
G4double Generator::getepPhiMin() { return epPhi_Min; }

G4double Generator::setepPhiMax(G4double max) { return epPhi_Max = max; }
G4double Generator::getepPhiMax() { return epPhi_Max; }

void Generator::Print() {
	G4cout << "Generator\n"
		 << "   Ebeam       = " << Ebeam / MeV << " [MeV]\n"
		 << "   Charge      = " << BeamCharge << "\n"
		 << "   epElastic   = " << ep_Elastic << "\n"
		 << "   epTheta_Min = " << epTheta_Min / degree << " [degree]\n"
		 << "   epTheta_Max = " << epTheta_Max / degree << " [degree]\n"
		 << G4endl;
	
}

ep_Kinematics::ep_Kinematics(G4double Ebeam) {

	G4double Me = CLHEP::electron_mass_c2;
	G4double Mp = CLHEP::proton_mass_c2;

	E1 = Ebeam + Me;
	p1 = sqrt(Ebeam * Ebeam + 2.0 * Me * Ebeam);

	beta = p1 / (E1 + Mp);

	E3cmbyG = (Me * Me + Mp * E1) / (E1 + Mp);

}

ep_Kinematics::~ep_Kinematics() {}

void ep_Kinematics::for_e_angle(G4double theta3, G4double & E3, G4double & E4,
	                                G4double & Q2, G4double & theta4) {
	
    G4double Me = CLHEP::electron_mass_c2;
	G4double Mp = CLHEP::proton_mass_c2;
	
	G4double cos3 = cos(theta3);
	G4double bbcos = 1.0 - beta * beta * cos3 * cos3;
	E3 = (E3cmbyG + beta * cos3 *
	           sqrt(E3cmbyG * E3cmbyG - bbcos * Me * Me)) / bbcos;
	
	G4double p3 = sqrt(E3 * E3 - Me * Me);

	Q2 = 2.0 * (E1 * E3 - p1 * p3 * cos3 - Me * Me);

	E4 = E1 + Mp - E3;

	G4double p4 = sqrt(E4 * E4 - Mp * Mp);

	theta4 = acos((p1 - p3 * cos3) / p4);

	return;
	
}

void ep_Kinematics::Print() {
	
		G4cout << "ep_Kinenmatics\n"
		 << "   E1   = " << E1 / MeV << " [MeV]\n"
		 << "   p1   = " << p1 / MeV << " [MeV]\n"
		 << "   beta = " << beta << "\n"
		 << "   E3cm = " << E3cmbyG / MeV << " [MeV]\n"
		 << G4endl;
	
}
G4double epCrossSection(const G4double& E, const G4double& theta3,
	                         const G4double& Ep, const G4double& Q2) {
	
	static G4double Mp = CLHEP::proton_mass_c2;
	static G4double Alpha = 1.0 / 137.035999679;
	static G4double Mu_p2 = pow(2.792847356, 2);
	static G4double hbarc = CLHEP::hbarc;
	
	G4double th = theta3 / 2.0;
	G4double costh = cos(th);
	G4double costh2 = pow(cos(th), 2);
	G4double sinth2 = pow(sin(th), 2);

	G4double Mott = pow((Alpha * costh * hbarc) /
			                           (2.0 * E * sinth2), 2);
	
	G4double GE2 = pow(1.0 - Q2 / (0.71 * GeV * GeV), -4);
	G4double GM2 = Mu_p2 * GE2;
	
	G4double tau = Q2 / (4.0 * Mp * Mp);

	return Mott * Ep / E * ((GE2 + tau * GM2) / (1.0 + tau) +
	                             2.0 * tau * GM2 * sinth2 / costh2);
}
