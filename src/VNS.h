#ifndef VNS_H_
#define VNS_H_

#include "SwapKeyPathLocalSearch.h"
#include "Survivability.h"
#include "LocalSearch.h"

class VNS : public Survivability {
	public:
		VNS();
		virtual ~VNS();
		Graph * Optim(Graph * g, Collection * cls, MatrixP * p);
		static Graph * VNSAlgorithm(Graph * g,Collection * cls, MatrixP * p);
		static void VNSAlgorithm2(Collection * cls);
	private:
		static Graph* Search(Graph * g, int k,Collection * cls);
};

#endif /*VNS_H_*/
