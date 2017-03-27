/* HW02_141044039_Doga_UYSAL
 * File:   HW2_141044039_Doga_UYSAL.cpp
 * Author: Doğa
 *
 * Created on 19 Ekim 2015 Pazartesi, 13:58
 */

#include <cstdlib>
#include <iostream>
#include <string.h>

const int STRSIZE = 50;

using namespace std;

class DayOfYear {
public:
    DayOfYear(int _month = 1, int _day = 1);


    void input();
    void setDayOfYear(int monthValue, int dayValue);

    void output() const {
        cout << "Gun : " << day << "  Ay : " << month << endl << endl;
    }

    int getMonth() const {
        return month;
    }

    int getDay() const {
        return day;
    }
private:
    int month;
    int day;
};

typedef struct {
    char name[STRSIZE];
    char surname[STRSIZE];
    DayOfYear birthday;
} person;

int return_mode(const void * base, int numberOfMembers, int sizeOfElem, bool (* equals) (const void *, const void *));
bool compareInt(const void* el1, const void* el2);
bool compareDouble(const void* el1, const void* el2);
bool compareString(const void* el1, const void* el2);
bool compareChar(const void* el1, const void* el2);
bool compareDayOfYear(const void* el1, const void* el2);
bool comparePerson(const void* el1, const void* el2);

int main(int argc, char** argv) {


    int intArr[] = {6, 4, 4, 3, 4, 1};
    int sizeOfInt = 6;
    cout << "intArr mod indexi : " << return_mode(intArr, sizeOfInt, sizeof (int), compareInt) << endl;

    double doubleArr[] = {1.00, 12.00, 1.00, 15.00, 34.00, 55.00, 55.00, 55.00, 54.00, 45.00, 10.00};
    int sizeOfDouble = 11;
    cout << "doubleArr mod indexi : " << return_mode(doubleArr, sizeOfDouble, sizeof (double), compareDouble) << endl;

    char charArr[] = {'a', 'a', 'd', 'd', 'c', 'd', 'd', 'd', 'y', 'j', 'k'};
    int sizeOfChar= 11;
    cout << "charArr mod indexi : " << return_mode(charArr, sizeOfChar, sizeof (char), compareChar) << endl;

    char strArr[5][STRSIZE];
    strcpy(strArr[0], "DarkSouls");
    strcpy(strArr[1], "DarkSouls");
    strcpy(strArr[2], "DemonSouls");
    strcpy(strArr[3], "DemonSouls");
    strcpy(strArr[4], "DarkSouls");
    int sizeOfString = 5;
    cout << "strArr mod indexi: " << return_mode(strArr, sizeOfString, STRSIZE, compareString) << endl;

    person people[8];
    strcpy(people[0].name, "Artorias");    strcpy(people[0].surname, "AbyssWalker");
    strcpy(people[1].name, "Artorias");    strcpy(people[1].surname, "AbyssWalker");
    strcpy(people[2].name, "Sif");         strcpy(people[2].surname, "TheGreatWolf");
    strcpy(people[3].name, "Solaire");     strcpy(people[3].surname, "SunBro");
    strcpy(people[4].name, "Solarie");     strcpy(people[4].surname, "SunBro");
    strcpy(people[5].name, "Gough");       strcpy(people[5].surname, "Hawkeye");
    strcpy(people[6].name, "Sif");         strcpy(people[6].surname, "TheGreatWolf");
    strcpy(people[7].name, "Artorias");    strcpy(people[7].surname, "AbyssWalker");
    int sizeOfPerson = 8;
    cout << "people mod indexi : " << return_mode(people, sizeOfPerson, sizeof (person), comparePerson) << endl;
    
    DayOfYear dayArr[3];
    dayArr[0].setDayOfYear(10, 21);
    dayArr[1].setDayOfYear(3, 6);
    dayArr[2].setDayOfYear(10, 21);
    int sizeOfDayOfTheYear = 3;
    cout << "dayArr mod indexi : " << return_mode(dayArr, sizeOfDayOfTheYear, sizeof (DayOfYear), compareDayOfYear) << endl;

    
    return 0;
}

