#ifndef NETWORKDESIGN_H_
#define NETWORKDESIGN_H_

#include "VNS.h"
#include "Greedy.h"
#include "RVR.h"
#include "KeyTreeLocalSearch.h"
#include "time.h"

#if defined(_WIN32)
		#include "direct.h"
	#else
		#include <sys/stat.h>
		#include <sys/types.h>
		#include <sys/time.h>
	#endif

class Result
{
public:
	Result(double pcost, double preliability, Graph * pgraph);
	virtual ~Result();
	double GetCost();
	double GetReliability();
	Graph * GetGraph();
	void Show();
private:
	double cost;
	double reliability;
	Graph * graph;
};

class NetworkDesign
{
public:
	NetworkDesign();
	virtual ~NetworkDesign();
	//Algoritmo principal para el disenio de topologias de red confiables
	//***Parametros***
	//input: 		String que indica el grafo a procesar
	//cantiter: 	Entero que indica el numero de iteraciones 
	//k:			Entero utilizado para la construccion Greedy
	//umbral:		Umbral para el calculo de confiabilidad
	//confiter:		Numero de replicaciones a realizar por RVR 	
	static void NetworkDesignAlgorithm(string input,int cantiter,int k,double umbral,int simiter);
	//static void NetworkDesign::NetworkDesignAlgorithm2(string input,int cantiter,int k);
	static void NetworkDesignAlgorithm2(string input,int cantiter,int k);
	static void NetworkDesignAlgorithm3(string input,int cantiter,int k,double umbral,int simiter);
private:
	static void AddResult(Collection * c, Result * r);
	static void make_directory(const char* name);
};

#endif /*NETWORKDESIGN_H_*/
