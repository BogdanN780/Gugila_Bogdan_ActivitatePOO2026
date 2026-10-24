
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string nume;
    int varsta;
    double medie;

public:
    // Constructor
    Student(string n, int v, double m) {
        nume = n;
        varsta = v;
        medie = m;
    }

    
    void afiseazaInformatii() {
        cout << "Nume: " << nume << endl;
        cout << "Varsta: " << varsta << endl;
        cout << "Medie: " << medie << endl;
    }

    
    void seteazaMedie(double m) {
        if (m >= 1 && m <= 10) {
            medie = m;
        } else {
            cout << "Media introdusa este invalida!\n";
        }
    }
};

int main() {
    
    Student s1("Andrei", 20, 9.50);

   
    s1.afiseazaInformatii();

    cout << "\nModificam media...\n";
    s1.seteazaMedie(10);

    s1.afiseazaInformatii();

    return 0;
}
