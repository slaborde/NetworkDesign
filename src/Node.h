//Clase que implementa un nodo de un grafo.

#ifndef NODO_H_
#define NODO_H_

class Node {
	public:
		//Crea un nodo no terminal habilitado con probabilidad de operacion 1.
		Node();
		Node(bool, double, bool);
		Node(int, int, bool, double, bool);
		Node(const Node &);
		Node &operator=(const Node &);
		~Node();
		Node * Copy();
		void Enable();
		void Disable();
		void SetProbability(double);
		void MarkTerminal();
		void MarkNoTerminal();
		bool IsEnabled();
		double GetProbability();
		bool IsTerminal();
		void Show();
		int GetPosX();
		int GetPosY();
		void SetPosX(int);
		void SetPosY(int);

	private:
		bool enabled;
		double r;			//probabilidad de operacion
		bool terminal;
		int posx;
		int posy;
};

#endif /*Node_H_*/
