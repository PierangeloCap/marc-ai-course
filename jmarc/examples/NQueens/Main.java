import jmarc.solving.MARCSequentialSolver;
import jmarc.solving.MARCSimulatedAnnealing;
import jmarc.solving.MARCSolverMonitor;
import jmarc.solving.MARCFirstChoiceHillClimbing;
import jmarc.modeling.MARCSolution;
import jmarc.solving.MARCSteepestDescent;

import java.util.ArrayList;
import java.util.HashSet;

public class Main {

    enum AlgorithmType {
        HILL_CLIMBING_FIRST_CHOICE,
        SIMULATED_ANNEALING,
        STEEPEST_DESCENT_RESTARTS
    }

    public static void main(String[] args) {

        // CONFIGURAZIONE
        Integer dim = 50;
        AlgorithmType type = AlgorithmType.SIMULATED_ANNEALING;

        // Parametri Hill Climbing
        int hcRestarts = 5;
        int hcMaxIdle = 50;

        // Parametri Simulated Annealing
        int saMaxIdle = 10000;
        double saTemp = 30.0;
        double saAlpha = 0.98;

        // Parametri Steepest Descent
        int sdRestarts = 20;

        System.out.println("Solving " + dim + "-Queens using: " + type);

        // Setup Problema
        NQueens problem = new NQueens(dim);

        // Generazione stato iniziale
        ArrayList<Integer> initVals = new ArrayList<>();
        for (int i = 0; i < dim; i++)
            initVals.add(0);
        QueensBoard initState = new QueensBoard(problem, initVals);
        problem.setInitialState(initState);

        HashSet<MoveQueen> actions = problem.generateAllActions();

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

            System.out.println("Running Steepest Descent with " + sdRestarts + " restarts...");
            solver.scheduleAlgorithm(sd, sdRestarts, true);
        }

        // Esecuzione
        System.out.println("Starting solver...");
        long startTime = System.currentTimeMillis();

        MARCSolution sol = solver.solve();

        long endTime = System.currentTimeMillis();

        // Stampa Risultati
        if (sol != null && sol.getStateSolution() != null) {
            ArrayList<Integer> result = ((QueensBoard) sol.getStateSolution()).getValue();
            double conflicts = problem.heuristic(sol.getStateSolution());

            System.out.println("------------------------------------------------");
            System.out.println("Solution found in " + (endTime - startTime) + "ms");
            System.out.println("Conflicts: " + (int) conflicts); // Dovrebbe essere 0
            System.out.println("Board: " + result);
            System.out.println("------------------------------------------------");
        } else {
            System.out.println("FAILED to find a solution.");
        }
    }

}
