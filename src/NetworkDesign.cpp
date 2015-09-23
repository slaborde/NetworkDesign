#include "NetworkDesign.h"

NetworkDesign::NetworkDesign(){
	
}

NetworkDesign::~NetworkDesign(){
	
}

void NetworkDesign::make_directory(const char* name) {
		/*__linux__*/
   #ifdef _WIN32
		_mkdir(name);
   #else
		mkdir(name, 777);
   #endif
}

//Algoritmo principal para el disenio de topologias de red confiables
//***Parametros***
//input: 		String que indica el grafo a procesar
//cantiter: 	Entero que indica el numero de iteraciones 
//k:			Entero utilizado para la construccion Greedy
//umbral:		Umbral para el calculo de confiabilidad
//simiter:		Numero de replicaciones a realizar por RVR 			
void NetworkDesign::NetworkDesignAlgorithm(string input,int cantiter,int k,double umbral, int simiter){
	
	Graph * g1, * g2;
	LocalSearch * ls1, * ls2;
	Collection * cls, * results;
	Survivability * vns;
	Construction * greedy;
	Reliability * r;
	MatrixP * p;
	int ok = 0;
	double costo1, costo2, costo3, tiempo;
	string inputName = input.substr(0,input.length()-4);
	long start,end;
	string raiz, dir1, dir2, path1, path2;
	
	//Genero directorios para resultados
	#if defined(_WIN32)
		mkdir(inputName.data());
	#else
		mkdir(inputName.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif

	raiz = inputName.data();
	dir1.append(raiz);
	dir1.append("/ND_Resultado");

	#if defined(_WIN32)
		mkdir(dir1.data());
	#else
		mkdir(dir1.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif


	dir2.append(raiz);
	dir2.append("/Log_Iteraciones");

	#if defined(_WIN32)
		mkdir(dir2.data());
	#else
		mkdir(dir2.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif

	//Donde estan los resultados
	path1 = dir1;
	path1.append("/result.txt");
	//Donde esta el log
	path2 = dir2;
	path2.append("/log.txt");
	
	//cargo el grafo
	g1 = Graph::LoadGraph(input);
	costo1 = g1->GetCost();
	//creo la coleccion de busquedas locales a utilizar en VNS
	cls = new Collection();
	ls1 = new KeyPathLocalSearch();
	ls2 = new KeyTreeLocalSearch();
	cls->Add((Object*)ls1);
	cls->Add((Object*)ls2);	
	//Instancio vns y greedy
	greedy = new Greedy();
	vns = new VNS();
	//Esta coleccion guardara los resultados
	results = new Collection();
	
	for(int i=0; i < cantiter; i++){	
		cout << "Ejecutando Iteracion: " << i << " de: "<< cantiter << endl;

		#if defined(_WIN32)
			start = clock();
		#else
			struct timeval timeStart;
			gettimeofday(&timeStart,NULL);
		#endif

		//Construyo el grafo hasta obtener una solucion factible
		do {
		if (ok != 0) {
			delete g2;
			delete p;
		}
		g2 = greedy->Construct(g1,p,k,ok);
		}
		while (ok != 0);
		costo2 = g2->GetCost();
		//Optimizo heuristicamente
		g2 = vns->Optim(g2,cls,p);
		costo3 = g2->GetCost();
		r = new RVR();
		r->SetForRk(g2);
		ResultRVR r2 = r->ConfMethod((unsigned)time(0),simiter,g2);

		#if defined(_WIN32)
			end = clock();
			tiempo = ((end - start)/(double)CLK_TCK);
		#else
			struct timeval timeEnd;
			gettimeofday(&timeEnd,NULL);
			long seconds = timeEnd.tv_sec  - timeStart.tv_sec;
			long useconds = timeEnd.tv_usec - timeStart.tv_usec;
			tiempo = (((seconds) * 1000 + useconds/1000.0) + 0.5)/1000;
		#endif

		//Agrego los datos al log de la iteracion
		FILE * f3 = fopen(path2.data(), "a");
		char * iter = new char[4];
		sprintf(iter,"%i",i);
		fprintf(f3,"%s\t%f\t%f\t%f\t%.10f\t%.15f\t%f\n",iter,costo1,costo2,costo3,r2.darMedia(),r2.darVar(),tiempo);
		fclose(f3);
		delete iter;
		
		if (r2.darMedia() >= umbral){ 
			Result * r3 = new Result(g2->GetCost(),r2.darMedia(),g2);
			AddResult(results, r3); 
		}
		delete g2;
		delete r;
	}
	
	delete vns;
	delete greedy;
	cls->Destroy();
	delete g1;
	
	cout << "RESULTADOS NETWORKDESIGN" << endl;
	cout << "COSTO	MEDIA"<< endl;
	
	for(int i=0; i < results->Size(); i++){
		Result * r = (Result *)results->GetItem(i);
		r->Show();
		//Agrego los datos del resultado al log de resultados del grafo
		//Guardo el/los xml de la solucion
		string fileName = "";
		fileName.append(dir1.data());
		char * s = new char[4];
		sprintf(s,"%i",i);
		fileName.append("/");
		int pos = inputName.find_last_of('/', inputName.length());
		string graphName = inputName.substr(pos+1,input.length());
		fileName.append(graphName);
		fileName.append("-");
		fileName.append(s);
		fileName.append(".xml");
		Graph::SaveGraph(fileName, r->GetGraph());
		FILE * f2 = fopen(path1.data(), "a");
		fprintf(f2,"%s\t%f\t%f\n",fileName.c_str(),r->GetCost(),r->GetReliability());
		fclose(f2);
		delete s;
		if ((r->GetGraph())->IsFactible())
			cout << "**Test factibilidad ok**" << endl;
		else 
			cout << "**error**" << endl;
	}
}

//Algoritmo principal para el disenio de topologias de red confiables
//No se ejecuta RVR
void NetworkDesign::NetworkDesignAlgorithm2(string input,int cantiter,int k){
	
	Graph * g1, * g2;
	LocalSearch * ls1, * ls2;
	Collection * cls;
	Survivability * vns;
	Construction * greedy;
	MatrixP * p;
	int ok = 0;
	double costo1, costo2, costo3, tiempo;
	string inputName = input.substr(0,input.length()-4);
	long start,end;
	string raiz, dir2, path2;
	
	//Genero directorios para resultados
	#if defined(_WIN32)
		mkdir(inputName.data());
	#else
		mkdir(inputName.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif

	raiz = inputName.data();
	dir2.append(raiz);
	dir2.append("/Log_Iteraciones");

	#if defined(_WIN32)
		mkdir(dir2.data());
	#else
		mkdir(dir2.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif

	//Donde esta el log
	path2 = dir2;
	path2.append("/log.txt");
	
	//cargo el grafo
	g1 = Graph::LoadGraph(input);
	costo1 = g1->GetCost();
	//creo la coleccion de busquedas locales a utilizar en VNS
	cls = new Collection();
	ls1 = new KeyPathLocalSearch();
	ls2 = new KeyTreeLocalSearch();
	cls->Add((Object*)ls1);
	cls->Add((Object*)ls2);	
	//Instancio vns y greedy
	greedy = new Greedy();
	vns = new VNS();
	
	
	for(int i = 0; i < cantiter; i++){	
		cout << "Iteracion: " << i << endl;

		#if defined(_WIN32)
			start = clock();
		#else
			struct timeval timeStart;
			gettimeofday(&timeStart,NULL);
		#endif

		//Construyo el grafo
		cout << "Iniciando Greedy..." << endl;
		do {
		if (ok != 0) {
			delete g2;
			delete p;
		}
		g2 = greedy->Construct(g1,p,k,ok);
		}
		while (ok != 0);
		cout << "Greedy terminado..." << endl;
		costo2 = g2->GetCost();
		//Optimizo heuristicamente
		g2 = vns->Optim(g2,cls,p);
		cout << "VNS terminado..." << endl;
		costo3 = g2->GetCost();

		#if defined(_WIN32)
			end = clock();
			tiempo = ((end - start)/(double)CLK_TCK);
		#else
			struct timeval timeEnd;
			gettimeofday(&timeEnd,NULL);
			long seconds = timeEnd.tv_sec  - timeStart.tv_sec;
			long useconds = timeEnd.tv_usec - timeStart.tv_usec;
			tiempo = (((seconds) * 1000 + useconds/1000.0) + 0.5)/1000;
		#endif

		//Agrego los datos al log de la iteracion
		FILE * f3 = fopen(path2.data(), "a");
		char * iter = new char[4];
		sprintf(iter,"%i",i);
		fprintf(f3,"%s\t%f\t%f\t%f\t%f\n",iter,costo1,costo2,costo3,tiempo);
		fclose(f3);
		delete iter;
		delete g2;
		cout << "**************************************" << endl;	
	}
	delete vns;
	delete greedy;
	cls->Destroy();
	delete g1;
}



//********************Operaciones de Result********************************************
void NetworkDesign::AddResult(Collection * c, Result * r){
	bool add = true;
	bool termine = false;
	int i=0;
	
	if (c->Size() == 0)
		c->Add((Object*)r);
	else{
		while((i < c->Size()) && not(termine)){
			Result * r2 = (Result *)c->GetItem(i);
			//si el costo del nuevo es mayor y la confiabilidad es menor
			//con respecto al comparado, no agrego el resultado
			if(r->GetCost() >= r2->GetCost() && r->GetReliability() <= r2->GetReliability()){
				add = false;
				termine = true;
			}
			else{
				//Si el costo del nuevo es menor, y la confiabilidad es mayor
				//con respecto al comparado, elimino el comparado
				if(r->GetCost() <= r2->GetCost() && r->GetReliability() >= r->GetReliability()){ 
					c->Remove(i);
				}
				else{
					i++;
				}
			}
		}
		if(add){
		c->Add((Object*)r);
		}
	}
}

Result::Result(double pcost, double preliability, Graph * pgraph){
	cost = pcost;
	reliability = preliability;
	graph = pgraph->Copy();
}

Result::~Result(){
}

double Result::GetCost(){
	return cost;
}

double Result::GetReliability(){
	return reliability;
}

Graph * Result::GetGraph(){
	return graph;
}

void Result::Show(){
	cout<< cost << "\t" << reliability << endl;
}
