/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw09_1410440_doğa_uysal;

/**
 *
 * @author Doğa
 */
public class coefficent_test {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here

        Coefficent test = new Coefficent();
        Coefficent test1 = new Coefficent(6);
        Coefficent test2 = new Coefficent(3);

        double[] coeff2 = {22, 16, 18, 16};

        test.setCoeff(coeff2);

        System.out.printf("%s", test);

        System.out.printf("%s", test1);

        test1.addCoeff(test2);

        System.out.printf("%s", test1);

        test1.subCoeff(test2);
        test1.subCoeff(test2);
        test1.subCoeff(test2);

        System.out.printf("%s", test1);

    }

}
