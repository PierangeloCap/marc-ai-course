import jmarc.modeling.MARCGenericState;
import java.util.ArrayList;


public class QueensBoard extends MARCGenericState<ArrayList<Integer>> {

    public QueensBoard(ArrayList<Integer> b) {
        super(b);
    }

    public QueensBoard(NQueens P, ArrayList<Integer> b) {
        super(P, b);
    }



}
