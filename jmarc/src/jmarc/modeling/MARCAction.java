package jmarc.modeling;

import jmarc.MARCNativeWrapper;


public abstract class MARCAction extends MARCNativeWrapper {

    protected native long createNativeObject(MARCProblem p, String label);

    public native MARCProblem getActionProblem();

    // public native void setActionProblem(MARCProblem p);

    abstract public boolean satisfiesPreconditions(MARCState s);

    abstract public MARCState evaluateEffects(MARCState s);

    abstract public double cost(MARCState s);

    public MARCAction(MARCProblem p, String label)  {
        long handle = this.createNativeObject(p, label);
        assert handle != 0;
        this.setHandle(handle);
        this.addDependency(p);
    }

}
