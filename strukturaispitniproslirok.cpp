#include <iostream>
using namespace std;

char* gettext(char* tekst)
{
    int vel = strlen(tekst) + 1;
    char* kopija = new char[vel];
    strcpy_s(kopija, vel, tekst);
    return kopija;

}
struct Avion {
    char* imeAviona = nullptr;
    char* kategorijaAviona = nullptr; //dozvoliti unos samo "Borbeni Avion", "Putnicki Avion", "Kargo Avion"
    char proizvodacAviona[40] = "";
    int brojSerija = 0;
    int brojPilota = 0;
    int** ocjene = nullptr; // matrica dimenzija (brojSerija * brojPilota)

    void unos()
    {
        char temp[200];
        cout << "Unesi ime aviona" << endl;
        cin.getline(temp, 200);
        imeAviona = gettext(temp);


        do {
            cout << "Unesi kategoriju" << endl;
            cin.getline(temp, 200);
            if (strcmp("Borbeni Avion", temp) != 0)
            {
                cout << "ponovo nije to to" << endl;
            }
        } while (strcmp("Borbeni Avion", temp) != 0);
        kategorijaAviona = gettext(temp);
        cout << "Unesi proizvodjaca" << endl;
        cin.getline(proizvodacAviona, 40);

        cout << "broj serija i pilota" << endl;
        cin >> brojSerija >> brojPilota;
        cin.ignore();

        ocjene = new int* [brojSerija];
        for (int i = 0; i < brojSerija; i++)
        {
            *(ocjene + i) = new int[brojPilota];
            for (int j = 0; j < brojPilota; j++)
            {
                *(*(ocjene + i) + j) = rand() % 10 + 1;
            }
        }
    }
    float* getAveragesBySeries()
    {
        float* prosjek=new float[brojSerija]{ 0 };

        
        for (int i = 0; i < brojSerija; i++)
        {
            float suma = 0;
            for (int j = 0; j < brojPilota; j++)
            {
                suma += *(*(ocjene + i) + j);
            }
            *(prosjek + i) = suma / brojPilota;
        }
        return prosjek;

    }
    float* getAverageByDiagonal()
    {
        float* prosjecidijagonale=new float[2]{ 0 };
        float sumaglavne = 0;
        float sumasporedne = 0;

        for (int i = 0; i < brojSerija; i++)
        {
           
            for (int j = 0; j < brojPilota; j++)
            {
                if (i == j)
                {
                    sumaglavne += *(*(ocjene + i) + j);
                }
            }
         
        }
        for (int i = 0; i < brojSerija; i++)
        {
            
            for (int j = 0; j < brojPilota; j++)
            {
                if (i+j ==brojSerija-1)
                {
                    sumasporedne += *(*(ocjene + i) + j);
                }
            }

        }

        *(prosjecidijagonale) = sumaglavne / brojSerija;
        *(prosjecidijagonale + 1) = sumasporedne / brojSerija;

            return prosjecidijagonale;
    }
    void ispis()
    {
        cout << "ime: " << imeAviona << endl;
        cout << "kategorija: " << kategorijaAviona << endl;
        cout << "proizvodjac: " << proizvodacAviona << endl;
        cout << "broj serija i pilota" << endl;
        for (int i = 0; i < brojSerija; i++)
        {
            cout << "Serija " << i + 1 << ": ";
            for (int j = 0; j < brojPilota; j++)
            {
                cout <<"pilot: "<< * (*(ocjene + i) + j) << " |";
            }
            cout << endl;
        }
    }
    void dealokacije()
    {
        delete[]imeAviona;
        delete[]kategorijaAviona;
        imeAviona = nullptr;
        kategorijaAviona = nullptr;

        for (int i = 0; i < brojSerija; i++)
        {
            delete[] * (ocjene + i);
        }
        delete[]ocjene;
        ocjene = nullptr;
    }
};
int main()
{
    int vel;
    cin >> vel;
    cin.ignore();
    Avion* avion = new Avion[vel];

    for (int i = 0; i < vel; i++)
    {
        (avion + i)->unos();
    }
    for (int i = 0; i < vel; i++)
    {
        (avion + i)->ispis();
    }
    float* prosjekposeriji = (*avion).getAveragesBySeries();

    for (int i = 0; i < avion->brojSerija; i++)
    {
        cout << "Prosjek za seriju " << i + 1 << ": " << *(prosjekposeriji + i) << endl; 
    }

    float* prosjekpodijagonalama = (*avion).getAverageByDiagonal();

    cout << "prosjek za glavnu " << ": " << *(prosjekpodijagonalama)<<endl;
    cout << "prosjek za sporednu " << ": " << *(prosjekpodijagonalama+1);
    for (int i = 0; i < vel; i++)
    {
        (avion + i)->dealokacije();
    }
    delete[] prosjekposeriji;
    delete[]prosjekpodijagonalama;
    prosjekposeriji = nullptr;
    prosjekpodijagonalama = nullptr;
    delete[]avion;
    avion = nullptr;
}




