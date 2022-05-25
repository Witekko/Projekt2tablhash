// TablicaHaszujacaaa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

const int Wielkosc = 11;

struct Element//definiowanie elementu
{
    int klucz;
    double wartosc;
};

class Table
{
public:
    Table();
    void insert(const Element& entry);//dodawanie do tablicy hashujacej probkwoaie liniowe
    void insertd(const Element& entry);//dodawanie do tablicy hashujacej double hash
    void remove(int klucz, bool& znaleziony, Element& wynik); //usuwanie
    void find(int klucz, bool& znaleziony, Element& wynik) const;
    void print();
    int size() const;
private:
    int hash(int klucz) const;//haszowanie klucza 
    int hashd(int klucz) const;//haszowanie drugie klucza
    void findIndexd(int klucz, bool& znaleziony, int& i) const;//znajdowanie odpowiedanego indeksu dla klucza double hash
    void findIndex(int klucz, bool& znaleziony, int& i) const;//znajdowanei odpowiedzniego indeksu dla klucza probkowanie liniowe
    void findIndexx(int klucz, bool& znaleziony, int& i) const;//zdajdowanie konkretnego indeksu dla remove i find
    Element data[Wielkosc];
    int uzywane;
};

Table::Table()//inicjowanie pustej tablicy
{
    uzywane = 0;
    for (int i = 0; i < Wielkosc; i++)
        data[i].klucz = -1;
}

void Table::insert(const Element& entry)//funkcja dodaj
{
    bool czyJest;
    int index;

    assert(entry.klucz >= 0);// zabezpieczenie przed niepoprawna dana wejsciowa

    findIndex(entry.klucz, czyJest, index);//szukanie indeksu odpowiedniego dla liczby
    if (!czyJest)
    {
        assert(size() < Wielkosc);
        uzywane++;
    }
    data[index] = entry;
}

void Table::insertd(const Element& entry)//funkcja dodaj
{
    bool czyJest;
    int index;

    assert(entry.klucz >= 0);// zabezpieczenie przed niepoprawna dana wejsciowa

    findIndexd(entry.klucz, czyJest, index);//szukanie indeksu odpowiedniego dla liczby
    if (!czyJest)
    {
        assert(size() < Wielkosc);
        uzywane++;
    }
    data[index] = entry;
}

int Table::hash(int klucz) const
{
    return klucz % Wielkosc;
}
int Table::hashd(int klucz) const
{
    return 7 - (klucz % 7);
}

int Table::size() const
{
    return uzywane;
}

void Table::findIndex(int klucz, bool& znaleziony, int& i) const
{
    int indeks = 0;

    i = hash(klucz);
    while (indeks < Wielkosc && data[i].klucz != -1 && data[i].klucz != klucz)
    {
        indeks++;
        i = (i + 1) % Wielkosc;
    }
    znaleziony = data[i].klucz == klucz;
}
void Table::findIndexd(int klucz, bool& znaleziony, int& i) const
{
    int indeks = 0;

    i = hash(klucz);
    if (data[i].klucz != -1) {//jezeli pustee to zapraszam
        znaleziony = data[i].klucz == klucz;
    }
    else {
        if (data[i].klucz != -1) {// podwojne hashowanie jesli indeks byl zajety
            i = hash(klucz) + hashd(klucz);
            znaleziony = data[i].klucz == klucz;
        }
        znaleziony = data[i].klucz == klucz;
    }
}
void Table::findIndexx(int klucz, bool& znaleziony, int& i) const
{
    int indeks = 0;

    i = hash(klucz);
    
    if (data[i].klucz == -1) {//brak zadnego klucza w indeksie oczekiwanym
        do 
        {
            indeks++;
            i = (i + 1) % Wielkosc;
        }while (indeks < Wielkosc && data[i].klucz != klucz);
        znaleziony = data[i].klucz == klucz;
    }
    else {
        if (data[i].klucz == klucz) {//zanleziono klucz od razu
            znaleziony = data[i].klucz == klucz;
        }
        else {//szukanie klucza jak byl tam klucz ale nie ten
            do
            {
                indeks++;
                i = (i + 1) % Wielkosc;
            }while (indeks < Wielkosc && data[i].klucz != klucz);
            znaleziony = data[i].klucz == klucz;
        }
    }
}

void Table::print() {
    for (int index = 0; index < Wielkosc; index++) {
        cout << "Index " << index<<": ";
        if (data[index].klucz == -1)
        {
            cout << "pusty slot!" << endl;
        }
        else {
            cout << "klucz: " << data[index].klucz << "    wartosc= " << data[index].wartosc << endl;
            }
    }
}
void Table::remove(int klucz,bool& znaleziony, Element& wynik)
{
    int index;
    bool czyJest;

    assert(klucz >= 0);
    findIndexx(klucz, czyJest, index);
    if (znaleziony)
    {
        assert(size()>0);
        uzywane--;//aktualizacja uzupenienia tablicy
        data[index].klucz = -1;//zerowanie elementu
        data[index].wartosc = NULL;
    }
}

