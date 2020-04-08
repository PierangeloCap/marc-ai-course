## MARC modeling and solving strategy example for the classic NP-complete problem Hamiltonian Cycle. 

### Definition:
Given a directed graph `G=(V,E)`, such that `|V|=n` and `|E|=m`, find a permutation of `V (v_1,...,v_n)` such that for all `i` in `1,...,n` there is an edge between `v_i` and `v_i+1` and there is an edge between `v_n` and `v_1`. 

### Notes:

1. The given model implements a solving strategy using the Simulated Annealing algorithm 

2. `./input` contains 6 graph examples in edge list (EL) form which are known to have an Hamiltonian Cycle

### Compilation:
    
1. Run `build.sh` (edit script and set environment variables to suit your machine configuration)

### Usage:

`./build/MARCSolveHamiltonianCycle G temp alpha T0 timeout maxIdle`
 
- G: A valid path to a file containing the definition of a graph in the form of an edge list

- temp: A string in {inv-log, exp, geom}

- alpha: A real constant defining the temperature function (see `./temperatures` or Temperatures below)

- T0: A real constant defining the temperature function (see `./temperatures` or Temperatures below)

- timeout: Maximum number of Simulated Annealing restarts

- maxIdle: Maximum number of Simulated Annealing non-improving iterations

### Temperatures:

- `inv-log(step : int >= 0) = (alpha*T0)/(ln(step+1))`
- `exp(step : int >= 0) = T0*e^((-alpha)*(step-1)^(1/N)), where N=|V|+|E|`
- `geom(step : int >= 0) = T0*(alpha^(step-1))`
        
