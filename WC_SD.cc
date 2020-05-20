#include "WC_SD.h"
#include "WC_Hit.h"
#include "WC_Data.h"
#include "WC_Messenger.h"

#include "EventAction.h"
#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4StepPoint.hh"
#include "G4TouchableHandle.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

using namespace std;

WC_SD::WC_SD(G4String name) : G4VSensitiveDetector(name) {
	// Insert hits collection name.
    collectionName.insert("WC_HC");
	
    // Create pointer to WC_SD Messenger.
		
    WC_Messenger::Instance()->setWC_SDptr(this);

	WC_threshold = 1.0 * eV;
	WC_Xresol = 0.02 * cm;
	WC_Yresol = 0.10 * cm;

	// Initially transformations are not defined so Boolean is false.
    for (int i = 0; i < N_WC; ++i) WC_Transform[i] = false;}

WC_SD::~WC_SD() {}

// Initialise hits collection.
void WC_SD::Initialize(G4HCofThisEvent * HCE) {
    WC_HC = new WC_HitsCollection(SensitiveDetectorName, collectionName[0]);
    static G4int HCID = -1;
	if (HCID < 0) HCID = G4SDManager::GetSDMpointer()-> GetCollectionID(collectionName[0]);
	    HCE->AddHitsCollection(HCID, WC_HC);
}
// Process hits.
G4bool WC_SD::ProcessHits(G4Step* step, G4TouchableHistory* ROhist) {
    // Get the total energy deposited in this step.
    G4double edep = step->GetTotalEnergyDeposit();
	
    // Skip this hit if below threshold.
    if (edep < WC_threshold) return false;
    // Get the PreStepPoint and the TouchableHandle.
    G4StepPoint * prestep = step->GetPreStepPoint();
	G4TouchableHandle touchable = prestep->GetTouchableHandle();
	
	// Get copy number (used to identify which WC).
	G4int copyno = touchable->GetCopyNumber(0) +
       3 * touchable->GetCopyNumber(2);

    // Get the track.
    G4Track * track = step->GetTrack();
    // Get the global time and track ID.
    G4double time = prestep->GetGlobalTime();
	G4int tr = track->GetTrackID();

	// Get the true world and local coordinate positions.
	G4ThreeVector trueworld = prestep->GetPosition();

	// If this first time store transformation and inverse.
		
    if (!WC_Transform[copyno]) {
		WC_WorldtoLocal[copyno] = touchable->GetHistory()->GetTopTransform();
		WC_LocaltoWorld[copyno] = WC_WorldtoLocal[copyno].Inverse();
        WC_Transform[copyno] = true;
	}

	G4ThreeVector Tmp = WC_WorldtoLocal[copyno].TransformPoint(trueworld);
	
    // Transform actual local coordinates into preferred OLYMPUS coordinates.

    G4ThreeVector truelocal = G4ThreeVector(-Tmp.y(), Tmp.x(), Tmp.z());

    // Create local and world coordinates smeared by resolution.

    G4ThreeVector local(
       truelocal.x() + CLHEP::RandGauss::shoot(0.0, WC_Xresol),
       truelocal.y() + CLHEP::RandGauss::shoot(0.0, WC_Yresol),
       truelocal.z());

    // Transform back to actual local coordinates.
		
    Tmp = G4ThreeVector(local.y(), -local.x(), local.z());
	
    G4ThreeVector world = WC_LocaltoWorld[copyno].TransformPoint(Tmp);
	
	// Create a pointer to a new Hit.
    WC_Hit * hit = new WC_Hit();
    // Fill the Hit information.
    hit->copyno = copyno;
    hit->trackid = tr;
    hit->edep = edep;
	hit->time = time;
    hit->tworld = trueworld;
    hit->tlocal = truelocal;
    hit->world = world;
    hit->local = local;
	
    // Add the Hit to the Hit Collection.

    WC_HC->insert(hit);
	
    //hit->Print();
	
    return true;

}

void WC_SD::EndOfEvent(G4HCofThisEvent * HCE) {
	WC_Data * wcdata = EventAction::wcdata;
	wcdata->Reset();
	
	G4int N_Hits = WC_HC->entries();
	wcdata->nWC = N_Hits;
	
	for (G4int i = 0; i < N_Hits; ++i) {
		wcdata->id.push_back((*WC_HC)[i]->copyno);
		wcdata->tr.push_back((*WC_HC)[i]->trackid);
		wcdata->e.push_back((*WC_HC)[i]->edep / eV);
		wcdata->t.push_back((*WC_HC)[i]->time / ns);
		
        wcdata->tx.push_back((*WC_HC)[i]->tworld.x() / cm);
        wcdata->ty.push_back((*WC_HC)[i]->tworld.y() / cm);
		wcdata->tz.push_back((*WC_HC)[i]->tworld.z() / cm);
		
        wcdata->txl.push_back((*WC_HC)[i]->tlocal.x() / cm);
		wcdata->tyl.push_back((*WC_HC)[i]->tlocal.y() / cm);
		wcdata->tzl.push_back((*WC_HC)[i]->tlocal.z() / cm);
		
        wcdata->x.push_back((*WC_HC)[i]->world.x() / cm);
		wcdata->y.push_back((*WC_HC)[i]->world.y() / cm);
		wcdata->z.push_back((*WC_HC)[i]->world.z() / cm);
	
        wcdata->xl.push_back((*WC_HC)[i]->local.x() / cm);
        wcdata->yl.push_back((*WC_HC)[i]->local.y() / cm);
        wcdata->zl.push_back((*WC_HC)[i]->local.z() / cm);

	}
}

void WC_SD::clear() {}

void WC_SD::DrawAll() {}
// Print all the hits.
void WC_SD::PrintAll() {
    G4int N_Hits = WC_HC->entries();
    G4cout << "\nWC Hits Collection N_Hits = " << N_Hits << "\n" << G4endl;
    for (G4int i = 0; i < N_Hits; ++i) (*WC_HC)[i]->Print();
}
// Set/Get energy threshold.

G4double WC_SD::setThreshold(G4double thres) { return WC_threshold = thres; }
G4double WC_SD::getThreshold() { return WC_threshold; }
// Set/Get X resolution.
G4double WC_SD::setXresol(G4double res) { return WC_Xresol = res; }
G4double WC_SD::getXresol() { return WC_Xresol; }
// Set/Get Y resolution.
G4double WC_SD::setYresol(G4double res) { return WC_Yresol = res; }
G4double WC_SD::getYresol() { return WC_Yresol; }