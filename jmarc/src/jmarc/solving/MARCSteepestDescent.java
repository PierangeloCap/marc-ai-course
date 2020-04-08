package jmarc.solving;


public class MARCSteepestDescent extends MARCAlgorithm {

    protected native long createNativeObject();

    public MARCSteepestDescent() {
        long handle = this.createNativeObject();
        assert handle != 0;
        this.setHandle(handle);
    }

}
