#include <iostream>
#include<iomanip>
using namespace std;

char* getPokazivac(char* text){
	if (text == nullptr)
	{
		return nullptr;
	}
	int vel = strlen(text) + 1;
	char* kopija = new char[vel];
	strcpy_s(kopija,vel,text);
	return kopija;
}
struct Igrica {
	char* imeIgrice = nullptr;
	char* imePublishera = nullptr;
	char Publika[40] = "";

	int brojRemeka = 0;
	int brojRecenzenta = 0;
	int** ocjene = nullptr; // matrica dimenzija (brojRemeka * brojRecenzenata)

	void unos()
	{
		char temp[200];

		cout << "Unesi ime igr." << endl;
		cin.getline(temp, 200);
		imeIgrice = getPokazivac(temp);

		cout << "Unesi ime publishera." << endl;
		cin.getline(temp, 200);
		imePublishera = getPokazivac(temp);

		cout << "Unesi publiku igrice." << endl;
		cin.getline(Publika, 40);

		cout << "Unesi broj remeka i broj recenzenata" << endl;
		cin >> brojRemeka >> brojRecenzenta;
		cin.ignore();

		ocjene = new int* [brojRemeka];
		for (int i = 0; i < brojRemeka; i++)
		{
			*(ocjene + i) = new int[brojRecenzenta];
			for (int j = 0; j < brojRecenzenta; j++)
			{
				std::cout << "Unesite ocjenu igrice za remake broj " << i+1 << " od strane ";
				std::cout << "recenzenta broj " << j+1 << ": ";
				cin >> *(*(ocjene + i) + j);
			}
			
		}
	}
	void ispis()
	{
		cout << "Ime igr: " << imeIgrice << endl;
		cout << "Ime publishera: " << imePublishera << endl;
		cout << "Publika igrice: " << Publika << endl;
		cout << "Broj remeka i recenzenata " << brojRemeka << " " << brojRecenzenta << endl;

		for (int i = 0; i < brojRemeka; i++)
		{
			cout << "remake broj " << i+1 <<" -> ";
			for (int j = 0; j < brojRecenzenta; j++)
			{
				cout<<"recenzija broj "<<j+1<<" -> " <<setw(3) <<*(*(ocjene + i) + j)<<" |";
			}
			cout << endl;
		}
	}
	void dealokacija()
	{
		delete[]imeIgrice;
		imeIgrice = nullptr;
		delete[]imePublishera;
		imePublishera = nullptr;
		for (int i = 0; i < brojRemeka; i++)
		{
			delete[] * (ocjene + i);
		}
		delete[]ocjene;
		ocjene = nullptr;
	}
};

int main()
{
	int n;
	cout << "unesi n" << endl;
	cin >> n;
	cin.ignore();
	Igrica* igrica = new Igrica[n];
	for (int i = 0; i < n; i++)
	{
		(igrica + i)->unos();
	}
	for (int i = 0; i < n; i++)
	{
		(igrica + i)->ispis();
	}
	for (int i = 0; i < n; i++)
	{
		(igrica + i)->dealokacija();
	}
	delete[]igrica;
	igrica = nullptr;

	return 0;

}

