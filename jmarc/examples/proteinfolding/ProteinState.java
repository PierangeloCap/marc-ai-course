package jmarc.examples.proteinfolding;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import jmarc.modeling.MARCGenericState;

public class ProteinState extends MARCGenericState<ArrayList<Integer>> {

    public ProteinState(ArrayList<Integer> moves) {
        super(moves);
    }

    public ProteinState(ProteinFolding2D p, ArrayList<Integer> moves) {
        super(p, moves);
    }

    @Override
    public String toString() {
        try {
            // Recupera la sequenza dal problema
            ProteinFolding2D problem = (ProteinFolding2D) this.getStateProblem();
            String sequence = problem.getSequence();
            ArrayList<Integer> moves = this.getValue();

            // Mappe per le direzioni (0=N, 1=E, 2=S, 3=W)
            int[] dx = { 0, 1, 0, -1 };
            int[] dy = { 1, 0, -1, 0 };

            // Mappa coordinate -> carattere (H o P)
            // Uso una Stringa "x,y" come chiave
            Map<String, String> grid = new HashMap<>();

            int x = 0;
            int y = 0;
            int minX = 0, maxX = 0, minY = 0, maxY = 0;

            // Posiziona il primo amminoacido
            grid.put(x + "," + y, formatAA(sequence.charAt(0), true)); // true = start

            // Calcola le posizioni degli altri
            for (int i = 0; i < moves.size(); i++) {
                int dir = moves.get(i);
                x += dx[dir];
                y += dy[dir];

                // Aggiorna i confini
                minX = Math.min(minX, x);
                maxX = Math.max(maxX, x);
                minY = Math.min(minY, y);
                maxY = Math.max(maxY, y);

                char aa = sequence.charAt(i + 1);
                boolean isEnd = (i == moves.size() - 1);
                grid.put(x + "," + y, formatAA(aa, isEnd));
            }

            // Costruisce la stringa finale
            StringBuilder sb = new StringBuilder();
            sb.append("\n--- PROTEIN SHAPE ---\n");

            // Cicla dall'alto (MaxY) al basso (MinY)
            for (int r = maxY; r >= minY; r--) {
                for (int c = minX; c <= maxX; c++) {
                    String key = c + "," + r;
                    if (grid.containsKey(key)) {
                        sb.append(grid.get(key));
                    } else {
                        sb.append(" . ");
                    }
                }
                sb.append("\n");
            }
            sb.append("Moves: ").append(moves.toString()).append("\n");

            return sb.toString();

        } catch (Exception e) {
            return "ProteinState: " + this.getValue().toString();
        }
    }

    private String formatAA(char aa, boolean isSpecial) {
        if (aa == 'H') {
            return "[H]"; // Idrofobico
        } else {
            return "[P]"; // Polare
        }
    }
}
