package jmarc.modeling;


public abstract class MARCInitStateProblem<DimensionType> extends MARCProblem<DimensionType> {

    protected native long createNativeObject(DimensionType dim);

    protected native long createNativeObject(DimensionType dim, String dir);

    public native MARCState getInitialState();

    public native void setInitialState(MARCState s);

    public MARCInitStateProblem(DimensionType dim) {
        super(dim);
    }

    public MARCInitStateProblem(DimensionType dim, String dir) {
        super(dim, dir);
    }

}
