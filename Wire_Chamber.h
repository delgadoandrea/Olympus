#ifndef WIRE_CHAMBER_H
#define WIRE_CHAMBER_H

#define N_WC 6

class G4VPhysicalVolume;

class Wire_Chamber {
public:

		Wire_Chamber();

		~Wire_Chamber();

		void Build(G4VPhysicalVolume * World_phys);

private:

};
#endif