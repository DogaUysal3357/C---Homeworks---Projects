/*  HW03_141044039_Doğa_UYSAL
 * File:   main.cpp
 * Author: Doğa
 *
 * Created on 29 Ekim 2015 Perşembe, 13:02
 */

#include <iostream>
#include <cstdlib> // exit(1) kullanabilmek icin
#include <cmath> // abs ve sin kullanabilmek icin.
#include <tgmath.h> // acos kullanimi icin.
using namespace std;

class Triangle {
public:
    Triangle();
    Triangle(int _A);
    Triangle(int _A, int _B);
    Triangle(int _A, int _B, int _C);

    int getA() const { return A; }
    int getB() const { return B; }
    int getC() const { return C; }
    void inputTriangle();
    void outputTriangle() const;
    void setA(int valueA) { A = valueA; isValid(); }
    void setB(int valueB) { B = valueB; isValid(); }
    void setC(int valueC) { C = valueC; isValid(); }
private:
    bool isRightAngle() const;
    double areOfTriangle() const;
    int perimeterOfTriangle() const;
    double angleA() const;
    double angleB() const;
    double angleC() const;
    int A;
    int B;
    int C;
    void isValid() const;
};
// Tum kenarlarin uzunluklarini 2 katina cikararak ucgeni büyüklügünü 2'ye katlar
void doubleTheTriangleRef(Triangle &triangle);
// Ucgenin ikizkenar olup olmadigini kontrol eder.
bool isIsoscelesTriangle(Triangle triangle);

int main(int argc, char** argv) {

    Triangle a1, a2, b(2, 2), c(3, 7, 6), d(3, 4, 5);

    // Triangle a3(5); // isValid icin test

    a2.inputTriangle();
    a1.outputTriangle();
    a2.outputTriangle();
    b.outputTriangle();
    c.outputTriangle();
    d.outputTriangle();

    doubleTheTriangleRef(d);
    d.outputTriangle();

    if (isIsoscelesTriangle(b))
        cout << "b ikizkenar ucgendir." << endl;
    else 
        cout << "b ikizkenar ucgen degildir." << endl;

        return 0;
}

Triangle::Triangle() {
    A = 1, B = 1, C = 1;
}

Triangle::Triangle(int _A) {
    A = _A;
    B = 1, C = 1;
    isValid();
}

Triangle::Triangle(int _A, int _B) {
    A = _A, B = _B;
    C = 1;
    isValid();
}

Triangle::Triangle(int _A, int _B, int _C) {
    A = _A, B = _B, C = _C;
    isValid();
}

// Verilen veya girilen ucgenin gecerli olup olmadigini test eder.
// Gecerli degilse exit(1) kullanilarak programdan cikilir

void Triangle::isValid() const {

    if (!(A + B > C && abs(A - B) < C)) {
        cerr << "Gecerli bir ucgen girmediniz.!" << endl << endl;
        exit(1);
    }

}

// Ucgen uzerinde oynama yapilmak istenirse, inputlarin alindigi fonksiyon

void Triangle::inputTriangle() {

    cout << "Ucgenin kose uzunluklarini sirasiyla giriniz ( A - B - C) : ";
    cin >> A >> B >> C;
    isValid();
}

// Tum outputlarin topluca ekrana basildigi fonksyon.

void Triangle::outputTriangle() const {

    cout << "A Kenarinin uzunlugu : " << getA() << endl
            << "A Kosesinin acisi : " << angleA() << endl
            << "B Kenarinin uzunlugu : " << getB() << endl
            << "B Kosesinin acisi : " << angleB() << endl
            << "C Kenarinin uzunlugu : " << getC() << endl
            << "C Kosesinin acisi : " << angleC() << endl
            << "Ucgenin alani : " << areOfTriangle() << endl
            << "Ucgenin cevresi : " << perimeterOfTriangle() << endl
            << "Dik ucgen : ";
    if (isRightAngle())
        cout << "Dogru" << endl << endl;
    else
        cout << "Yanlis" << endl << endl;

}

// A kosesinin acisinin hesaplandigi fonksyon. 
// A kosesinin cos'unun arccos'u alinarak aciya ulasilir.

double Triangle::angleA() const {

    double angle = acos((pow(getA(), 2.0) - pow(getB(), 2.0) - pow(getC(), 2.0)) / ((-2.0) * getC() * getB())) *(180.0 / M_PI);
    return angle;
}
// B kosesinin acisinin hesaplandigi fonksyon. 
// B kosesinin cos'unun arccos'u alinarak aciya ulasilir.

double Triangle::angleB() const {

    double angle = acos((pow(getB(), 2.0) - pow(getA(), 2.0) - pow(getC(), 2.0)) / ((-2.0) * getC() * getA())) *(180.0 / M_PI);
    return angle;
}
// C kosesinin acisinin hesaplandigi fonksyon. 
// C kosesinin cos'unun arccos'u alinarak aciya ulasilir.

double Triangle::angleC() const {

    double angle = acos((pow(getC(), 2.0) - pow(getA(), 2.0) - pow(getB(), 2.0)) / ((-2.0) * getB() * getA())) *(180.0 / M_PI);
    return angle;
}
// Sinus teoremi kullanilarak alan hesaplanir

double Triangle::areOfTriangle() const {

    return (getB() * getC() * sin(angleA() * M_PI / 180.0)) / 2.0;
}
// Tum koseler toplanarak cevre hesaplanir

int Triangle::perimeterOfTriangle() const {

    return getA() + getB() + getC();
}
//  Acilarin 90 derece olup olmadigi kontrol edilir ve eger 90'larsa true return 

bool Triangle::isRightAngle() const {

    if (angleA() == 90 || angleB() == 90 || angleC() == 90)
        return true;
    else
        return false;
}

// Tum kenarlarin uzunluklarini 2 katina cikararak ucgeni büyüklügünü 2'ye katlar
void doubleTheTriangleRef(Triangle& triangle) {
    triangle.setA(triangle.getA()*2);
    triangle.setB(triangle.getB()*2);
    triangle.setC(triangle.getC()*2);
}

// Ucgenin ikizkenar olup olmadigini kontrol eder.
bool isIsoscelesTriangle(Triangle triangle) {

    bool isosceles = false;

    if (triangle.getA() == triangle.getB())
        isosceles = true;
    else if (triangle.getA() == triangle.getC())
        isosceles = true;
    else if (triangle.getC() == triangle.getB())
        isosceles = true;

    return isosceles;
}



