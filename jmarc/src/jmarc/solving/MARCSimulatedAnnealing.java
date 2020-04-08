package jmarc.solving;


public class MARCSimulatedAnnealing extends MARCAlgorithm {

    protected native long createNativeObject(int maxIdleIterations);

    // public native MARCTemperature getTemperature();

    public native void setTemperature(MARCTemperature t);

    public MARCSimulatedAnnealing(MARCTemperature t, int maxIdleIterations) {
        assert maxIdleIterations >= 0;
        long handle = this.createNativeObject(maxIdleIterations);
        assert handle != 0;
        this.setHandle(handle);
        this.setTemperature(t);
        this.addDependency(t);
    }

}
