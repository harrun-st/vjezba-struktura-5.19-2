

#include <iostream>
using namespace std;
char* alocirajTekst(const char* tekst) {
	if (tekst == nullptr) return nullptr;
	int vel = strlen(tekst) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, tekst);
	return novi;
}
struct Jelo {
	char* imeJela = nullptr;
	char* kategorijaJela = nullptr; // dozvoliti unos samo "Tjestenina", "Tradicionalna", "Fast Food"
	char imeKuhara[40] = "";
	int brojVarijacija = 0;
	int brojKriticara = 0;
	int** ocjene = nullptr; // matrica brojVarijacija * brojKriticara

    void unos() {
        char temp[200];

        cout << "Unesite ime jela: ";
        cin.getline(temp, 200);
        imeJela = alocirajTekst(temp);

        // Validacija unosa kategorije jela
        do {
            cout << "Unesite kategoriju jela (Tjestenina, Tradicionalna, Fast Food): ";
            cin.getline(temp, 200);
            if (strcmp(temp, "Tjestenina") != 0 && strcmp(temp, "Tradicionalna") != 0 && strcmp(temp, "Fast Food") != 0) {
                cout << "Greska! Nevazeca kategorija.\n";
            }
        } while (strcmp(temp, "Tjestenina") != 0 && strcmp(temp, "Tradicionalna") != 0 && strcmp(temp, "Fast Food") != 0);
        kategorijaJela = alocirajTekst(temp);

        cout << "Unesite ime kuhara: ";
        cin.getline(imeKuhara, 40);

        cout << "Unesite broj varijacija i broj kriticara: ";
        cin >> brojVarijacija >> brojKriticara;
        cin.ignore();

        // Alokacija matrice ocjena pomoću pokazivačke aritmetike
        ocjene = new int* [brojVarijacija];
        for (int i = 0; i < brojVarijacija; i++) {
            *(ocjene + i) = new int[brojKriticara];
            for (int j = 0; j < brojKriticara; j++) {
                // Random ocjene u rasponu od 1 do 10
                *(*(ocjene + i) + j) = rand() % 10 + 1;
            }
        }
    }

    void ispis() {
        cout << "Ime jela: " << imeJela << endl;
        cout << "Kategorija: " << kategorijaJela << endl;
        cout << "Kuhar: " << imeKuhara << endl;
        cout << "Ocjene (matrica):" << endl;
        for (int i = 0; i < brojVarijacija; i++) {
            for (int j = 0; j < brojKriticara; j++) {
                cout << *(*(ocjene + i) + j) << " ";
            }
            cout << endl;
        }
    }

    void dealokacija() {
        delete[] imeJela;
        imeJela = nullptr;

        delete[] kategorijaJela;
        kategorijaJela = nullptr;

        if (ocjene != nullptr) {
            for (int i = 0; i < brojVarijacija; i++) {
                delete[] * (ocjene + i);
                *(ocjene + i) = nullptr;
            }
            delete[] ocjene;
            ocjene = nullptr;
        }
    }
};
float* getAverageByCategory(Jelo* niz, int velNiza)
{
    float* prosjek = new float[3] {0};

    float* sume = new float[3] {0};
    float* brojac = new float[3] {0};
    for (int k = 0; k < velNiza; k++)
    {
        for (int i = 0; i < (niz+k)->brojVarijacija; i++)
        {
            for (int j = 0; j < (niz+k)->brojKriticara; j++)
            {
                if (strcmp("Tjestenina", (niz + k)->kategorijaJela)==0)
                {
                    *(sume + 0) += *(*(((niz + k)->ocjene) + i) + j);

                    *(brojac + 0) += 1;
                }
                else if (strcmp("Tradicionalna", (niz + k)->kategorijaJela)==0)
                {
                    *(sume + 1) += *(*(((niz + k)->ocjene) + i) + j);

                    *(brojac + 1) += 1;
                }
                else if (strcmp("Fast Food", (niz + k)->kategorijaJela)==0)
                {
                    *(sume + 2) += *(*(((niz + k)->ocjene) + i) + j);

                    *(brojac + 2) += 1;
                }
            }
        }

    }

    for (int i = 0; i < 3; i++)
    {
        if (*(brojac + i) != 0)
            *(prosjek + i) += *(sume + i) / *(brojac + i);
    }

    return prosjek;
}
int main()
{
    int vel;
    cin >> vel;
    cin.ignore();

    Jelo* jelo = new Jelo[vel];

    for (int i = 0; i < vel; i++)
    {
        (jelo + i)->unos();
    }
    for (int i = 0; i < vel; i++)
    {
        (jelo + i)->ispis();
    }

    float* prosjekpokategoriji = getAverageByCategory(jelo, vel);

    cout << "prosjek po tjestenini " << *(prosjekpokategoriji + 0) << endl;
    cout << "prosjek po tradicionalnoj " << *(prosjekpokategoriji + 1) << endl;
    cout << "prosjek po fast food " << *(prosjekpokategoriji + 2) << endl;
    for (int i = 0; i < vel; i++)
    {
        (jelo + i)->dealokacija();
    }

    delete[]prosjekpokategoriji;
    delete[]jelo;
    prosjekpokategoriji = nullptr;
    jelo = nullptr;
}


