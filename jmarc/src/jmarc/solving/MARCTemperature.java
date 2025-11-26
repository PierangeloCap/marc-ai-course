package jmarc.solving;

import jmarc.MARCNativeWrapper;

public abstract class MARCTemperature extends MARCNativeWrapper {

    protected native long createNativeObject();

    public abstract double temperature(int step);

    public MARCTemperature() {
        long handle = this.createNativeObject();
        assert handle != 0;
        this.setHandle(handle);
    }

}
