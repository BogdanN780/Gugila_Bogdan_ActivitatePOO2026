
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

enum TipSala { MICA = 1, MEDIE = 2, MARE = 3 };

class SalaFitness {
private:
    const int id;
    TipSala tipSala;
    string denumire;
    int nrAbonamente;
    float* preturiAbonamente;

public:
    static int nrSali;

    
    SalaFitness() : id(++nrSali) {
        this->denumire = "Sala fitness generala";
        this->tipSala = MICA;
        this->nrAbonamente = 0;
        this->preturiAbonamente = nullptr;
    }

   
    SalaFitness(int id, string denumire, int nrAbonamente,
        const float* preturiAbonamente, TipSala tipSala) : id(id) {

        nrSali++;

        this->denumire = denumire;
        this->tipSala = tipSala;
        this.nrAbonamente = nrAbonamente;

        if (nrAbonamente > 0 && preturiAbonamente != nullptr) {
            this->preturiAbonamente = new float[nrAbonamente];

            for (int i = 0; i < nrAbonamente; i++) {
                this->preturiAbonamente[i] = preturiAbonamente[i];
            }
        }
        else {
            this->nrAbonamente = 0;
            this->preturiAbonamente = nullptr;
        }
    }

   
    SalaFitness(const SalaFitness& copie) : id(++nrSali) {
        this->denumire = copie.denumire;
        this->tipSala = copie.tipSala;
        this->nrAbonamente = copie.nrAbonamente;

        if (copie.preturiAbonamente != nullptr) {
            this->preturiAbonamente = new float[this->nrAbonamente];

            for (int i = 0; i < this->nrAbonamente; i++) {
                this->preturiAbonamente[i] =
                    copie.preturiAbonamente[i];
            }
        }
        else {
            this->preturiAbonamente = nullptr;
        }
    }

   
    SalaFitness& operator=(const SalaFitness& copie) {
        if (this != &copie) {
            this->denumire = copie.denumire;
            this->tipSala = copie.tipSala;
            this->nrAbonamente = copie.nrAbonamente;

            if (this->preturiAbonamente != nullptr) {
                delete[] this->preturiAbonamente;
                this->preturiAbonamente = nullptr;
            }

            if (copie.preturiAbonamente != nullptr) {
                this->preturiAbonamente =
                    new float[this->nrAbonamente];

                for (int i = 0; i < this->nrAbonamente; i++) {
                    this->preturiAbonamente[i] =
                        copie.preturiAbonamente[i];
                }
            }
        }

        return *this;
    }

 
    int getNrAbonamente() {
        return this->nrAbonamente;
    }

    void setNrAbonamente(int valoareNoua) {
        if (valoareNoua >= 0) {
            float* vectorNou = nullptr;

            if (valoareNoua > 0) {
                vectorNou = new float[valoareNoua];

                for (int i = 0; i < valoareNoua; i++) {
                    if (i < this->nrAbonamente &&
                        this->preturiAbonamente != nullptr) {
                        vectorNou[i] = this->preturiAbonamente[i];
                    }
                    else {
                        vectorNou[i] = 0;
                    }
                }
            }

            if (this->preturiAbonamente != nullptr) {
                delete[] this->preturiAbonamente;
            }

            this->preturiAbonamente = vectorNou;
            this->nrAbonamente = valoareNoua;
        }
        else {
            throw invalid_argument("Numar negativ de abonamente!");
        }
    }

    
    float* getPreturiAbonamente() {
        if (this->preturiAbonamente == nullptr) {
            return nullptr;
        }

        float* vectorPreturi = new float[this->nrAbonamente];

        for (int i = 0; i < this->nrAbonamente; i++) {
            vectorPreturi[i] = this->preturiAbonamente[i];
        }

        return vectorPreturi;
    }

    
    void setPreturiAbonamente(const float* vectorPreturi, int dim) {
        if (dim < 0) {
            throw invalid_argument("Dimensiune negativa!");
        }

        if (dim > 0 && vectorPreturi == nullptr) {
            throw invalid_argument("Vectorul de preturi este nul!");
        }

        float* vectorNou = nullptr;

        if (dim > 0) {
            vectorNou = new float[dim];

            for (int i = 0; i < dim; i++) {
                vectorNou[i] = vectorPreturi[i];
            }
        }

        if (this->preturiAbonamente != nullptr) {
            delete[] this->preturiAbonamente;
        }

        this->preturiAbonamente = vectorNou;
        this->nrAbonamente = dim;
    }

    
    void afisare() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;

        cout << endl << "Tip sala: ";

        if (this->tipSala == MICA) {
            cout << "MICA";
        }
        else if (this->tipSala == MEDIE) {
            cout << "MEDIE";
        }
        else {
            cout << "MARE";
        }

        cout << endl << "Nr. abonamente: " << this->nrAbonamente;

        if (this->nrAbonamente > 0) {
            cout << " cu urmatoarele preturi: ";

            for (int i = 0; i < this->nrAbonamente - 1; i++) {
                cout << this->preturiAbonamente[i] << " lei, ";
            }

            cout << this->preturiAbonamente[this->nrAbonamente - 1]
                 << " lei.";
        }

        cout << endl;
    }

 
    bool operator<(const SalaFitness& s) {
        return this->nrAbonamente < s.nrAbonamente;
    }

    
    ~SalaFitness() {
        cout << endl << "S-a apelat destructorul pentru sala fitness!";

        if (this->preturiAbonamente != nullptr) {
            delete[] this->preturiAbonamente;
        }
    }
};


int SalaFitness::nrSali = 0;


int main() {

   
    SalaFitness salaGenerala;
    salaGenerala.afisare();

    
    float* preturi = new float[3] {150, 250, 350};

    SalaFitness* salaFitness1 = new SalaFitness(
        7, "Fitness Arena", 3, preturi, MARE);

    delete[] preturi;

    salaFitness1->afisare();

   
    SalaFitness* salaFitness2 = new SalaFitness(*salaFitness1);
    salaFitness2->afisare();

   
    salaGenerala = *salaFitness2;
    salaGenerala.afisare();

    SalaFitness salaFitness3;
    salaFitness3 = salaGenerala;
    salaFitness3.afisare();

   
    try {
        salaFitness3.setNrAbonamente(2);
    }
    catch (const exception& e) {
        cout << endl << e.what();
    }

    cout << endl << "Noul numar de abonamente este: "
         << salaFitness3.getNrAbonamente() << endl;

   
    salaFitness3.setPreturiAbonamente(
        new float[2] {180, 300}, 2);

    float* vectorPreturi = salaFitness3.getPreturiAbonamente();

    cout << endl << "Preturile abonamentelor sunt: ";

    for (int i = 0; i < salaFitness3.getNrAbonamente(); i++) {
        cout << vectorPreturi[i] << " lei, ";
    }

    delete[] vectorPreturi;

    
    if (salaFitness3 < salaGenerala) {
        cout << endl << "SalaFitness3 are mai putine abonamente "
             << "decat SalaGenerala!";
    }
    else {
        cout << endl << "SalaGenerala are mai putine abonamente "
             << "decat SalaFitness3!";
    }

   
    try {
        salaFitness3.setNrAbonamente(-2);
    }
    catch (const exception& e) {
        cout << endl << "Exceptie: " << e.what();
    }

    
    delete salaFitness1;
    delete salaFitness2;

    cout << endl << "Numar sali create: "
         << SalaFitness::nrSali;

    return 0;
}

