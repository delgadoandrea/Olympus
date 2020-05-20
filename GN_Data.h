#ifndef GN_DATA_H
#define GN_DATA_H

#include <vector>
#include "TObject.h"

using namespace std;

class GN_Data : public TObject {

public:

	GN_Data();

	~GN_Data();

	void Reset();

	double P(int i);

	double Theta(int i);

	double Phi(int i);

private:

	friend class EventAction;

	int nGN;

	vector<int> id;
	vector<int> q;
	vector<int> tr;

	vector<double> x;
	vector<double> y;
	vector<double> z;

	vector<double> px;
	vector<double> py;
	vector<double> pz;

	ClassDef(GN_Data, 1)     //The OLYMPUS MC data class.
		
};
#endif