package jmarc.examples.proteinfolding;

import jmarc.solving.MARCSequentialSolver;
import jmarc.solving.MARCSimulatedAnnealing;
import jmarc.solving.MARCSolverMonitor;
import jmarc.solving.MARCFirstChoiceHillClimbing;
import jmarc.modeling.MARCSolution;
import jmarc.modeling.MARCState;
import jmarc.solving.MARCSteepestDescent;
import java.util.HashSet;

public class MainProtein {

    enum AlgorithmType {
        HILL_CLIMBING_FIRST_CHOICE,
        SIMULATED_ANNEALING,
        STEEPEST_DESCENT_RESTARTS
    }

    public static void main(String[] args) {

        // SEQUENZA DI ESEMPIO
        String sequence = "PHHPHPPHPPHPPHP";

        AlgorithmType type = AlgorithmType.SIMULATED_ANNEALING;

        // CONFIGURAZIONE PARAMETRI
        int hcRestarts = 20;
        int hcMaxIdle = 200; // Aumentare perché lo spazio è vasto

        // Simulated Annealing
        int saMaxIdle = 50000;
        double saTemp = 100.0;
        double saAlpha = 0.95; // Raffreddamento lento essenziale per Folding

        int sdRestarts = 50;

        System.out.println("Solving Protein Folding (" + sequence.length() + " AA) using: " + type);

        // Setup Problema
        ProteinFolding2D problem = new ProteinFolding2D(sequence);

        // Generazione stato iniziale
        MARCState initState = problem.getRandomState();
        problem.setInitialState(initState);

        // Genera azioni
        HashSet<FoldProtein> actions = problem.generateAllActions();

        // Setup Solver
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

        // Esecuzione
        System.out.println("Starting solver...");
        long startTime = System.currentTimeMillis();

        MARCSolution sol = solver.solve();

        long endTime = System.currentTimeMillis();

        // Stampa Risultati
        if (sol != null && sol.getStateSolution() != null) {
            ProteinState finalState = (ProteinState) sol.getStateSolution();
            double energy = problem.heuristic(finalState);

            System.out.println("------------------------------------------------");
            System.out.println("Solution found in " + (endTime - startTime) + "ms");
            System.out.println("Final Energy: " + energy);
            System.out.println("(Negative is Good. Positive means collisions)");
            System.out.println("Moves: " + finalState.getValue());
            System.out.println("------------------------------------------------");

            System.out.println(finalState.toString());
        } else {
            System.out.println("FAILED to find a solution.");
        }
    }

}
