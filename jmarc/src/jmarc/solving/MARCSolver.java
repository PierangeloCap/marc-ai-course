package jmarc.solving;

import jmarc.MARCNativeWrapper;
import jmarc.modeling.MARCProblem;
import jmarc.modeling.MARCSolution;


public abstract class MARCSolver extends MARCNativeWrapper {

    public native MARCProblem getSolverProblem();

    public native void setSolverProblem(MARCProblem p);

    public native void scheduleAlgorithm(MARCAlgorithm alg, int exec, boolean alwaysReInit);

    public native void setMonitor(MARCSolverMonitor mon);

    public abstract MARCSolution solve();

    // public MARCSolver(MARCProblem p) { this.setSolverProblem(p); }

}
