#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip> // Do ustawiania precyzji
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
// Funkcja do wyświetlania macierzy
void wypiszMacierz(const vector<vector<int>>& macierz) {
    for (const auto& wiersz : macierz) {
        for (int komorka : wiersz) {
            cout << komorka << " ";
        }
        cout << endl;
    }
}
// Funkcja obliczająca największe pole prostokąta z jedynek
int znajdzNajwiekszyProstokat(const vector<vector<int>>& macierz, int& najlepszy_w1, int& najlepszy_k1, int& najlepszy_w2, int& najlepszy_k2) {
    if (macierz.empty() || macierz[0].empty()) return 0;
    int wiersze = macierz.size();
    int kolumny = macierz[0].size();
    int maxPole = 0;
// DP tablica do przechowywania szerokości jedynek dla każdego punktu
    vector<vector<int>> dp(wiersze, vector<int>(kolumny, 0));

    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            if (macierz[i][j] == 1) {
                // Obliczamy szerokość jedynek w bieżącym wierszu
                dp[i][j] = (j == 0 ? 1 : dp[i][j - 1] + 1);

                // Minimalna wysokość w pionie (wysokość prostokąta)
                int minSzerokosc = dp[i][j];
                for (int k = i; k >= 0; k--) {
                    minSzerokosc = min(minSzerokosc, dp[k][j]);
                    int wysokosc = i - k + 1;
                    int pole = minSzerokosc * wysokosc;
                    if (pole > maxPole) {
                        maxPole = pole;
                        najlepszy_w1 = k;
                        najlepszy_k1 = j - minSzerokosc + 1;
                        najlepszy_w2 = i;
                        najlepszy_k2 = j;
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

    // Wypisanie wierszy i kolumn tworzących największy prostokąt
    cout << "Jedynki tworzace najwiekszy prostokat znajduja sie w:" << endl;
    cout << "Wiersze: " << (najlepszy_w1 + 1) << "-" << (najlepszy_w2 + 1) << endl; // Zakres wierszy
    cout << "Kolumny: " << (najlepszy_k1 + 1) << "-" << (najlepszy_k2 + 1) << endl; // Zakres kolumn
}
else cout<<"Utworzona macierz nie posiada jedynek z ktorych mozna obliczyc pole prostokata"<<endl;}

int main() {
    int wiersze, kolumny;
    cout << "Podaj liczbe wierszy: ";
    cin >> wiersze;
    cout << "Podaj liczbe kolumn: ";
    cin >> kolumny;

    vector<vector<int>> macierz = generujLosowaMacierz(wiersze, kolumny);

    cout << "Wygenerowana macierz:" << endl;
    wypiszMacierz(macierz);

    int najlepszy_w1 = 0, najlepszy_k1 = 0, najlepszy_w2 = 0, najlepszy_k2 = 0;
// Mierzenie czasu wykonania
    clock_t start = clock();

    int maxPole = znajdzNajwiekszyProstokat(macierz, najlepszy_w1, najlepszy_k1, najlepszy_w2, najlepszy_k2);

    clock_t end = clock();

    wypiszWynik(maxPole, najlepszy_w1, najlepszy_k1, najlepszy_w2, najlepszy_k2);

    // Wypisanie czasu wykonania w milisekundach
    double czas_wykonania = (double)(end - start) / CLOCKS_PER_SEC * 1000.0; // Czas w milisekundach
    cout << "Czas wykonania programu: " << fixed << setprecision(3) << czas_wykonania << " ms" << endl;

    return 0;
}
