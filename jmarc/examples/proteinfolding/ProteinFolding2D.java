package jmarc.examples.proteinfolding;

import jmarc.modeling.*;
import java.awt.Point;
import java.util.*;

public class ProteinFolding2D extends MARCInitStateProblem<Integer> implements MARCHeuristicProblem, MARCRandomProblem {

    private String sequence;

    // Direzioni: 0=N, 1=E, 2=S, 3=W
    private static final int[] DX = { 0, 1, 0, -1 };
    private static final int[] DY = { 1, 0, -1, 0 };

    public ProteinFolding2D(String sequence) {
        super(sequence.length());
        this.sequence = sequence;
    }

    /**
     * Test di obiettivo: Non esiste uno stato finale valido in questo problema.
     * Si cerca di minimizzare l'energia (euristica).
     */
    public boolean objectiveTest(MARCState s) {
        return false;
    }

    /**
     * Funzione di Energia (Costo).
     * Voglio MINIMIZZARE questo valore.
     * Formula: (Collisioni * 500) - (Contatti H-H * 10)
     */
    public double heuristic(MARCState s) {
        ArrayList<Integer> moves = ((ProteinState) s).getValue();
        List<Point> coords = new ArrayList<>();
        Set<Point> occupied = new HashSet<>();

        int x = 0, y = 0;
        coords.add(new Point(0, 0));
        occupied.add(new Point(0, 0));

        int collisions = 0;

        // Conta Collisioni
        for (int dir : moves) {
            x += DX[dir];
            y += DY[dir];
            Point p = new Point(x, y);

            if (occupied.contains(p)) {
                collisions++;
            } else {
                occupied.add(p);
            }
            coords.add(p);
        }

        // Conta Contatti H-H (Topologici non sequenziali)
        int hContacts = 0;
        for (int i = 0; i < coords.size(); i++) {
            if (sequence.charAt(i) != 'H')
                continue;

            Point p1 = coords.get(i);

            // Controlla tutti gli altri H (j > i+1 per evitare legami covalenti)
            for (int j = i + 2; j < coords.size(); j++) {
                if (sequence.charAt(j) != 'H')
                    continue;

                Point p2 = coords.get(j);
                // Distanza Manhattan = 1 significa adiacenti in griglia
                if (Math.abs(p1.x - p2.x) + Math.abs(p1.y - p2.y) == 1) {
                    hContacts++;
                }
            }
        }

        // PENALITÀ vs PREMI
        // Collisione = +500 (molto male)
        // Contatto H-H = -10 (molto bene, riduce energia)
        return (collisions * 500.0) - (hContacts * 10.0);
    }

    /**
     * Genera tutte le possibili mutazioni valide dallo stato corrente.
     * Per ogni snodo, prova le 3 direzioni alternative.
     */
    public HashSet<FoldProtein> generateAllActions() {
        HashSet<FoldProtein> actions = new HashSet<>();
        int numMoves = sequence.length() - 1;

        // Iteriamo su ogni mossa del cromosoma
        for (int i = 0; i < numMoves; i++) {
            // Proviamo tutte le 4 direzioni cardinali
            for (int dir = 0; dir < 4; dir++) {
                // Le precondizioni dell'azione filtreranno quelle non valide
                FoldProtein action = new FoldProtein(i, dir, this);
                actions.add(action);
            }
        }
        return actions;
    }

    public MARCState getRandomState() {
        Random r = new Random();
        ArrayList<Integer> moves = new ArrayList<>();
        int numMoves = sequence.length() - 1;

        for (int i = 0; i < numMoves; i++) {
            int prevMove = (i > 0) ? moves.get(i - 1) : -99;
            int nextMove;
            do {
                nextMove = r.nextInt(4);
            } while (Math.abs(prevMove - nextMove) == 2);

            moves.add(nextMove);
        }
        return new ProteinState(this, moves);
    }

    public String getSequence() {
        return sequence;
    }
}
