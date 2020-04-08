package jmarc.modeling;

public class MARCGenericState<StateType> extends MARCState {

    private StateType value;

    public StateType getValue() {
        return this.value;
    }

    public boolean equals(MARCState s) {
        try {
            MARCGenericState genericS = (MARCGenericState)s;
            return this.value.equals(genericS.getValue());
        } catch(ClassCastException e) {
            return false;
        }
    }

    public MARCGenericState(MARCProblem p, StateType val) {
        super(p);
        this.value = val;
    }

    public MARCGenericState(StateType val) {
        super();
        this.value = val;
    }

}
