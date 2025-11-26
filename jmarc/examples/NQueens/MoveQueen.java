import jmarc.modeling.MARCAction;
import jmarc.modeling.MARCState;
import jmarc.modeling.MARCProblem;

import java.util.ArrayList;

public class MoveQueen extends MARCAction {

    private int movement;
    private int queen;

    // Verifica che la mossa sia valida nello stato s
    public boolean satisfiesPreconditions(MARCState s) {
        Integer N = ((NQueens) this.getActionProblem()).getDim();
        ArrayList<Integer> board = ((QueensBoard) s).getValue();
        int currentPos = board.get(queen);
        int newPos = currentPos + movement;

        return newPos >= 0 && newPos < N;
    }

    public MARCState evaluateEffects(MARCState s) {
        ArrayList<Integer> board = new ArrayList<>(((QueensBoard) s).getValue());
        board.set(queen, board.get(queen) + movement);
        return new QueensBoard((NQueens) this.getActionProblem(), board);
    }

    public double cost(MARCState s) {
        return 0;
    }

    public MoveQueen(int movement, int queen, MARCProblem p, String label) {
        super(p, label);
        int N = ((NQueens) p).getDim();

        // Validazioni
        assert movement != 0 && Math.abs(movement) < N;
        assert queen >= 0 && queen < N;

        this.queen = queen;
        this.movement = movement;
    }
}
