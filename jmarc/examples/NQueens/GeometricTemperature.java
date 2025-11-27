import jmarc.solving.MARCTemperature;

public class GeometricTemperature extends MARCTemperature {

    private double initialTemp;
    private double alpha;

    public GeometricTemperature(double initialTemp, double alpha) {
        super();
        this.initialTemp = initialTemp;
        this.alpha = alpha;
    }

    @Override
    public double temperature(int step) {
        // Formula: T_corrente = T_iniziale * (alpha ^ numero_step)
        return initialTemp * Math.pow(alpha, step);
    }
}
