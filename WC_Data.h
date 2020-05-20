#ifndef WC_DATA_H
#define WC_DATA_H

#include <vector>

#include "TObject.h"

using namespace std;

class WC_Data : public TObject {
	
public:
	WC_Data();

	~WC_Data();
	
	void Reset();
	
	int nWC;
    vector<int> id;
	vector<int> tr;
	vector<double> e;
	vector<double> t;
	vector<double> tx;
	vector<double> ty;
	vector<double> tz;
	
    vector<double> txl;
	vector<double> tyl;
    vector<double> tzl;
	
    vector<double> x;
	vector<double> y;
    vector<double> z;
	
	vector<double> xl;
	vector<double> yl;
	vector<double> zl;

private:

	ClassDef(WC_Data, 1)     //The OLYMPUS WC data class.
};
#endif
