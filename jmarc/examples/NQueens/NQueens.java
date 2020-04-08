import jmarc.modeling.*;

import java.util.Random;
import java.util.ArrayList;


public class NQueens extends MARCInitStateProblem<Integer> implements MARCHeuristicProblem, MARCRandomProblem {

    private Integer queens;

    public boolean objectiveTest(MARCState s) {
        return this.heuristic(s) == 0;
    }

    public double heuristic(MARCState s) {
        double res = 0;
        ArrayList<Integer> board = ((QueensBoard)s).getValue();

        for (int i = 0; i < queens; i++) {
            for (int j = i+1; j < queens; j++) {
                if (board.get(i).equals(board.get(j)) || (Math.abs(board.get(j) - board.get(i)) == j - i)) res++;
            }
        }

        return res;

    }


    private int countConflicts(int index, int newVal, ArrayList<Integer> board) {
        int res = 0;
        ArrayList<Integer> sim = new ArrayList<>(board);
        sim.set(index, newVal);
        for (int i = 0; i < queens; i++) {
            for (int j = i+1; j < queens; j++) {
                if (sim.get(i).equals(sim.get(j)) || (Math.abs(sim.get(j) - sim.get(i)) == j - i)) res++;
            }
        }
        return res;
    }


    public MARCState getRandomState() {
        Random r = new Random();
        ArrayList<Integer> board = new ArrayList<>();
        for (int i = 0; i < queens; i++) board.add(r.nextInt(queens));
        return new QueensBoard(this, board);
    }

    public Integer getDim() {
        return this.queens;
    }

    public NQueens(Integer dim) {
        super(dim);
        this.queens = dim;
    }


}

