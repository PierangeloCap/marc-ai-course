package jmarc.examples.proteinfolding;

import jmarc.modeling.MARCState;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

public class ProteinGeneticSolver {

    private ProteinFolding2D problem;
    private int populationSize;
    private double mutationRate;
    private double crossoverRate;
    private int maxGenerations;
    private int elitismCount;
    private Random random;

    public ProteinGeneticSolver(ProteinFolding2D problem, int popSize, double mutRate, double crossRate, int maxGen,
            int elitism) {
        this.problem = problem;
        this.populationSize = popSize;
        this.mutationRate = mutRate;
        this.crossoverRate = crossRate;
        this.maxGenerations = maxGen;
        this.elitismCount = elitism;
        this.random = new Random();
    }

    /**
     * Esegue l'algoritmo genetico
     * 
     * @return
     */
    public MARCState solve() {
        // 1. Inizializzazione Popolazione
        List<MARCState> population = new ArrayList<>();
        for (int i = 0; i < populationSize; i++) {
            population.add(problem.getRandomState());
        }

        MARCState bestGlobalState = population.get(0);
        double bestGlobalEnergy = problem.heuristic(bestGlobalState);

        // Ciclo Generazionale
        for (int gen = 0; gen < maxGenerations; gen++) {

            // Ordino per energia (dal più basso al più alto, poiché vogliamo minimizzare
            // l'energia)
            population.sort(Comparator.comparingDouble(s -> problem.heuristic(s)));

            // Controllo se abbiamo un nuovo best
            MARCState currentBest = population.get(0);
            double currentEnergy = problem.heuristic(currentBest);

            if (currentEnergy < bestGlobalEnergy) {
                bestGlobalEnergy = currentEnergy;
                bestGlobalState = currentBest;
                System.out.println("Gen " + gen + " New Best Energy: " + bestGlobalEnergy);
            }

            // Creazione nuova generazione
            List<MARCState> newPopulation = new ArrayList<>();

            // I migliori invariati
            for (int i = 0; i < elitismCount && i < populationSize; i++) {
                newPopulation.add(population.get(i));
            }

            // Riproduzione
            while (newPopulation.size() < populationSize) {
                // Selezione
                MARCState parent1 = tournamentSelection(population);
                MARCState parent2 = tournamentSelection(population);

                MARCState child;

                // Crossover
                if (random.nextDouble() < crossoverRate) {
                    child = crossover(parent1, parent2);
                } else {
                    child = parent1; // Nessun crossover, copia diretta
                }

                // Mutazione
                if (random.nextDouble() < mutationRate) {
                    child = mutate(child);
                }

                newPopulation.add(child);
            }

            population = newPopulation;

            if (gen % 100 == 0) {
                System.out.println("Gen " + gen + " Best: " + bestGlobalEnergy);
            }
        }

        return bestGlobalState;
    }

    // --- OPERATORI GENETICI ---

    /**
     * Seleziona un individuo tramite torneo: prende 5 individui a caso e
     * restituisce
     * quello con l'energia più bassa (migliore)
     * 
     * @param population
     * @return
     */
    private MARCState tournamentSelection(List<MARCState> population) {
        int tournamentSize = 5;
        MARCState best = null;
        double bestFit = Double.MAX_VALUE;

        for (int i = 0; i < tournamentSize; i++) {
            MARCState candidate = population.get(random.nextInt(population.size()));
            double fit = problem.heuristic(candidate);
            if (fit < bestFit) {
                bestFit = fit;
                best = candidate;
            }
        }
        return best;
    }

    /**
     * Crossover semplice: taglia a metà e combina le mosse dei due genitori
     * 
     * @param p1
     * @param p2
     * @return
     */
    private MARCState crossover(MARCState p1, MARCState p2) {
        ArrayList<Integer> g1 = ((ProteinState) p1).getValue();
        ArrayList<Integer> g2 = ((ProteinState) p2).getValue();

        int size = g1.size();
        int cutPoint = random.nextInt(size); // Punto di taglio casuale

        ArrayList<Integer> newMoves = new ArrayList<>();

        // Prima parte dal genitore 1
        for (int i = 0; i < cutPoint; i++) {
            newMoves.add(g1.get(i));
        }
        // Seconda parte dal genitore 2
        for (int i = cutPoint; i < size; i++) {
            newMoves.add(g2.get(i));
        }

        return new ProteinState(problem, newMoves);
    }

    /**
     * Mutazione semplice: cambia casualmente la direzione di una mossa
     * 
     * @param s
     * @return
     */
    private MARCState mutate(MARCState s) {
        ArrayList<Integer> moves = new ArrayList<>(((ProteinState) s).getValue());
        int index = random.nextInt(moves.size());

        // Genera nuova direzione (0-3)
        int currentDir = moves.get(index);
        int newDir;

        do {
            newDir = random.nextInt(4);
        } while (newDir == currentDir);

        moves.set(index, newDir);
        return new ProteinState(problem, moves);
    }
}