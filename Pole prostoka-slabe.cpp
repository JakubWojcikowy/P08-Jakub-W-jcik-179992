#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono> // Do mierzenia czasu
using namespace std;

// Funkcja do generowania losowej macierzy 0 i 1
vector<vector<int>> generujLosowaMacierz(int wiersze, int kolumny) {
    vector<vector<int>> macierz(wiersze, vector<int>(kolumny));
    srand(time(0));
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            macierz[i][j] = rand() % 2; // Losuj 0 lub 1
        }
    }
    return macierz;
}

// Funkcja do wyœwietlania macierzy
void wypiszMacierz(const vector<vector<int>>& macierz) {
    for (const auto& wiersz : macierz) {
        for (int komorka : wiersz) {
            cout << komorka << " ";
        }
        cout << endl;
    }
}
// Funkcja do znajdowania najwiekszego prostokata z jedynek
int znajdzNajwiekszyProstokat(const vector<vector<int>>& macierz, int& najlepszy_w1, int& najlepszy_k1, int& najlepszy_w2, int& najlepszy_k2) {
    int wiersze = macierz.size();
    int kolumny = macierz[0].size();
    int maxPole = 0;

    for (int w1 = 0; w1 < wiersze; w1++) {
        for (int k1 = 0; k1 < kolumny; k1++) {
            for (int w2 = w1; w2 < wiersze; w2++) {
                for (int k2 = k1; k2 < kolumny; k2++) {
                    bool sameJedynki = true;
                    for (int w = w1; w <= w2; w++) {
                        for (int k = k1; k <= k2; k++) {
                            if (macierz[w][k] == 0) {
                                sameJedynki = false;
                                break;
                            }
                        }
                        if (!sameJedynki) break;
                    }

                    if (sameJedynki) {
                        int pole = (w2 - w1 + 1) * (k2 - k1 + 1);
                        if (pole > maxPole) {
                            maxPole = pole;
                            najlepszy_w1 = w1;
                            najlepszy_k1 = k1;
                            najlepszy_w2 = w2;
                            najlepszy_k2 = k2;
                        }
                    }
                }
            }
        }
    }

    return maxPole;
}

// Funkcja do wypisywania wyników
void wypiszWynik(int maxPole, int najlepszy_w1, int najlepszy_k1, int najlepszy_w2, int najlepszy_k2) {
    if(maxPole!=0){
    cout << "Najwieksze pole prostokata: " << maxPole << endl;

    // Wypisanie wierszy i kolumn tworz¹cych najwiêkszy prostok¹t
    cout << "Jedynki tworzace najwiekszy prostokat znajduja sie w:" << endl;
    cout << "Wiersze: " << (najlepszy_w1 + 1) << "-" << (najlepszy_w2 + 1) << endl; // Zakres wierszy
    cout << "Kolumny: " << (najlepszy_k1 + 1) << "-" << (najlepszy_k2 + 1) << endl; // Zakres kolumn
    }
    else{ cout<<"W zadanej tablicy nie ma prostokata z jedynek"<<endl;
    }}


int main() {
    int wiersze, kolumny;
    cout << "Podaj liczbe wierszy: ";
    cin >> wiersze;
    cout << "Podaj liczbe kolumn: ";
    cin >> kolumny;
auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> macierz = generujLosowaMacierz(wiersze, kolumny);

    cout << "Wygenerowana macierz:" << endl;
    wypiszMacierz(macierz);



    int najlepszy_w1 = 0, najlepszy_k1 = 0, najlepszy_w2 = 0, najlepszy_k2 = 0;
    int maxPole = znajdzNajwiekszyProstokat(macierz, najlepszy_w1, najlepszy_k1, najlepszy_w2, najlepszy_k2);

    wypiszWynik(maxPole, najlepszy_w1, najlepszy_k1, najlepszy_w2, najlepszy_k2);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> czas_wykonania = end - start;
 cout << "Czas wykonania programu: " << fixed << czas_wykonania.count() << " sekund" << endl;

    return 0;
}
