package hw10_141044039_doğa_uysal;

/**
 * 
 * @author Doğa No : 141044039
 */
import java.util.Vector;
import java.util.Scanner;

/**
 * Expression'in kullanidan alinip, islemi hesaplayan class.
 * @author Doğa
 */
public class Expressions {

    /**
     * Girilen tum expression'i icinde barindiran string.
     */
    private String wholeexp;

    /**
     * Expression dizisinin tutuldugu obje vectoru.
     */
    private Vector expVec;

    /**
     * No Param Constructor. wholeexp string'ine " " atar. expVec'e ici bos
     * 10luk yer hazirlar.
     */
    public Expressions() {
        wholeexp = " ";
        expVec = new Vector<Object>();
    }

    /**
     * Inputlarin teker teker kontrollu sekilde alinip, expVec vectorune
     * atandigi fonksyon. Integer'in ardindan tekrar bir integer girilmedigi
     * surece sorunsuz sekilde calismaktadir. Atama bittikten sonra answer ve
     * calculate fonksyonlari cagirarak sonucu ekrana basar.
     */
    public void takeExpressionAndCalculate() {

        String test = " "; // Inputlarin alinip uzerinde test yapildigi string.
        String last = test; // test ile karsilastirilan ve girdilerin duzgunlugunun konrolunu saglayan string
        int testInt = 0; // Girilen integer icin kullanilan degisken.
        Vector expTest = new Vector<Object>();
        expTest.add(new Paranthesis('('));
        System.out.println("Enter your expresion, after each operator or operand press enter, to end the expression =");
        Scanner input = new Scanner(System.in);

        //  = karakteri girilene kadar teker teker expresion alinir. Onceki alinan expression ile karsilastirilir. 
        //Her girdi gerekli obje'ye donusturulerek expVec'in icine koyulur
        while (test.charAt(test.length() - 1) != '=') {
            System.out.println("Enter your expression element :");
            test = input.nextLine();

            if (test.charAt(test.length() - 1) == '(' || test.charAt(test.length() - 1) == ')') {
                if (((expTest.get(expTest.size() - 1) instanceof Operand) && test.charAt(test.length() - 1) == '(') || ((expTest.get(expTest.size() - 1) instanceof Operator) && test.charAt(test.length() - 1) == ')') || (last.charAt(last.length() - 1) == ')')) {
                    System.out.println("Your input '" + test + "' is not valid. Try Again.");
                } else {
                    Paranthesis par = new Paranthesis(test.charAt(test.length() - 1));
                    expVec.add(par);
                    expTest.add(par);
                    wholeexp += test;
                }
            } else if (test.charAt(test.length() - 1) == '+' || test.charAt(test.length() - 1) == '-' || test.charAt(test.length() - 1) == '*' || test.charAt(test.length() - 1) == '/') {
                if (expTest.get(expTest.size() - 1) instanceof Operator) {
                    System.out.println("Your input '" + test + "' is not valid. Try Again.");
                } else {
                    Operator op = new Operator(test.charAt(test.length() - 1));
                    expVec.add(op);
                    expTest.add(op);
                    wholeexp += test;
                }
            } else if (test.charAt(test.length() - 1) == '=') {
                // integer kontrolde yakalanmasin diye yazilmis ve bilrek bos birakilmistir.
            } else {
                if (expTest.get(expTest.size() - 1) instanceof Operand) {
                    System.out.println("Your input '" + test + "' is not valid. Try Again.");
                } else {
                    try {
                        testInt = Integer.parseInt(test);
                        Operand op = new Operand(testInt);
                        expVec.add(op);
                        expTest.add(op);
                        wholeexp += test;
                    } catch (NumberFormatException e) {
                        System.out.println("Your input '" + test + "' is not valid. Try Again.");
                    }
                }
            }
            last = test;
        }
        answer(calculate());
    }

