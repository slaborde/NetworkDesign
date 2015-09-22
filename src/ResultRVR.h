//Clase para el almacenamiento del resultado del algoritmo RVR

#ifndef RESULTRVR_H_
#define RESULTRVR_H_

class ResultRVR{
	public:
		ResultRVR(double =0.0, double = 0.0);
		double darMedia();
		double darVar();
		void mostrar();

	private:
		double media, varianza;
};

#endif
