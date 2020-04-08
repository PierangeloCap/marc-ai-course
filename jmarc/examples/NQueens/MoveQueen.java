import jmarc.modeling.MARCAction;
import jmarc.modeling.MARCState;
import jmarc.modeling.MARCProblem;

import java.util.ArrayList;
import java.util.Arrays;


public class MoveQueen extends MARCAction {

    private int movement;

    private int queen;

    public boolean satisfiesPreconditions(MARCState s) {
        Integer N = ((NQueens)this.getActionProblem()).getDim();
        ArrayList<Integer> board = ((QueensBoard)s).getValue();
        // System.out.println("Position " + board.get(queen) + ", movement " + movement + ", result " + (board.get(queen) + movement < N && board.get(queen) + movement >= 0));
        return board.get(queen) + movement < N && board.get(queen) + movement >= 0;
    }

    public MARCState evaluateEffects(MARCState s) {
        ArrayList<Integer> board = new ArrayList<>();
        for (int i = 0; i < ((QueensBoard)s).getValue().size(); i++) board.add(((QueensBoard)s).getValue().get(i));
        board.set(queen, board.get(queen) + movement);
        return new QueensBoard((NQueens)this.getActionProblem(), board);
    }

    public double cost(MARCState s) {
        return 0;
    }

    public MoveQueen(int movement, int queen, MARCProblem p, String label) {
        super(p, label);
        assert queen >= 0 && queen <= ((NQueens)p).getDim() && movement > 0 && movement < ((NQueens)p).getDim();
        this.queen = queen;
        this.movement = movement;
    }

}
