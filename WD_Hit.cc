#include "WC_Hit.h"
#include "G4Allocator.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
using namespace std;

WC_Hit::WC_Hit() {}

WC_Hit::WC_Hit(const WC_Hit & hit) : G4VHit() {
	copyno = hit.copyno;
	trackid = hit.trackid;
	edep = hit.edep;
	time = hit.time;
	tworld = hit.tworld;
	tlocal = hit.tlocal;
	world = hit.world;
	local = hit.local;
}

const WC_Hit & WC_Hit::operator = (const WC_Hit & hit) {
	copyno = hit.copyno;
	trackid = hit.trackid;
	edep = hit.edep;
	time = hit.time;
	tworld = hit.tworld;
	tlocal = hit.tlocal;
	world = hit.world;
	local = hit.local;
	return *this;
}

WC_Hit::~WC_Hit() {}


G4int WC_Hit::operator == (const WC_Hit & hit) const {
	return (this == &hit) ? 1 : 0;
}

G4Allocator< WC_Hit > WC_HitAllocator;

void* WC_Hit::operator new(size_t) {
	return (void*)WC_HitAllocator.MallocSingle();
	
}

void WC_Hit::operator delete(void* aHit) {
	WC_HitAllocator.FreeSingle((WC_Hit*)aHit);
}

void WC_Hit::Draw() {

	G4VVisManager * pVVisManager = G4VVisManager::GetConcreteInstance();
	if (pVVisManager) {
		
		G4Circle circle(world);
		circle.SetScreenSize(5.0);
		circle.SetFillStyle(G4Circle::filled);
		circle.SetVisAttributes(G4VisAttributes(G4Colour(1.0, 1.0, 0.0)));
		pVVisManager->Draw(circle);
	}
	
}

void WC_Hit::Print() {
	G4cout.precision(3);
    G4cout << fixed
		<< "WC Hit Copy # " << copyno
		<< "   Track #       = " << trackid << "\n"
		<< "   Edep          = " << edep / eV << " [eV]   "
		<< "   Time          = " << time / ns << " [ns]\n"
		<< "   True World    = " << tworld / cm << " [cm]   "
		<< "   True Local    = " << tlocal / cm << " [cm]\n"
		<< "   Smeared World = " << world / cm << " [cm]   "
		<< "   Smeared Local = " << local / cm << " [cm]\n"
		<< G4endl;
}
