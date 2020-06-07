# NetworkDesign
MSc Thesis: A GRASP/VND Heuristic for the Generalized
Steiner Problem with Node-Connectivity
Constraints and Hostile Reliability

## Compile
Execute: make compile

## Create the executable file
Execute: make dist

## Run
Execute for Example: ./NetworkDesign testset/att48/att48_T20/att48_T20.xml 100 5 0.99 10000 3
where:
100 =  number of network design itertions
5 = k shortest paths
0.99 = reliability threshold
10000 = reliability simulations iterations
3 = kind of network design algorithm (1: for optimization and reliability, 2: 1: for optimization only, 3: for optimization and reliability for node-link combination between 0.90-0.99)

## Nota
El código está escrito para que compile en Win, Linux y Mac OS, de todas formas algunos compiladores tienen problemas con los parentisis en algunas sentencias
de algunos métodos (por ejemplo en Adyacence.cpp linea 12), por está razón es posible que haya que quitar o agregar estos parentesis para que el código compile en alguna de las plataformas.
