#include "WC_Data.h"

// Include the STL header files referenced in this file.
#include <vector>

using namespace std;

ClassImp(WC_Data)

WC_Data::WC_Data() {}

WC_Data::~WC_Data() {}

void WC_Data::Reset() {
	nWC = 0;
    id.clear();
    tr.clear();
	e.clear();
    t.clear();
	
    tx.clear();
    ty.clear();
    tz.clear();
	
    txl.clear();
    tyl.clear();
    tzl.clear();
	
    x.clear();
    y.clear();
    z.clear();
	
    xl.clear();
    yl.clear();
    zl.clear();

}