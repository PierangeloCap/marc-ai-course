package jmarc.solving;


public class MARCFirstChoiceHillClimbing extends MARCAlgorithm {

    protected native long createNativeObject(int maxIdleIterations);

    public MARCFirstChoiceHillClimbing(int maxIdleIterations) {
        assert maxIdleIterations >= 0;
        long handle = this.createNativeObject(maxIdleIterations);
        assert handle != 0;
        this.setHandle(handle);
    }

}
