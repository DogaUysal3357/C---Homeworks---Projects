package hw10_141044039_doğa_uysal;

/**
 * Parantezler icin hazirlanmis class.
 * @author Doğa
 */
public class Paranthesis {

    /**
     * İcersinde barindirdigi parantez karakteri.
     */
    private char par;

    /**
     * No Param Cons. ilk atama olarak '(' karakterini atar.
     */
    public Paranthesis() {
        par = '(';
    }

    /**
     * Tek Param Constructor.
     *
     * @param _p. Set'er gönderilen karakter.
     */
    public Paranthesis(char _p) {
        setParanthesis(_p);

    }

    /**
     * Set'er
     *
     * @param _p. Set edilen karakter.
     */
    public void setParanthesis(char _p) {
        par = _p;
    }

    /**
     * Get'er
     *
     * @return par. Parantez karakterini return eder.
     */
    public char getParanthesis() {
        return par;
    }

}
