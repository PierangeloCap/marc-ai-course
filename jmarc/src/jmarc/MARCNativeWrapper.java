package jmarc;


import java.lang.ref.Cleaner;
import java.util.*;


public /*abstract*/ class MARCNativeWrapper implements AutoCloseable {

    private long handle;

    private HashSet<MARCNativeWrapper> referencing = new HashSet<>();

    private Cleaner.Cleanable cleanTarget;


    private static final String libraryName = "JMARCNativeInterface";

    private static final Cleaner resourceHandler = Cleaner.create();

    private static native void cleanUp(long handle);

    //public static HashSet<WeakReference<MARCNativeWrapper>> instances = new HashSet<>(); //only for debug


    private void clearDependencies() {
        this.referencing.clear();
    }

    private void registerForCleaning() {
        this.cleanTarget = resourceHandler.register(this, new NativeHandleDisposer(this.handle));
    }

    private static class NativeHandleDisposer implements Runnable {

        private long pointer;

        NativeHandleDisposer(long handle) {
            this.pointer = handle;
        }

        public void run() {
            cleanUp(pointer);
        }

    }


    protected void setHandle(long handle)  {
        assert this.handle == 0;
        this.handle = handle;
        this.registerForCleaning();
    }

    protected void addDependency(MARCNativeWrapper dep) {
        referencing.add(dep);
    }


    public void close() {
        this.cleanTarget.clean();
        this.clearDependencies();
    }

    static {
        System.loadLibrary(libraryName);
    }

}