DayOfYear::DayOfYear(int _month, int _day) {

    setDayOfYear(_month, _day);
}
//DayOfYear class'i icin seter
void DayOfYear::setDayOfYear(int monthValue, int dayValue) {

    month = monthValue;
    day = dayValue;
}
// DayOfYear class'i icin input fonksyonu
void DayOfYear::input() {

    cout << "Gunu ve ayi sirasiyla giriniz :";
    cin >> month >> day;
    cout << endl << endl;
}
// Double degerleri karsilastirarak, esitlerse true return eder
bool compareDouble(const void* el1, const void* el2) {

    double* p1 = (double*) el1;
    double* p2 = (double*) el2;

    if (*p1 == *p2) {
        return true;
    } else
        return false;
}
// integer degerleri karsilastirarak, esitlerse true return eder
bool compareInt(const void* el1, const void* el2) {

    int* p1 = (int*) el1;
    int* p2 = (int*) el2;

    if (*p1 == *p2) {
        return true;
    } else
        return false;
}
// Stringleri karsilastirarak, esitlerse true return eder
bool compareString(const void* el1, const void* el2) {

    char* p1 = (char*) el1;
    char* p2 = (char*) el2;

    if (strcmp(p1, p2) == 0)
        return true;
    else
        return false;
}
// Char degerleri karsilastirarak, esitlerse true return eder
bool compareChar(const void* el1, const void* el2) {

    char* p1 = (char*) el1;
    char* p2 = (char*) el2;

    if (*p1 == *p2)
        return true;
    else
        return false;
}
// Person structure'inin stringlerini ve icinde barindirdigi class yapilarini kasilastirir.
// olusan farkliliga gore return edilen equal degerini ayarlar.
bool comparePerson(const void* el1, const void* el2) {

    person* p1 = (person*) el1;
    person* p2 = (person*) el2;
    bool equal = true;

    if (strcmp(p1->name, p2->name) != 0)
        equal = false;
    if (strcmp(p1->surname, p2->surname) != 0)
        equal = false;
    if (compareDayOfYear(&(p1->birthday), &(p2->birthday)) == false)
        equal = false;

    return equal;
}
//DayOfYear'in barindirdigi objeleri karsilastirarak esitlik durumuna gore equal'u updateler
// ve equal return eder.
bool compareDayOfYear(const void* el1, const void* el2) {

    DayOfYear* p1 = (DayOfYear*) el1;
    DayOfYear* p2 = (DayOfYear*) el2;

    bool equal = true;


    if (p1->getDay() != p2->getDay())
        equal = false;
    if (p1->getMonth() != p2->getMonth())
        equal = false;

    return equal;
}

//tum arayin icinde arama yaparak oncelikle modu bulur. Ardindan modu bulana 
//kadar tekrar tarama yapar ve bulundugu noktanin indexini return eder
int return_mode(const void * base, int numberOfMembers, int sizeOfElem, bool (* equals) (const void *, const void *)) {

    unsigned char* scanElem1 = (unsigned char*) base;
    unsigned char* scanElem2 = (unsigned char*) base + sizeOfElem;
    unsigned char* end = (unsigned char*) base + (sizeOfElem * numberOfMembers);
    unsigned char* tempElemHolder = NULL;
    int frequentCount = 0;
    int maxCount = 0;
    int index = 0;

    for (; scanElem1 < end; scanElem1 += sizeOfElem) {
        frequentCount = 0;
        for (scanElem2 = scanElem1 + sizeOfElem; scanElem2 < end; scanElem2 += sizeOfElem)
            if ((*equals)(scanElem1, scanElem2) == true)
                frequentCount++;

        if (frequentCount > maxCount) {
            maxCount = frequentCount;
            tempElemHolder = scanElem1;
        }
    }

    scanElem1 = (unsigned char*) base;
    for (index = 0; scanElem1 < end; scanElem1 += sizeOfElem, ++index) {
        if ((*equals)(tempElemHolder, scanElem1) == true)
            return index;
    }
}