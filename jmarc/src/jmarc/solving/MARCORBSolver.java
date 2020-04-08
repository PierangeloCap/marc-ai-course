package jmarc.solving;

import jmarc.modeling.MARCProblem;
import jmarc.modeling.MARCSolution;
import jmarc.modeling.MARCState;

import java.util.Vector;


public class MARCORBSolver extends MARCSolver {

    protected native long createNativeObject(int bootstrapSize);

    public native MARCSolution solve();

    public native void addBootstrapState(MARCState s);

    public native void bootstrap();

    public native Vector<MARCState> getBootstrap();

    public MARCORBSolver(MARCProblem p, int bootstrapSize) {
        assert bootstrapSize > 0;
        long handle = this.createNativeObject(bootstrapSize);
        assert handle != 0;
        this.setHandle(handle);
        this.setSolverProblem(p);
    }

}
