package hw10_141044039_doğa_uysal;

/**
 * Integer icin hazirlanmis class.
 *
 * @author Doğa
 */
public class Operand {

    /**
     * Operand'in icinde tasidigi integer deger.
     */
    private int opInt;

    /**
     * No Parameter constructor.
     */
    public Operand() {
        setOperand(0);
    }

    /**
     * Tek Paremetreli Constructor.
     *
     * @param opInt. Operand'in icine atanacak olan integer deger.
     */
    public Operand(int opInt) {
        setOperand(opInt);
    }

    /**
     * Set'er.
     *
     * @param _i. Set edilen integer deger.
     */
    public void setOperand(int _i) {
        opInt = _i;
    }

    /**
     * get'er.
     *
     * @return opInt. Icinde barindirdigi integer degeri return eder.
     */
    public int getOperand() {
        return opInt;
    }
}
