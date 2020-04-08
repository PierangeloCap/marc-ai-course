package jmarc.solving;

import jmarc.MARCNativeWrapper;


public class MARCSolverMonitor extends MARCNativeWrapper {

    protected native long createNativeObject(String name);

    public MARCSolverMonitor(String name) {
        long handle = this.createNativeObject(name);
        assert handle != 0;
        this.setHandle(handle);
    }

}