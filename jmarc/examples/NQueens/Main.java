import jmarc.MARCNativeWrapper;
import jmarc.solving.MARCSequentialSolver;
import jmarc.solving.MARCSolverMonitor;
import jmarc.solving.MARCFirstChoiceHillClimbing;
import jmarc.modeling.MARCSolution;
import jmarc.solving.MARCSteepestDescent;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;


public class Main {

    public static void main(String[] args) {

        Integer dim = 128;
        int maxIdle = 100;
        int restarts = 4;

        System.out.println("JMARC usage example: " + dim + "-Queens");

        ArrayList<Integer> initBoard = new ArrayList<>();
        for (int i = 0; i < dim; i++) initBoard.add(0);

        NQueens problem = new NQueens(dim);
        QueensBoard initState = new QueensBoard(problem, initBoard);
        problem.setInitialState(initState);
        System.out.println("Initial value: " + problem.heuristic(initState));

        HashSet<MoveQueen> store = new HashSet<>();
        for (int i = 0; i < dim; i++) {
            for (int j = 1; j < dim; j++) {
                store.add(new MoveQueen(j, i, problem, "move queen " + i + " down"));
                //MoveQueen act = new MoveQueen(j, i, problem, "move queen " + i + " down");
            }
        }

        MARCSequentialSolver solver = new MARCSequentialSolver(problem);
        MARCSolverMonitor mon = new MARCSolverMonitor("Sequential");
        solver.setMonitor(mon);

        MARCFirstChoiceHillClimbing fchc = new MARCFirstChoiceHillClimbing(maxIdle);
        solver.scheduleAlgorithm(fchc, restarts, true);

        System.out.println("Running First Choice Hill Climbing for " + restarts + " restarts");

        MARCSolution sol = solver.solve();

        ArrayList<Integer> boardSol = ((QueensBoard)sol.getStateSolution()).getValue();

        System.out.print("Solution state:\n[");
        for (int i = 0; i < dim; i++) System.out.print(boardSol.get(i) + ", ");
        System.out.print("]\nWith value: ");

        System.out.println(problem.heuristic(sol.getStateSolution()));
        System.out.print("\n");

    }


}
