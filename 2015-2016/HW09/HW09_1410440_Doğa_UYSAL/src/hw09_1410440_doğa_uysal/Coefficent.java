package hw09_1410440_doğa_uysal;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Doğa
 */
public class Coefficent {

    /**
     * katsiyilarin dizisini tutan array. Array icersindeki double'ların x^0'dan
     * x^n'e dogru cikan uslulerin kati oldugu varsayilmistir.
     */
    private double[] coefficent;

    /**
     * No parameter Constructor
     */
    public Coefficent() {
        coefficent = new double[10];
        for (int i = 0; i < 10; ++i) {
            coefficent[i] = 1.0;
        }
    }// No parameter Constructor sonu

    /**
     * Tek parametreli, polinom dizisi uzunlugunu alıp tum katsayılara 1 atayan
     * constructor
     *
     * @param size
     */
    public Coefficent(int size) {
        coefficent = new double[size];
        for (int i = 0; i < size; i++) {
            coefficent[i] = 1;
        }
    }// Tek parametreli constructor sonu

    /**
     *
     * Bir double dizisi alarak onu katsayı dizisi olarak atar ve gonderilen
     * array referansina null atar.
     *
     * @param newCoeff
     */
    public void setCoeff(double[] newCoeff) {
        coefficent = newCoeff;
        newCoeff = null;
    }// setCoeff sonu

    /**
     *
     * Class icinde barindirilan double katsayi arrayini return eder
     *
     * @return
     */
    public double[] getCoeff() {
        return coefficent;
    }// getCoeff sonu

    public double result(int x) {
        double res = 0;
        for (int i = 0; i < coefficent.length; i++) {
            res += coefficent[i] * Math.pow(x, i);
        }
        return res;
    }

    /**
     * Polinomun katsayilarinda toplama yapilir. Gonderilen dizi icerisindeki
     * katsayilarin a0.x^0'dan baslayip an.x^n'e dogru gittigi varsayilarak
     * islem yapilir. Toplamin sonucu classin yeni katsayi dizisi olur ve
     * katsayisi dizisi return edilir.
     *
     * @param addArr
     * @return
     */
    public double[] addCoeff(double[] addArr) {
        if (addArr.length > coefficent.length) {
            for (int i = 0; i < coefficent.length; i++) {
                addArr[i] = coefficent[i] + addArr[i];
            }
            coefficent = addArr;
        } else {
            for (int i = 0; i < addArr.length; i++) {
                coefficent[i] = coefficent[i] + addArr[i];
            }
        }
        return coefficent;
    }// addCoeff sonu

    /**
     * addCoeff fonksyonunu, Coefficent classi icin override'lanmis hali.
     *
     * @param addCo
     * @return coefficent
     */
    public double[] addCoeff(Coefficent addCo) {
        if ((addCo.getCoeff()).length > coefficent.length) {
            for (int i = 0; i < coefficent.length; i++) {
                (addCo.getCoeff())[i] = coefficent[i] + (addCo.getCoeff())[i];
            }
            coefficent = (addCo.getCoeff());
        } else {
            for (int i = 0; i < (addCo.getCoeff()).length; i++) {
                coefficent[i] = coefficent[i] + (addCo.getCoeff())[i];
            }
        }
        return coefficent;

    }// addCoeff sonu

    /**
     * Cikarilan dizi eksi ile carpilip toplama islemi yapilir.
     *
     * @param subArr
     * @return
     */
    public double[] subCoeff(double[] subArr) {
        if (subArr.length > coefficent.length) {
            for (int i = 0; i < coefficent.length; i++) {
                subArr[i] = coefficent[i] - subArr[i];
            }
            coefficent = subArr;
        } else {
            for (int i = 0; i < subArr.length; i++) {
                coefficent[i] = coefficent[i] - subArr[i];
            }
        }
        return coefficent;
    }// subCoeff sonu

    /**
     * Cikarilan dizi eksi ile carpilip toplama islemi yapilir.
     *
     * @param subCo
     * @return
     */
    public double[] subCoeff(Coefficent subCo) {
        if ((subCo.getCoeff()).length > coefficent.length) {
            for (int i = 0; i < coefficent.length; i++) {
                (subCo.getCoeff())[i] = coefficent[i] - (subCo.getCoeff())[i];
            }
            coefficent = (subCo.getCoeff());
        } else {
            for (int i = 0; i < (subCo.getCoeff()).length; i++) {
                coefficent[i] = coefficent[i] - (subCo.getCoeff())[i];
            }
        }
        return coefficent;

    }// subCoeff sonu

    /**
     * Coefficent objesinin string gosterimi
     *
     * @return
     */
    public String toString() {

        String temp = "";
        for (int i = 0; i < coefficent.length; i++) {
            temp += "(" + String.valueOf(coefficent[i] + ")" + "x^" + String.valueOf(i) + " + ");
        }

        return String.format("Polinomunuz : \n%s \n ", temp);
    }// toString sonu

    /**
     * * Coefficent objesinin karsilastirma fonksyonu
     *
     * @param obj
     * @return
     */
    @Override
    public boolean equals(Object obj) {
        boolean answer = true;
        if (obj instanceof Coefficent) {

            Coefficent test = (Coefficent) obj;

            if ((test.getCoeff()).length == coefficent.length) {
                for (int i = 0; i < coefficent.length; i++) {
                    if ((test.getCoeff())[i] != coefficent[i]) {
                        answer = false;
                    }
                }

            } else {
                answer = false;
            }
        }

        return answer;
    } // equals sonu

}// Coefficent class sonu

