#include "Test.h"

//Prueba el grafo
void test1(string s)
{
	for(int i=0; i<1000000;i++){
		Graph * g = Graph::LoadGraph(s);
		cout <<i<< endl;
		delete g;
	}
	cout << "fin" << endl;
}

//Prueba el dijkstra
void test2(string s)
{
	Graph * g = Graph::LoadGraph(s);
	for(int i=0; i<1000000;i++){
		Path * p = Algorithms::Dijkstra(g,1,10);
		p->Show();
		cout << endl;
		delete p;
	}
	cout << "fin" << endl;
}

//Prueba la operación de copia de un grafo
void test4(string s)
{
	Graph * g = Graph::LoadGraph(s);
	for(int i=0; i<1000000;i++){
		Graph * g2 = g->Copy();
		cout <<i<< endl;
		delete g2;
	}
	cout << "fin" << endl;
}

//Prueba las colecciones
void test5()
{
	for(int i=0; i<1000000;i++){
		Collection * c = new Collection();
		for(int j=0; j <100;j++)
		{
			c->Add((Object*)new Integer(j));
		}
		cout <<i<< endl;
		c->Destroy();
		delete c;
	}
	cout << "fin" << endl;
}

//Prueba keytree
void test6()
{
	Graph * g = Graph::LoadGraph("hola");
	KeyTree * tree = KeyTree::GetKeyTree(g,1);
	tree->Show();
	cout << "fin" << endl;
}

void test7()
{
	Collection * c1 = new Collection();
	Collection * c2 = new Collection();
	c1->Add((Object*)new Integer(23));
	c1->Add((Object*)new Integer(52));
	c1->Add((Object*)new Integer(61));
	c1->Add((Object*)new Integer(44));
	c1->Add((Object*)new Integer(53));
	c1->Add((Object*)new Integer(62));
	c2->Add((Object*)new Integer(52));
	c2->Add((Object*)new Integer(61));
	c2->Add((Object*)new Integer(7));
	c2->Add((Object*)new Integer(82));
	c2->Add((Object*)new Integer(93));
	c2->Add((Object*)new Integer(10));
	c1->Show();
	c2->Show();
	c1->Union(c2);
	c1->Show();
	c1->Remove(c2);
	c1->Show();
}

void test8()
{
	Graph * g = Graph::LoadGraph("hola");
	g->MarkTerminal(1);
	g->MarkTerminal(10);
	g->DisableNode(0,true);
	g->DisableEdge(1,4);
	g->DisableEdge(3,4);
	g->DisableEdge(5,4);
	g->DisableEdge(7,6);
	g->DisableEdge(9,6);
	Graph * sol = KeyTreeLocalSearch::KeyTreeLS(g);
	delete sol;
	delete g;
}

//Prueba la operación union de colecciones.
void test9()
{
	for(int i=0;i < 10000;i++)
	{
		cout << i <<endl;
	Collection * c1 = new Collection();
	Collection * c2 = new Collection();
	c1->Add((Object*)new Integer(23));
	c1->Add((Object*)new Integer(52));
	c1->Add((Object*)new Integer(61));
	c1->Add((Object*)new Integer(44));
	c1->Add((Object*)new Integer(53));
	c1->Add((Object*)new Integer(62));
	c2->Add((Object*)new Integer(52));
	c2->Add((Object*)new Integer(61));
	c2->Add((Object*)new Integer(7));
	c2->Add((Object*)new Integer(82));
	c2->Add((Object*)new Integer(93));
	c2->Add((Object*)new Integer(10));
	Collection * c3 = c1->Union(c2);
	delete c3;
	c1->Destroy();
	c2->Destroy();
	}
}

