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
* 3 = kind of network design algorithm (1: for optimization and reliability, 2: for optimization only, 3: for optimization and reliability with nine node-link failure probability combinations ranging between 0.90-0.99)

## Test Set
Under "/testset" folder, TSPLIB graphs instances and their results.

## Note
This code, should compile in all platforms, ie: Win, Linux y Mac OS, etc, but some compilers have trouble with parenthesis in some special code line declarations for example: in Adyacence.cpp file, line 12. For this reason, in order to compile in a particular platform, may need to quit or add those parenthesis.
