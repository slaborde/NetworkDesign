# NetworkDesign

## MSc Thesis
### A GRASP/VND Heuristic for the Generalized Steiner Problem with Node-Connectivity Constraints and Hostile Reliability

## Compile
Execute: make compile

## Create the executable file
Execute: make dist

## Run
Execute for Example: "./NetworkDesign testset/att48/att48_T20/att48_T20.xml 100 5 0.99 10000 3"

where:

* 100 =  number of network design iterations
* 5 = k shortest paths
* 0.99 = reliability threshold
* 10000 = reliability simulations iterations
* 3 = kind of network design algorithm (1: for optimization and reliability, 2: 1: for optimization only, 3: for optimization and reliability with nine node-link failure probability combinations ranging between 0.90-0.99)

## Test Set
Under /testset tsp lib graphs instances and their results.

## Note
This should compile in all platforms Win, Linux y Mac OS, but some compilers have trouble with parenthesis in some special code line declarations for example: Adyacence.cpp line 12. For this reason maybe quit parenthesis should be needed in order to compile in some platforms.
