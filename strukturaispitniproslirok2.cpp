#include <iostream>
#include<iomanip>
using namespace std;

char* gettext(char* tekst)
{
    int vel = strlen(tekst) + 1;
    char* kopija = new char[vel];

    strcpy_s(kopija, vel, tekst);
    return kopija;
}
struct Igra {
    char* imeIgre = nullptr;
    char* zanrIgre = nullptr; //dozvoljeni unosi: ["Akcija", "RPG", "Simulacija"]
    char izdavac[40] = "";
    int brojVerzija = 0;
    int brojRecenzenata = 0;
    int** ocjene = nullptr; // matrica dimenzija (brojVerzija * brojRecenzenata)

    void unos()
    {
        char temp[200];

        cout << "Unesi ime igre" << endl;
        cin.getline(temp, 200);
        imeIgre = gettext(temp);

        do
        {
            cout << "Unesi zanr igre" << endl;
            cin.getline(temp, 200);
            if (strcmp("Akcija", temp) != 0)
            {
                cout << "Nije dobar zanr" << endl;
            }
        } while (strcmp("Akcija", temp) != 0);
        zanrIgre = gettext(temp);

        cout << "unesi izdavaca" << endl;
        cin >> izdavac;

        cout << "unesi broj verzija i recenzenata" << endl;
        cin >> brojVerzija >> brojRecenzenata;
        cin.ignore();

        ocjene = new int* [brojVerzija];
        for (int i = 0; i < brojVerzija; i++)
        {
            *(ocjene + i) = new int[brojRecenzenata];
            for (int j = 0; j < brojRecenzenata; j++)
            {
                *(*(ocjene + i) + j) = rand() % 10 + 1;

            }
        }
    }
    float* getAveragesByreviewer()
    {
        float* prosjek = new float[brojRecenzenata];
        for (int j = 0; j < brojRecenzenata; j++)
        {
            float suma = 0;
            for (int i = 0; i < brojVerzija; i++)
            {
                suma += *(*(ocjene + i) + j);
            }
            *(prosjek + j) = suma / brojVerzija;
        }

        return prosjek;
    }

    float* getaveragebyversion()
    {
        float* prosjek = new float[brojVerzija];

        for (int i = 0; i < brojVerzija; i++)
        {
            float suma = 0;
            for (int j = 0; j < brojRecenzenata; j++)
            {
                suma += *(*(ocjene +i) + j);
            }
            *(prosjek + i) = suma / brojRecenzenata;
        }

        return prosjek;
    }
    void ispis()
    {
        cout << "ime: " << imeIgre;
        cout << endl;
        cout << "zanr: " << zanrIgre;
        cout << endl;
        cout << "izdavac: " << izdavac;
        cout << endl;
        cout << "broj verzija i recenzenata: " << brojVerzija << " i " << brojRecenzenata << endl;

        for (int i = 0; i < brojVerzija; i++)
        {
            cout << "verzija " << i + 1 << ": ";
            for (int j = 0; j < brojRecenzenata; j++)
            {
                cout << "recenzent " << j + 1 << ": " << setw(3) << *(*(ocjene + i) + j) << " |";

            }
            cout << endl;
        }
    }
    void dealokacija()
    {
        delete[]imeIgre;
        delete[]zanrIgre;

        imeIgre = nullptr;
        zanrIgre = nullptr;

        for (int i = 0; i < brojVerzija; i++)
        {
            delete[] * (ocjene + i);
            *(ocjene + i) = nullptr;
        }
        delete[]ocjene;
        ocjene = nullptr;
    }
};
int main()
{
    srand(time(0));
    int vel;
    cin >> vel;
    cin.ignore();
    Igra* igra = new Igra[vel];
    for (int i = 0; i < vel; i++)
    {
        (igra + i)->unos();
    }
    for (int i = 0; i < vel; i++)
    {
        (igra + i)->ispis();
    }
    float* prosjekporecenzentu = igra->getAveragesByreviewer();

    for (int i = 0; i < igra->brojRecenzenata; i++)
    {
        cout << "Recenzent " << i + 1 << " prosjek: " << *(prosjekporecenzentu + i)<<endl;
    }
    float* prosjekpoverziji = igra->getaveragebyversion();
    for (int i = 0; i < igra->brojVerzija; i++)
    {
        cout << "Verzija " << i + 1 << " prosjek: " << *(prosjekpoverziji + i) << endl;
    }
    for (int i = 0; i < vel; i++)
    {
        (igra + i)->dealokacija();
    }
    delete[]prosjekporecenzentu;
    prosjekporecenzentu = nullptr;
    delete[]igra;
    igra = nullptr;
}

