package hw10_141044039_doğa_uysal;

/**
 * Matematiksel isaretler icin hazirlanmis class.
 *
 * @author Doğa
 */
public class Operator {

    /**
     * Icerinde barindirdigi operator karakteri.
     */
    private char operator;

    /**
     * No Param Constructor.
     */
    public Operator() {
        setOperator('+');
    }

    /**
     * Tek Parametreli Constructor.
     *
     * @param op. Set edilecek karakter.
     */
    public Operator(char op) {
        setOperator(op);
    }

    /**
     * Set'er
     *
     * @param _o. Set edilecek olan karakter
     */
    public void setOperator(char _o) {
        operator = _o;
    }

    /**
     * Get'er
     *
     * @return Operator icersindeki karakteri return eder.
     */
    public char getOperator() {
        return operator;

    }

}
