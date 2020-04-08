package jmarc.modeling;

import jmarc.MARCNativeWrapper;

public class MARCSolution extends MARCNativeWrapper {

    protected native long createNativeObject(MARCState s);

    public native MARCState getStateSolution();

    // public native void setStateSolution(MARCState s);

    public MARCSolution(MARCState s) {
        long handle = this.createNativeObject(s);
        assert handle != 0;
        this.setHandle(handle);
        this.addDependency(s);
    }

}
