// TablicaHaszujacaa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <list>

using namespace std;

class Hashtablica {
private:
    list<int>* tablica;
    int liczba_elementow;

    // Funkcja haszujaca:
    int getHash(int klucz) {
        return klucz % liczba_elementow;
    }

public:
    // Tworzenie tablicy z n elementow i list od kolejnych miejsc w tablicaail:
    Hashtablica(int n) {
        liczba_elementow = n;
        tablica = new list<int>[liczba_elementow];
    }

    // Dodawanie elementu tablicy:
    void insertElement(int klucz) {
        tablica[getHash(klucz)].push_back(klucz);
    }
    

    // Usuwanie elkementu z tablicy:
    void removeElement(int klucz) {
        int x = getHash(klucz);

        list<int>::iterator i;
        for (i = tablica[x].begin(); i != tablica[x].end(); i++) {
            // szukanie elemantu na liscie:
            if (*i == klucz)
                break;
        }

        // usuwanie elementu z listy:
        if (i != tablica[x].end())
            tablica[x].erase(i);
    }

    void searchElement(int klucz) {
        int x = getHash(klucz);
        list<int>::iterator i;
        for (i = tablica[x].begin(); i != tablica[x].end(); i++) {
            // szukanie elemantu na liscie:
            if (*i == klucz)
                break;
        }
        if (i != tablica[x].end()) {
            cout <<"indeks: "<<x<<endl;
            for (int j : tablica[x])
                cout << j << " => ";
        }
    }
    void printAll() {
        // Przeczesywanie tablicy:
        for (int i = 0; i < liczba_elementow; i++) {
            cout << "Indeks " << i << ": ";
            // przeczesywanie konkretnej listy:
            for (int j : tablica[i])
                cout << j << " => ";

            cout << endl;
        }
    }
};

int main() {
    int ile;
    int jaka;
    int wybor=3;
    srand(time(NULL));
    Hashtablica ht1(21);
    cout << "ile liczb wprowadzic: ";
    cin >> ile;


    int* tab = new int[ile];

    for (int i = 0; i < ile; i++) {
        tab[i] = rand() % 1000 + 1;
    }
    // Dodaj wygenrowane elementy do tablicy:
    for (int i = 0; i < ile; i++)
        ht1.insertElement(tab[i]);

    while (wybor != 5) {
        
        
        cout << endl;
        cout << "MENU GLOWNE\n" << "-------------\n";
        cout << "1. dodawanie\n";
        cout << "2. usuwanie\n";
        cout << "3. wyswielt\n";
        cout << "4. szukaj\n";
        cout << "5. koniec\n";


        cout << endl;
        cin >> wybor;
        switch (wybor) {
        case 1:
        {
            cout << "jaka licze dodac: ";
            cin >> jaka;
            ht1.insertElement(jaka);
        }
        break;
        case 2:
        {
            cout << "jaka licze usunac: ";
            cin >> jaka;
            ht1.removeElement(jaka);
        }
        break;
        case 3:
        {
            cout << "..:: Hash tablica ::.." << endl;
            ht1.printAll();
        }
        break;
        case 4:
        {
            cout << "jaka liczbe chcesz poszukac: ";
            cin >> jaka;
            ht1.searchElement(jaka);
        }
        break;

        case 5:
        {
            exit(0);
        }
        break;

        default: cout << "Nie ma takiej opcji";
        }
    }
    delete[] tab;
    return 0;
}