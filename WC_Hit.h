#ifndef WC_HIT_H
#define WC_HIT_H

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"

 // *+****1****+****2****+****3****+****4****+****5****+****6****+****7****+****
 //! Wire_Chamber Hit class based of G4VHit.
 //!
//! Provides routines for setting and accessing the various stored information
//! on each hit in this detector.

class WC_Hit : public G4VHit {
	
public:
	WC_Hit();
	WC_Hit(const WC_Hit & hit);
	const WC_Hit & operator = (const WC_Hit & hit);
	~WC_Hit();

	G4int operator == (const WC_Hit & hit) const;
	
	void* operator new(size_t);
	
	void operator delete(void* aHit);
	
	void Draw();

	void Print();

private:

	friend class WC_SD;
	
	G4int copyno;         //!< Copy number identifying the sub-detector hit.
	G4int trackid;        //!< Track ID which created this hit.
	G4double edep;        //!< Total energy deposited by this hit.
	G4double time;        //!< Global time (relative to event) for this hit.
	G4ThreeVector tworld; //!< Position in true world coordinates.
	G4ThreeVector tlocal; //!< Position in true local coordinates.
	G4ThreeVector world;  //!< Position in world coordinates.
	G4ThreeVector local;  //!< Position in local coordinates.

};

typedef G4THitsCollection<WC_Hit> WC_HitsCollection;
#endif