//Local KeyTree Neiborhood based Search.
void Test::TestKeyTreeLocalSearch(string s)
{
	Graph * g = Graph::LoadGraph(s);
	for(int i=0;i < 100000;i++)
	{
		Graph * g2 = KeyTreeLocalSearch::KeyTreeLS(g);
		if(g2->IsFactible())
		{
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
		delete g2;
	}
}

void Test::TestKeyPathLocalSearch(string s)
{
	Graph * g = Graph::LoadGraph(s);
	for(int i=0;i < 100000;i++)
	{
		KeyPathLocalSearch * kpls= new KeyPathLocalSearch();
		Graph * g2 = kpls->KeyPathLS(g);
		if(g2->IsFactible())
		{
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
		delete g2;
	}
}

//Local KeyPath neighbourhood based Search.
void Test::TestKeyPathLocalSearch(){
	
	bool factible;
	Graph* g, *g2, *g3;
	double costo1, costo2, costo3;
	MatrixP * p;
	int mejora = 0;
	LocalSearch * kp;
	ResultRVR result;
	Reliability * alg;
	Construction * greedy;
	long rep;
	Component c;
	int ok;
	
	
	
	for(int i = 0;i < 20;i++){
		cout << "*********************************************" << endl;
		cout << "iteracion: " << i << endl;
		cout << "comenzando..." << endl;
		//Construyo grafo de prueba 
		do{
			g = Utilities::GenerateGraph4(20,5,4);
			costo1 = g->GetCost();
			factible = g->IsFactible();
			if (!factible)
				delete g;
			else{
				cout << "grafo generado, comenzando greedy..." << endl;
				//Construyo Greedy sobre el grafo generado
				greedy = new Greedy();
				g2 = greedy->Construct(g, p, 5,ok);
				costo2 = g2->GetCost();
				factible = g2->IsFactible();
				if(!factible){
					Graph::SaveGraph("NoFactGreedy.xml",g);
					delete g;
					delete g2;
					delete greedy;
				}
				else
					cout << "greedy finalizado con exito..." << endl;
			}
		}while(!factible);
		delete greedy;		
		delete g;
			
		//Aplico busqueda local
		kp = new KeyPathLocalSearch();
		g3 = kp->LocalSearchMethod(g2,p);
		delete g2;
		costo3 = g3->GetCost();
		
		//despliego costos
		cout << "costo de g: " << costo1 << endl;
		cout << "costo post greedy: " << costo2 << endl;
		cout << "costo post busqueda: " << costo3 << endl;
		
		//Corroboro factibilidad
		if(g3->IsFactible()){
			cout << "Solucion FACTIBLE" << endl;
			cout << "Probando RVR sobre el grafo... " << endl;
			alg = new RVR();
			rep = 10*10*10*10;	
			alg->SetForRk(g3);
			result = alg->ConfMethod((unsigned)time(0),rep,g3);
			delete alg;
			cout << "RESULTADO RVR: ";
			result.mostrar();
			cout << endl;
		}
		else{
			cout << "Solucion NO FACTIBLE" << endl;
			Graph::SaveGraph("no_fact1.xml",g);
			Graph::SaveGraph("no_fact2.xml",g3);
		}
		if (costo2 < costo3){
			cout << "PROBLEMA DE COSTO" << endl;
			Graph::SaveGraph("costo1.xml",g);
			Graph::SaveGraph("costo2.xml",g3);
		}
		if (costo3 < costo2){
			mejora++;
			cout << "mejora número: " << mejora << endl;
		}
		
		delete p;
		delete g3;
	}	
	cout << "La busqueda mejoro " << mejora << " de las redes generadas" << endl; 
	delete kp;
}

//Test para la descomposición en key-paths
void Test::TestKeyPathDecomp(){

	bool factible;
	Graph* g, *g2;
	Collection *key_paths;
	Construction * greedy;
	MatrixP * p;
	KeyPathLocalSearch *kp;
	int ok;
	
	
	kp = new KeyPathLocalSearch();
	//Construyo grafo de prueba 

	for(int i = 0;i < 1;i++){
		
		do{
			g = Utilities::GenerateGraph4(20,5,4);
			factible = g->IsFactible();
			if (!factible)
				delete g;
			else{
				//Construyo Greedy sobre el grafo generado
				greedy = new Greedy();
				g2 = greedy->Construct(g, p, 5,ok);
				factible = g2->IsFactible();
				if(!factible){
					delete g;
					delete g2;
					delete greedy;
				}
			}
		}while(!factible);
		Graph::SaveGraph("prueba.xml",g2);
		delete greedy;	
		delete g;
	
		cout << i << endl;
		key_paths = kp->KeyPathDecomp(g2);
		key_paths->Show();
		cout << endl;
		key_paths->Destroy();
		delete p;
		delete g2;	
	}
	delete kp;
}

//Prueba el algoritmo de Ford Fulkerson
void TestFordFulkerson(string s, int x, int y)
{
	Graph * g = Graph::LoadGraph(s);
	DirectedGraph * gd = g->ToDirectedGraph();
	for(int i = 0; i < 10000000; i++)
	{
		Algorithms::FFAlgorithm(gd, x, y);
	}
}

void TestDirectedGraph()
{
	for(int i = 0; i < 10000000; i++)
	{
		DirectedGraph * gd = new DirectedGraph(8);
		gd->AddEdge(0,1,1);
		gd->AddEdge(0,2,1);
		gd->AddEdge(1,3,1);
		gd->AddEdge(1,4,1);
		gd->AddEdge(2,7,1);
		gd->AddEdge(7,4,1);
		gd->AddEdge(3,5,1);
		gd->AddEdge(4,6,1);
		gd->AddEdge(5,6,1);
		delete gd;
	}
}

void TestFordFulkerson2()
{
	
	for(int i = 0; i < 10000000; i++)
	{
		DirectedGraph * gd = new DirectedGraph(8);
		gd->AddEdge(0,1,1);
		gd->AddEdge(0,2,1);
		gd->AddEdge(1,3,1);
		gd->AddEdge(1,4,1);
		gd->AddEdge(2,7,1);
		gd->AddEdge(7,4,1);
		gd->AddEdge(3,5,1);
		gd->AddEdge(4,6,1);
		gd->AddEdge(5,6,1);
		Algorithms::FFAlgorithm(gd, 0, 6);
		delete gd;
	}
}

void TestFactibility(string s)
{
	Graph * g = Graph::LoadGraph(s);
	for(int i = 0; i < 10000; i++)
	{
		cout << "Is Factible " << g->IsFactible()<< endl;
	}
}

//Prueba el Heap binario
void Test::TestBinaryHeap()
{
	BinaryHeap * heap = new BinaryHeap(2);
	heap->Enqueue((INumerable *)new Number(8));
	heap->Enqueue((INumerable *)new Number(5));
	heap->Enqueue((INumerable *)new Number(2));
	heap->Enqueue((INumerable *)new Number(0));
	heap->Enqueue((INumerable *)new Number(1));
	heap->Enqueue((INumerable *)new Number(3));
	heap->Enqueue((INumerable *)new Number(4));
	heap->Enqueue((INumerable *)new Number(9));
	heap->Enqueue((INumerable *)new Number(7));
	heap->Enqueue((INumerable *)new Number(6));
	for(int i=0;i <10;i++)
	{
		cout << "," << ((INumerable*)heap->DequeueFirst())->GetValue();
	}
	cout << endl;
	heap = new BinaryHeap(10, false);
	heap->Enqueue((INumerable *)new Number(8));
	heap->Enqueue((INumerable *)new Number(5));
	heap->Enqueue((INumerable *)new Number(2));
	heap->Enqueue((INumerable *)new Number(0));
	heap->Enqueue((INumerable *)new Number(1));
	heap->Enqueue((INumerable *)new Number(3));
	heap->Enqueue((INumerable *)new Number(4));
	heap->Enqueue((INumerable *)new Number(9));
	heap->Enqueue((INumerable *)new Number(7));
	heap->Enqueue((INumerable *)new Number(6));
	for(int i=0;i <10;i++)
	{
		cout << "," << ((INumerable*)heap->DequeueFirst())->GetValue();
	}
	cout << endl;
}

void Test::TestGreedy(string input)
{
	Graph * g = Graph::LoadGraph(input);
	MatrixP * p;
	int ok;
	for(int i=0;i < 100000000;i++){
		Graph * temp = Greedy::GreedyConstruction(g, p, 1,ok);
		cout << i <<endl;
		delete temp;
		delete p;
	}
}

void Test::TestGreedyPerformance()
{
	FILE  * f = fopen("result.txt", "w");
	int ok;
	for(int i=100; i > 10; i-- )
	{
		Graph * g;
		string fileName;
		fileName.assign("");
		char * s;
		sprintf(s,"%i",i);
		fileName.append(s);
		fileName.append(".xml");
		g = Graph::LoadGraph(fileName);
		long int tStartGreedy = clock();
		MatrixP * p;
		Graph * temp = Greedy::GreedyConstruction(g, p, 1,ok);
		delete temp;
		delete p;
		delete g;
		long int tEndGreedy = clock();
		cout << i << "\t"<< tEndGreedy - tStartGreedy << endl;
		fprintf(f,"%i\t%li\n",i,tEndGreedy - tStartGreedy);
	}
	fclose(f);
}

void Test::GenerateGraphs(int startNode, int endNode)
{
	for(int i=startNode; i <= endNode; i++ )
	{
		bool factible = false;
		Graph * g;
		do
		{
			g = Utilities::GenerateGraph4(i,3,i/5);
			factible = g->IsFactible();
			if(!factible)
			{
				Graph::SaveGraph("NoFactible.xml",g);
				delete g;
			}
		}
		while(!factible);
		string fileName;
		fileName.assign("");
		char * s = new char[4];
		sprintf(s,"%i",i);
		fileName.append(s);
		fileName.append(".xml");
		Graph::SaveGraph(fileName,g);
	}
}

void TestMatrixp(string input)
{
	Graph * g = Graph::LoadGraph(input);
	Collection * terminals = g->GetTerminals();
	for(int n=0; n < 1000000000; n++)
	{
		MatrixP * p = new MatrixP(g);
		for(int i=0;i<terminals->Size();i++)
		{
			int x = ((Integer*)terminals->GetItem(i))->GetValue();
			for(int j=0;j<terminals->Size();j++)
			{
				int y = ((Integer*)terminals->GetItem(j))->GetValue();
				if(x != y)
				{
					Path * path = new Path(g);
					path->Add(0);
					path->Add(1);
					for(int k=0;k < 3;k++){
						p->GetCell(x,y)->Add((Object*)path->Copy());
					}
					delete path;
				}
			}
		}
		delete p;
		cout << n <<endl;
	}
}
void Test::TestSwapEdgeLocalSearch(string input)
{
	Graph * graph = Graph::LoadGraph(input);
	int ok;
	do
	{
		graph = Utilities::GenerateGraph(400,1000,20);
	}
	while(! graph->IsFactible());
	Graph::SaveGraph(input,graph);

	MatrixP * p;
	for(int i=0; i < 1000; i++)
	{
		Graph * graph2 = Greedy::GreedyConstruction(graph, p, 6,ok);
		Graph * graph3 = SwapKeyPathLocalSearch::SwapEdgeLS(graph2, p);
		delete graph2;
		delete graph3;
		delete p;
	}
}

void Test::TestKsp() {

	Graph * g = Graph::LoadGraph("grafo20.xml");
	Collection * ksp;
	for(int i=1; i <= 100000; i++ )
	{
		ksp = Algorithms::KSP(g,4,2,5);
		ksp->Destroy();
	}
}
