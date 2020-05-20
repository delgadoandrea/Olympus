#ifndef PHYSICS_H
#define PHYSICS_H

#include "G4VUserPhysicsList.hh"

class Physics : public G4VUserPhysicsList {

public:
	Physics();
	
	~Physics();

protected:

	void ConstructParticle();

	void ConstructProcess();

	void SetCuts();

protected:

	void ConstructBosons();

	void ConstructLeptons();

	void ConstructMesons();

	void ConstructBaryons();

protected:

	void ConstructGeneral();

	void ConstructEM();
	
};
#endif
