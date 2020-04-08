package jmarc.modeling;

import jmarc.MARCNativeWrapper;

import java.util.HashSet;


public abstract class MARCProblem<DimensionType> extends MARCNativeWrapper {

    protected native long createNativeObject(DimensionType dim);

    protected native long createNativeObject(DimensionType dim, String dir);

    // public native HashSet<MARCAction> getPossibleActions(MARCState s);

    public abstract boolean objectiveTest(MARCState s);

    // public enum OptDirection { MIN, MAX }

    public MARCProblem(DimensionType dim) {
        long handle = this.createNativeObject(dim);
        assert handle != 0;
        this.setHandle(handle);
    }

    public MARCProblem(DimensionType dim, String dir) {
        assert dir.equals("MIN") || dir.equals("MAX");
        long handle = this.createNativeObject(dim, dir);
        assert handle != 0;
        this.setHandle(handle);
    }

}