void Table::find(int klucz, bool& znaleziony, Element& wynik) const
{
    int index;

    assert(klucz >= 0);

    findIndexx(klucz, znaleziony, index);
    if (znaleziony) {
        wynik = data[index];
    }
}

void menu();

int main()
{
    int ile;
    char wybor;
    Table tablicaHashujaca;
    Element elem;
    int klucz;
    bool znaleziony;
    int size;
    srand(time(NULL));
    cout << "ile liczb wprowadzic: ";
    cin >> ile;
    int* klucze = new int[ile];
    double* wartosci= new double[ile];
    for (int i = 0; i < ile; i++) {
        klucze[i] = rand() % 100 + 1;
    }
    for (int i = 0; i < ile; i++) {
        wartosci[i] = rand() % 1000 + 1;
    }
    for (int i = 0; i < ile; i++) {
        cout << klucze[i] << endl;
        cout << wartosci[i] << endl << endl;
    }
    for (int i = 0; i < ile; i++) {
        elem.klucz = klucze[i];
        elem.wartosc = wartosci[i];
        tablicaHashujaca.insert(elem);
    }
    delete[] klucze;
    delete[] wartosci;
    
    cout << "Dodano "<<ile<< " elementow do tablicy haszujacej" << endl << endl;
    do
    {
        
        menu();
        cout << "podaj wybor: ";
        cin >> wybor;
        cout << endl;
        wybor = toupper(wybor);

        switch (wybor)
        {
        case 'I': // insert
            cout << "Podaj klucz (int >= 0) pod jakim chcesz zapisac elemnt: ";
            cin >> elem.klucz;
            cout << "Podaj wartosc (double) dla elementu: ";
            cin >> elem.wartosc;
            tablicaHashujaca.insert(elem);
            cout << "Dodano element do tablicy haszujacej" << endl << endl;
            break;
        case 'D': // insert ale to doublehash

            cout << "Podaj klucz (int >= 0) pod jakim chcesz zapisac elemnt: ";
            cin >> elem.klucz;
            cout << "Podaj wartosc (double) dla elementu: ";
            cin >> elem.wartosc;
            tablicaHashujaca.insertd(elem);
            cout << "Dodano element do tablicy haszujacej" << endl << endl;
            break;
        case 'F': // find
            cout << "podaj klucz (int >= 0) jaki odnalezc: " << endl;
            cin >> klucz;
            tablicaHashujaca.find(klucz, znaleziony, elem);
            if (znaleziony)
            {
                cout << "   Element znaleziony!!1!111!1" << endl;
                cout << "   klucz       = " << setw(8)
                    << elem.klucz << endl;
                cout << "   wartosc     = " << setw(8)
                    << elem.wartosc << endl;
            }
            else
                cout << "element pod kluczem " << klucz << " nie znaleziony."
                << endl << endl;
            break;

        case 'P': // find
            cout << "podaj klucz (int >= 0) jaki odnalezc: "<<endl;
            tablicaHashujaca.print();
            break;
            

        case 'R': // remove
            cout << "podaj klucz (int >= 0) jaki usunac: ";
            cin >> klucz;
            tablicaHashujaca.remove(klucz, znaleziony, elem);
            if (znaleziony)
            {
                cout << "element znaleziony i usuniety." << endl;
            }
            else
                cout << "element pod kluczem " << klucz << " nie znaleziony."
                << endl << endl;
            break;
        case 'S': // size
            size = tablicaHashujaca.size();
            cout << "Jest " << size << " elementow w tablicy."
                << endl;
            cout << "Jest " << (Wielkosc - size)
                << " pustych pozycji w tablicy." << endl << endl;
            break;
        case 'Q': cout << "..::Koniec programu::.." << endl;
            break;
        default:  cout << wybor << " zle wrowadzona opcja wyboru." << endl;
        }
    } while ((wybor != 'Q'));

    return EXIT_SUCCESS;
    

}

void menu()
{
    cout << endl;
    cout << "...:::dostepne opcje:::... " << endl;
    cout << " I   Dodaj element" << endl;
    cout << " D   Dodaj element(double hash)" << endl;
    cout << " F   Znajdz element" << endl;
    cout << " R   Usun elemnet" << endl;
    cout << " P   Wypisz tablice" << endl;
    cout << " S   Policz elementy w tablicy" << endl;
    cout << " Q   Opusc program" << endl << endl;
}
