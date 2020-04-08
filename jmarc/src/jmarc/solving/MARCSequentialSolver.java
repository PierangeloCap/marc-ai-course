package jmarc.solving;

import jmarc.modeling.MARCProblem;
import jmarc.modeling.MARCSolution;


public class MARCSequentialSolver extends MARCSolver {

    protected native long createNativeObject();

    public native MARCSolution solve();

    public MARCSequentialSolver(MARCProblem p) {
        long handle = this.createNativeObject();
        assert handle != 0;
        this.setHandle(handle);
        this.setSolverProblem(p);
    }

}
