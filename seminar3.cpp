
#include<iostream>
#include<string>

using namespace std;

class Biblioteca {
private:
    const int id;
    string denumire;
    int nrCarti;
    float* vectorPreturi;

public:
    static int nrBiblioteci;

    
    Biblioteca() :id(++nrBiblioteci) {
        this->denumire = "Biblioteca generala";
        this->nrCarti = 0;
        this->vectorPreturi = nullptr;
    }

    
    Biblioteca(int id, string denumire, int nrCarti, float* vectorPreturi)
        :id(id) {

        this->denumire = denumire;
        this->nrCarti = nrCarti;

        this->vectorPreturi = new float[nrCarti];

        for (int i = 0; i < this->nrCarti; i++) {
            this->vectorPreturi[i] = vectorPreturi[i];
        }

        nrBiblioteci++;
    }

    
    void afisareBiblioteca() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;
        cout << endl << "Nr carti: " << this->nrCarti;

        if (this->nrCarti > 0) {
            cout << endl << "Preturi carti: ";

            for (int i = 0; i < this->nrCarti - 1; i++) {
                cout << this->vectorPreturi[i] << ", ";
            }

            cout << this->vectorPreturi[this->nrCarti - 1] << ".";
        }
    }

   
    ~Biblioteca() {
        if (this->vectorPreturi != nullptr) {
            delete[] this->vectorPreturi;
        }
    }
};


int Biblioteca::nrBiblioteci = 0;


int main() {

    Biblioteca bibliotecaGenerala;
    bibliotecaGenerala.afisareBiblioteca();

    float* vectorPreturi = new float[3] {25, 40, 55};

    Biblioteca* bibliotecaCentrala =
        new Biblioteca(7, "Biblioteca Centrala", 3, vectorPreturi);

    bibliotecaCentrala->afisareBiblioteca();

    delete[] vectorPreturi;

    delete bibliotecaCentrala;

    cout << endl << "Am construit "
         << Biblioteca::nrBiblioteci << " biblioteci!";

    return 0;
}
