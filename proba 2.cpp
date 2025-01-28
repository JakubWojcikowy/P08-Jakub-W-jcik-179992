#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
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


int main() {
    int wiersze, kolumny;
    cout << "Podaj liczbe wierszy: ";
    cin >> wiersze;
    cout << "Podaj liczbe kolumn: ";
    cin >> kolumny;

    vector<vector<int>> macierz = generujLosowaMacierz(wiersze, kolumny);

    cout << "Wygenerowana macierz:" << endl;
    wypiszMacierz(macierz);



    return 0;
}
