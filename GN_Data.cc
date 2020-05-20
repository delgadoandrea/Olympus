#include "GN_Data.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include <vector>
#include <cmath>

using namespace std;

ClassImp(GN_Data)

GN_Data::GN_Data() {}

GN_Data::~GN_Data() {}

void GN_Data::Reset() {

	nGN = 0;

	id.clear();
	q.clear();
	tr.clear();

	x.clear();
	y.clear();
	z.clear();

	px.clear();
	py.clear();
	pz.clear();

}

double GN_Data::P(int i) {
	return sqrt(px[i] * px[i] + py[i] * py[i] + pz[i] * pz[i]);
	
}

double GN_Data::Theta(int i) {
	return acos(pz[i] / P(i));
}

double GN_Data::Phi(int i) {
	double ph = atan2(py[i], px[i]);
	return (ph > -CLHEP::halfpi) ? ph : ph + CLHEP::twopi;
}
