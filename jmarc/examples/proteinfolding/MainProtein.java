package jmarc.examples.proteinfolding;

import jmarc.solving.MARCSequentialSolver;
import jmarc.solving.MARCSimulatedAnnealing;
import jmarc.solving.MARCSolverMonitor;
import jmarc.solving.MARCFirstChoiceHillClimbing;
import jmarc.modeling.MARCSolution;
import jmarc.modeling.MARCState;
import jmarc.solving.MARCSteepestDescent;

public class MainProtein {

    enum AlgorithmType {
        HILL_CLIMBING_FIRST_CHOICE,
        SIMULATED_ANNEALING,
        STEEPEST_DESCENT_RESTARTS,
        GENETIC_ALGORITHM
    }

    public static void main(String[] args) {

        // SEQUENZA DI ESEMPIO
        String sequence = "PHHPHPPHPPHPPHP";

        // SELEZIONA QUI L'ALGORITMO
        AlgorithmType type = AlgorithmType.GENETIC_ALGORITHM;

        // CONFIGURAZIONE PARAMETRI STANDARD
        int hcRestarts = 20;
        int hcMaxIdle = 200;

        int saMaxIdle = 50000;
        double saTemp = 100.0;
        double saAlpha = 0.95;

        int sdRestarts = 50;

        // CONFIGURAZIONE PARAMETRI GENETIC ALGORITHM
        int gaPopSize = 100; // Numero individui
        double gaMutation = 0.05; // 5% probabilità mutazione
        double gaCrossover = 0.85; // 85% probabilità crossover
        int gaGenerations = 1000; // Numero generazioni
        int gaElitism = 2; // Mantieni i 2 migliori sempre

        System.out.println("Solving Protein Folding (" + sequence.length() + " AA) using: " + type);

        // Setup Problema
        ProteinFolding2D problem = new ProteinFolding2D(sequence);

        // Setup Variabili per il risultato
        MARCState finalState = null;
        long startTime = System.currentTimeMillis();

        // LOGICA DI SELEZIONE ALGORITMO
        if (type == AlgorithmType.GENETIC_ALGORITHM) {

            ProteinGeneticSolver gaSolver = new ProteinGeneticSolver(
                    problem, gaPopSize, gaMutation, gaCrossover, gaGenerations, gaElitism);

            System.out.println("Starting Genetic Algorithm...");
            finalState = gaSolver.solve();

        } else {
            MARCState initState = problem.getRandomState();
            problem.setInitialState(initState);

            MARCSequentialSolver solver = new MARCSequentialSolver(problem);
            MARCSolverMonitor mon = new MARCSolverMonitor("Monitor");
            solver.setMonitor(mon);

            if (type == AlgorithmType.HILL_CLIMBING_FIRST_CHOICE) {
                MARCFirstChoiceHillClimbing fchc = new MARCFirstChoiceHillClimbing(hcMaxIdle);
                solver.scheduleAlgorithm(fchc, hcRestarts, true);
            } else if (type == AlgorithmType.SIMULATED_ANNEALING) {
                GeometricTemperature temp = new GeometricTemperature(saTemp, saAlpha);
                MARCSimulatedAnnealing sa = new MARCSimulatedAnnealing(temp, saMaxIdle);
                solver.scheduleAlgorithm(sa, 1, true);
            } else if (type == AlgorithmType.STEEPEST_DESCENT_RESTARTS) {
                MARCSteepestDescent sd = new MARCSteepestDescent();
                solver.scheduleAlgorithm(sd, sdRestarts, true);
            }

            System.out.println("Starting Standard Solver...");
            MARCSolution sol = solver.solve();
            if (sol != null)
                finalState = sol.getStateSolution();
        }

        long endTime = System.currentTimeMillis();

        // Stampa Risultati
        if (finalState != null) {
            // Cast specifico per ottenere le mosse
            ProteinState pState = (ProteinState) finalState;
            double energy = problem.heuristic(pState);

            System.out.println("------------------------------------------------");
            System.out.println("Solution found in " + (endTime - startTime) + "ms");
            System.out.println("Final Energy: " + energy);
            System.out.println("(Negative is Good. Positive means collisions)");
            System.out.println("Moves: " + pState.getValue());
            System.out.println("------------------------------------------------");

            System.out.println(pState.toString());
        } else {
            System.out.println("FAILED to find a solution.");
        }
    }
}