    /**
     * Matematiksel islemin hesaplandigi func.
     * Baslangic olarak tum expression'in parantez icine alinir. Ardindan ilk
     * parantez kapama karakterinden geriye dogru gidilerek ilk parantez acma
     * karakteri bulunur. Iki parantez karakteri icersinde kalan matematiksel
     * islemler yapilir. Herhangi bir islem yapildiktan sonra Operator ve
     * sagdaki Operand vector'dan atilir. Sonuc soldaki Operand'a atanir.
     * Her parantez ikilisi ici temizlendikten sonra ekrana basilir.
     *
     * @return Sonuc int olarak return edilir.
     */
    public int calculate() {

        Paranthesis parAdd1 = new Paranthesis('(');
        expVec.add(0, parAdd1);
        Paranthesis parAdd2 = new Paranthesis(')');
        expVec.add(parAdd2);

        int firstParIndex;

        System.out.println(wholeexp);

        for (int endParIndex = 0; endParIndex < expVec.size(); ++endParIndex) {
            if (expVec.get(endParIndex) instanceof Paranthesis) {
                Paranthesis par = (Paranthesis) expVec.get(endParIndex);

                if (par.getParanthesis() == ')') {
                    firstParIndex = endParIndex;
                    firstParIndex--;

                    while (!(expVec.get(firstParIndex) instanceof Paranthesis)) {
                        firstParIndex--;
                    }

                    for (int i = firstParIndex + 2; i < endParIndex; ++i) {
                        if (expVec.get(i) instanceof Operator) {
                            Operator op = (Operator) expVec.get(i);
                            if (op.getOperator() == '*') {
                                Operand first = (Operand) expVec.get(i - 1);
                                Operand second = (Operand) expVec.get(i + 1);
                                first.setOperand(first.getOperand() * second.getOperand());
                                expVec.remove(i);
                                expVec.remove(i);
                                endParIndex--;
                                endParIndex--;
                            }
                        }

                    }

                    for (int i = firstParIndex + 2; i < endParIndex; ++i) {
                        if (expVec.get(i) instanceof Operator) {
                            Operator op = (Operator) expVec.get(i);
                            if (op.getOperator() == '/') {
                                Operand first = (Operand) expVec.get(i - 1);
                                Operand second = (Operand) expVec.get(i + 1);
                                first.setOperand(first.getOperand() / second.getOperand());
                                expVec.remove(i);
                                expVec.remove(i);
                                endParIndex -= 2;
                            }
                        }

                    }

                    for (int i = firstParIndex + 2; i < endParIndex; ++i) {
                        if (expVec.get(i) instanceof Operator) {
                            Operator op = (Operator) expVec.get(i);
                            if (op.getOperator() == '+') {
                                Operand first = (Operand) expVec.get(i - 1);
                                Operand second = (Operand) expVec.get(i + 1);
                                first.setOperand(first.getOperand() + second.getOperand());
                                expVec.remove(i);
                                expVec.remove(i);
                                endParIndex -= 2;
                            }
                        }

                    }

                    for (int i = firstParIndex + 2; i < endParIndex; ++i) {
                        if (expVec.get(i) instanceof Operator) {
                            Operator op = (Operator) expVec.get(i);
                            if (op.getOperator() == '-') {
                                Operand first = (Operand) expVec.get(i - 1);
                                Operand second = (Operand) expVec.get(i + 1);
                                first.setOperand(first.getOperand() - second.getOperand());
                                expVec.remove(i);
                                expVec.remove(i);
                                endParIndex -= 2;
                            }
                        }

                    }

                    expVec.remove(endParIndex);
                    expVec.remove(firstParIndex);

                    for (int i = 0; i < expVec.size(); ++i) {
                        if (expVec.get(i) instanceof Operator) {
                            Operator op = (Operator) expVec.get(i);
                            System.out.printf("%c", op.getOperator());
                        }
                        if (expVec.get(i) instanceof Operand) {
                            Operand op = (Operand) expVec.get(i);
                            System.out.printf("%d", op.getOperand());
                        }
                        if (expVec.get(i) instanceof Paranthesis) {
                            Paranthesis op = (Paranthesis) expVec.get(i);
                            System.out.printf("%c", op.getParanthesis());
                        }
                    }
                    System.out.println();

                }
            }

        }

        int resultInt = 0;
        if (expVec.get(0) instanceof Operand) {
            Operand result = (Operand) expVec.get(0);
            resultInt = result.getOperand();
        }

        return resultInt;
    }

    /**
     * Tum islemi, yani wholeexp stringini ekrana basar. Ardindan Input olarak
     * alinan sonucu ekrana basar.
     *
     * @param a. Ekrana basilacak sonuc (integer).
     */
    public void answer(int a) {

        System.out.printf("Result : \n%s = %d\n", wholeexp, a);

    }

    @Override
    public String toString() {
        Operand result = (Operand) expVec.get(0);
        return String.format("Result : %d\n", result.getOperand());
    }

    @Override
    public boolean equals(Object obj) {
        Expressions compared = (Expressions) obj;
        if (compared.calculate() == calculate()) {
            return true;
        } else {
            return false;
        }

    }

}
