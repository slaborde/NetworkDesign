#include "ResultRVR.h"
#include <iostream>
using namespace std;

ResultRVR::ResultRVR(double m, double v){
	media = m;
	varianza = v;
}

double ResultRVR::darMedia() {
	return (media);
}

double ResultRVR::darVar() {
	return (varianza);
}

void ResultRVR::mostrar() {
	cout << "Media: " << media << endl;
	cout << "Varianza: " << varianza << endl;
}
