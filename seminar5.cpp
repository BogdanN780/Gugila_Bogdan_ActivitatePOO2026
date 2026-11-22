
#include<iostream>
#include<string>

using namespace std;

enum TipBiblioteca { UNIVERSITARA = 1, PUBLICA = 2 };

class Biblioteca {
private:
    const int id;
    string denumire;
    TipBiblioteca tip;
    int nrCarti;
    float* vectorPreturi;

public:
    static int nrBiblioteci;

    // Constructor fara parametri
    Biblioteca() :id(++nrBiblioteci) {
        this->denumire = "Biblioteca generala";
        this->nrCarti = 0;
        this->tip = PUBLICA;
        this->vectorPreturi = nullptr;
    }

    // Constructor cu parametri
    Biblioteca(int id, string denumire, TipBiblioteca tip,
        int nrCarti, float* vectorPreturi) :id(id) {

        this->denumire = denumire;
        this->tip = tip;
        this->nrCarti = nrCarti;

        this->vectorPreturi = new float[nrCarti];

        for (int i = 0; i < this->nrCarti; i++) {
            this->vectorPreturi[i] = vectorPreturi[i];
        }

        nrBiblioteci++;
    }

    // Constructor de copiere
    Biblioteca(const Biblioteca& b) :id(++nrBiblioteci) {
        this->denumire = b.denumire;
        this->nrCarti = b.nrCarti;
        this->tip = b.tip;

        if (b.vectorPreturi != nullptr) {
            this->vectorPreturi = new float[b.nrCarti];

            for (int i = 0; i < b.nrCarti; i++) {
                this->vectorPreturi[i] = b.vectorPreturi[i];
            }
        }
        else {
            this->vectorPreturi = nullptr;
        }
    }

    // Operator =
    void operator=(const Biblioteca& b) {
        this->denumire = b.denumire;
        this->nrCarti = b.nrCarti;
        this->tip = b.tip;

        if (this->vectorPreturi != nullptr) {
            delete[] this->vectorPreturi;
            this->vectorPreturi = nullptr;
        }

        if (b.vectorPreturi != nullptr) {
            this->vectorPreturi = new float[b.nrCarti];

            for (int i = 0; i < b.nrCarti; i++) {
                this->vectorPreturi[i] = b.vectorPreturi[i];
            }
        }
        else {
            this->vectorPreturi = nullptr;
        }
    }

    // Metoda de afisare
    void afisareBiblioteca() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;
        cout << endl << "Nr carti: " << this->nrCarti;

        cout << endl << "Tip biblioteca: ";

        if (this->tip == UNIVERSITARA) {
            cout << "UNIVERSITARA";
        }
        else {
            cout << "PUBLICA";
        }

        if (this->nrCarti > 0) {
            cout << endl << "Preturi carti: ";

            for (int i = 0; i < this->nrCarti - 1; i++) {
                cout << this->vectorPreturi[i] << ", ";
            }

            cout << this->vectorPreturi[this->nrCarti - 1] << ".";
        }
    }

    // Getter si setter pentru nrCarti
    int getNrCarti() {
        return this->nrCarti;
    }

    void setNrCarti(int nrCartiNou) {
        if (nrCartiNou >= 0) {
            this->nrCarti = nrCartiNou;
        }
        else {
            throw "Numar negativ de carti!";
        }
    }

    // Getter si setter pentru vectorPreturi
    float* getVectorPreturi() {
        float* vectorPreturiNou = new float[this->nrCarti];

        for (int i = 0; i < this->nrCarti; i++) {
            vectorPreturiNou[i] = this->vectorPreturi[i];
        }

        return vectorPreturiNou;
    }

    void setVectorPreturi(float* vector, int nr) {
        setNrCarti(nr);

        if (this->vectorPreturi != nullptr) {
            delete[] this->vectorPreturi;
        }

        this->vectorPreturi = new float[this->nrCarti];

        for (int i = 0; i < this->nrCarti; i++) {
            this->vectorPreturi[i] = vector[i];
        }

        delete[] vector;
    }

    // Destructor
    ~Biblioteca() {
        if (this->vectorPreturi != nullptr) {
            delete[] this->vectorPreturi;
        }
    }

    // Operator <
    bool operator<(const Biblioteca& b) {
        return this->nrCarti < b.nrCarti;
    }
};

// Initializare atribut static
int Biblioteca::nrBiblioteci = 0;

int main() {
    Biblioteca bibliotecaGenerala;
    bibliotecaGenerala.afisareBiblioteca();

    float* vectorPreturi = new float[3] {35, 27, 41};

    Biblioteca* bibliotecaCentrala =
        new Biblioteca(7, "Biblioteca Centrala",
            UNIVERSITARA, 3, vectorPreturi);

    bibliotecaCentrala->afisareBiblioteca();

    // Constructor de copiere
    Biblioteca bibliotecaPublica = *bibliotecaCentrala;
    bibliotecaPublica.afisareBiblioteca();

    // Operator =
    bibliotecaGenerala = *bibliotecaCentrala;
    bibliotecaGenerala.afisareBiblioteca();

    cout << endl << "Am construit "
        << Biblioteca::nrBiblioteci << " biblioteci!";

    // Operator <
    if (bibliotecaGenerala < bibliotecaPublica) {
        cout << endl << "Biblioteca Generala are mai putine carti!";
    }
    else {
        cout << endl << "Biblioteca Publica are mai putine carti!";
    }

    delete bibliotecaCentrala;
}
