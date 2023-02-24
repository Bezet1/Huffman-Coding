#include "Funkcje.h"

int main(int argc, char* argv[])
{
    if (!sprawdz_argumenty(argc)) {
        return 0;
    };

    const int liczba_bajtow = 256;

    std::string input;
    std::string output;
    std::string operacja;
    std::ifstream plik_wejsciowy;
    std::ofstream plik_wyjsciowy;
    
    if (!przypisz_argumenty(argv, input, output, operacja)) {
        return 0;
    }
    
    if (!otworz_wejsciowy(input, plik_wejsciowy)) {
        return 0;
    }

    if (!otworz_wyjsciowy(output, plik_wyjsciowy)) {
        return 0;
    }

    if (operacja == "-c")
    {
        std::vector<wezel*> wektor_wezlow;
        std::vector<int> kolejnosc;
        std::string tablica_kodow[liczba_bajtow];
        int tablica_bajtow[liczba_bajtow]{};

        zlicz_bajty_i_zapisz(kolejnosc, tablica_bajtow, plik_wejsciowy);

        dodaj_wezly(wektor_wezlow, tablica_bajtow);

        stworz_drzewo(wektor_wezlow);

        przypisz_kod(wektor_wezlow.front(), tablica_kodow);

        oznacz_brak_kodu(tablica_kodow);

        zapisz_bajty_dla_odkodowania(plik_wyjsciowy, tablica_kodow);

        wpisz_zakodowane_bajty(kolejnosc, plik_wyjsciowy, tablica_kodow);

        zwolnij_pamiec(wektor_wezlow.front());

        pozytywny_komunikat("Kodowanie poprawne!");
        return 0;
    }
    else 
    {
        std::string kody_bajtow_pobrane[liczba_bajtow];
        
        zapisz_kody_do_bufora(kody_bajtow_pobrane, plik_wejsciowy);

        dekoduj(plik_wejsciowy, plik_wyjsciowy, kody_bajtow_pobrane);

        pozytywny_komunikat("Dekodowanie poprawne!");
        return 0;
    }
}
