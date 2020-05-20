#ifndef WC_SD_H
#define WC_SD_H

#include "Wire_Chamber.h"
#include "WC_Hit.h"

#include "G4VSensitiveDetector.hh"
#include "G4AffineTransform.hh"

// Declare classes used in this file.
class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class WC_SD : public G4VSensitiveDetector {

public:

    WC_SD(G4String name);
    
    ~WC_SD();
    
    // Member functions.
        
     //! Initialise the hits collection.
        
      void Initialize(G4HCofThisEvent * HCE);
    
      //! Routine to process each hit.
      //!
      //! Stores all the hit information in the data members of the hit class.
      //! ROHist is only given if a readout geometry is associated with th is
      //! detector.

      G4bool ProcessHits(G4Step * aStep, G4TouchableHistory * ROhist);

      //! End of event routine.

      void EndOfEvent(G4HCofThisEvent * HCE);
  
      //! In the event of an aborted event clear hit collections not assigned
      //! to the usual hit collection..
     
      void clear();

      //! Draw all hits.

      void DrawAll();
    
      //! Print all hits.
   
      void PrintAll();
   
      //! Set/Get energy threshold.
 
      G4double setThreshold(G4double);
      G4double getThreshold();
  
      //! Set/Get X resolution.
 
      G4double setXresol(G4double);
      G4double getXresol();
 
      //! Set/Get Y resolution.

      G4double setYresol(G4double);
      G4double getYresol();
 
     //! Data member consists of a pointer to the hits collection.
       
private:
      WC_HitsCollection * WC_HC;    //!< Pointer to hits collection.
    
      G4double WC_threshold;        //!< Energy threshold for valid hit.
    
      G4double WC_Xresol;           //!< x resolution.
      G4double WC_Yresol;           //!< y resolution.

      G4bool WC_Transform[N_WC];    //! Boolean if transforms defined.

      //! Pointers to transformations.
        
      G4AffineTransform WC_WorldtoLocal[N_WC];
      G4AffineTransform WC_LocaltoWorld[N_WC];
   
};
#endif