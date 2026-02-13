package jmarc.examples.proteinfolding;

import jmarc.modeling.MARCAction;
import jmarc.modeling.MARCState;
import jmarc.modeling.MARCProblem;

import java.util.ArrayList;

public class FoldProtein extends MARCAction {

    private int indexToChange;
    private int newDirection;

    // 0=N, 1=E, 2=S, 3=W

    public boolean satisfiesPreconditions(MARCState s) {
        ArrayList<Integer> moves = ((ProteinState) s).getValue();

        // Non posso assegnare la stessa direzione che c'è già
        if (moves.get(indexToChange) == newDirection)
            return false;

        if (indexToChange > 0) {
            int prev = moves.get(indexToChange - 1);
            if (Math.abs(prev - newDirection) == 2)
                return false;
        }

        if (indexToChange < moves.size() - 1) {
            int next = moves.get(indexToChange + 1);
            if (Math.abs(newDirection - next) == 2)
                return false;
        }

        return true;
    }

    public MARCState evaluateEffects(MARCState s) {
        ArrayList<Integer> newMoves = new ArrayList<>(((ProteinState) s).getValue());
        // Applica la mutazione
        newMoves.set(indexToChange, newDirection);
        return new ProteinState((ProteinFolding2D) this.getActionProblem(), newMoves);
    }

    public double cost(MARCState s) {
        return 0;
    }

    public FoldProtein(int index, int direction, MARCProblem p) {
        super(p, "Fold index " + index + " to dir " + direction);
        this.indexToChange = index;
        this.newDirection = direction;
    }
}
