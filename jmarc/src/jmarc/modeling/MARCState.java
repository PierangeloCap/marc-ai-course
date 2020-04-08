package jmarc.modeling;

import jmarc.MARCNativeWrapper;


public abstract class MARCState extends MARCNativeWrapper {

    protected native long createNativeObject(MARCProblem p);

    protected native long createNativeObject();

    public native MARCProblem getStateProblem();

    public native void setStateProblem(MARCProblem p);

    abstract public boolean equals(MARCState s);

    public MARCState(MARCProblem p) {
        long handle = this.createNativeObject(p);
        assert handle != 0;
        this.setHandle(handle);
        this.addDependency(p);
    }

    public MARCState() {
        long handle = this.createNativeObject();
        assert handle != 0;
        this.setHandle(handle);
    }

}
