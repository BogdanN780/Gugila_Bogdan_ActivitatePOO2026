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

        if (this->nrCarti > 0 && this->vectorPreturi != nullptr) {
            cout << endl << "Preturi carti: ";

            for (int i = 0; i < this->nrCarti - 1; i++) {
                cout << this->vectorPreturi[i] << " lei, ";
            }

            cout << this->vectorPreturi[this->nrCarti - 1] << " lei.";
        }
    }

  
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

    
    float* getVectorPreturi() {
        if (this->vectorPreturi == nullptr) {
            return nullptr;
        }

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
            this->vectorPreturi = nullptr;
        }

        if (this->nrCarti > 0) {
            this->vectorPreturi = new float[this->nrCarti];

            for (int i = 0; i < this->nrCarti; i++) {
                this->vectorPreturi[i] = vector[i];
            }
        }
        else {
            this->vectorPreturi = nullptr;
        }

        delete[] vector;
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

    
    try {
        bibliotecaGenerala.setNrCarti(2);
    }
    catch (int cod) {
        cout << endl << cod;
    }
    catch (const char* mesaj) {
        cout << endl << mesaj;
    }
    catch (...) {
        cout << endl << "Numar negativ de carti!";
    }

    cout << endl << "Noul numar de carti este: "
        << bibliotecaGenerala.getNrCarti();

   
    bibliotecaGenerala.setVectorPreturi(
        new float[3] {28.5, 35.4, 42.7}, 3);

    // Testare getter vectorPreturi
    float* vector = bibliotecaGenerala.getVectorPreturi();

    cout << endl << "Noile preturi sunt: ";

    for (int i = 0; i < bibliotecaGenerala.getNrCarti(); i++) {
        cout << vector[i] << " lei, ";
    }

    bibliotecaGenerala.afisareBiblioteca();

    delete[] vector;

    
    float* vectorPreturi = new float[3] {20, 30, 45};

    Biblioteca* bibliotecaCentrala =
        new Biblioteca(7, "Biblioteca Centrala", 3, vectorPreturi);

    delete[] vectorPreturi;

    bibliotecaCentrala->afisareBiblioteca();

    delete bibliotecaCentrala;

    cout << endl << "Am construit "
        << Biblioteca::nrBiblioteci << " biblioteci!";

    return 0;
}
