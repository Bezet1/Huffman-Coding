#include "Funkcje.h"

//ustawienie kolorow w konsoli
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

wezel* stworzWezel(int wystepowanie)
{
    wezel* nowyWezel = new wezel();
    nowyWezel->czestosc_wystepowania = wystepowanie;
    return nowyWezel;

}

bool sprawdz_argumenty(int liczba) {
    if (liczba != 6)
    {
        std::cout << std::endl;
        SetConsoleTextAttribute(h, 4);
        std::cout << "UZYCIE (dowolna kolejnosc): -i plik-Wejsciowy -o plik-Wyjsciowy -c (kodowanie) lub -d (dekodowanie)" << std::endl;
        std::cout << "UWAGA! Plik wyjsciowy podczas kodowania musi miec rozszerzenie .txt" << std::endl;
        SetConsoleTextAttribute(h, 7);
        std::cout << std::endl;
        return false;
    }
    else {
        return true;
    }
}

bool przypisz_argumenty(char* argv[], std::string& input, std::string& output, std::string& operacja) {
    bool bylInput = false;
    bool bylOutput = false;
    bool bylaOperacja = false;
    
    for (int i = 1; i < 6; ++i) {
        std::string i_ = "-i";
        if (i_.compare(argv[i]) == 0) {
            input = argv[i + 1];
            bylInput = true;
        }
        std::string o_ = "-o";
        if (o_.compare(argv[i]) == 0) {
            output = argv[i + 1];
            bylOutput = true;
        }
        std::string d_ = "-d";
        std::string c_ = "-c";
        if (c_.compare(argv[i]) == 0 or d_.compare(argv[i]) == 0) {
            operacja = argv[i];
            bylaOperacja = true;
        }
    }

    if (bylInput && bylOutput && bylaOperacja) {
        
        return true;
    }
    else {
        std::cout << std::endl;
        SetConsoleTextAttribute(h, 4);
        std::cout << "Nieprawidlowe parametry" << std::endl;
        SetConsoleTextAttribute(h, 7);
        return false;
    }
}

bool otworz_wejsciowy(std::string nazwa, std::ifstream& plik) {

    plik.open(nazwa, std::ios::binary);

    if (!plik.is_open() || !plik.good())
    {
        std::cout << std::endl;
        SetConsoleTextAttribute(h, 4);
        std::cout << "Blad: nie mozna otworzyc pliku wejsciowego" << std::endl;
        SetConsoleTextAttribute(h, 7);
        return false;
    }
    else {
        return true;
    }
}

bool otworz_wyjsciowy(std::string nazwa, std::ofstream& plik) {

    plik.open(nazwa, std::ios::binary);

    if (!plik.is_open() || !plik.good())
    {
        std::cout << std::endl;
        SetConsoleTextAttribute(h, 4);
        std::cout << "Blad: nie mozna otworzyc pliku wyjsciowego" << std::endl;
        SetConsoleTextAttribute(h, 7);
        return false;
    }
    else {
        return true;
    }
}

void zlicz_bajty_i_zapisz(std::vector<int>& kolejnosc, int tablica_bajtow[], std::ifstream& plik_wejsciowy) {

    unsigned char bajt;

    while (!plik_wejsciowy.eof())
    {
        bajt = plik_wejsciowy.get();
        tablica_bajtow[bajt]++;

        kolejnosc.push_back(bajt);
    }
}

void dodaj_wezly(std::vector<wezel*>& wektor, int tablica[]) {
    for (int i = 0; i < liczba_bajtow; i++)
    {
        if (tablica[i] > 0)
        {

            wezel* nowy_wezel = stworzWezel(tablica[i]);
            nowy_wezel->index_tablicy = i;
            nowy_wezel->p_lewy = nullptr;
            nowy_wezel->p_prawy = nullptr;

            wektor.push_back(nowy_wezel);
        }
    }
}

void stworz_drzewo(std::vector<wezel*>& wektor_wezlow) {

    int szukana_minimalna_1 = 0;
    int index_wezla_1 = 0;
    int szukana_minimalna_2 = 0;
    int index_wezla_2 = 0;
    bool ostatni_wezel = false;

    while (wektor_wezlow.size() != 1)
    {
        int rozmiar_wektora = wektor_wezlow.size();
        szukana_minimalna_1 = wektor_wezlow.at(0)->czestosc_wystepowania;
        index_wezla_1 = 0;

        //szukanie pierwszego wezla z minimalna liczebnoscia
        for (int i = 0; i < rozmiar_wektora; i++)
        {
            if (wektor_wezlow.at(i)->czestosc_wystepowania <= szukana_minimalna_1 && index_wezla_1 != i)
            {
                szukana_minimalna_1 = wektor_wezlow.at(i)->czestosc_wystepowania;
                index_wezla_1 = i;
            }
        }

        // szukanie drugiego wezla z minimalna liczebnoscia
        for (int i = 0; i < rozmiar_wektora; i++)
        {
            if (i != index_wezla_1)
            {
                szukana_minimalna_2 = wektor_wezlow.at(i)->czestosc_wystepowania;
                index_wezla_2 = i;
                break;
            }
        }

        // szukanie faktycznego, drugiego wezla z minimalna liczebnoscia
        for (int i = 0; i < rozmiar_wektora; i++)
        {
            if (wektor_wezlow.at(i)->czestosc_wystepowania <= szukana_minimalna_2 && i != index_wezla_1 && i != index_wezla_2)
            {
                szukana_minimalna_2 = wektor_wezlow.at(i)->czestosc_wystepowania;
                index_wezla_2 = i;
            }
        }

        // tworzenie nowego wezla glownego
        wezel* wezel_glowny = stworzWezel(wektor_wezlow.at(index_wezla_1)->czestosc_wystepowania + wektor_wezlow.at(index_wezla_2)->czestosc_wystepowania);

        //przypisanie kodu
        wektor_wezlow.at(index_wezla_1)->kod = "0";
        wektor_wezlow.at(index_wezla_2)->kod = "1";

        // podpinanie wezlow do glownego
        wezel_glowny->p_lewy = wektor_wezlow.at(index_wezla_1);
        wezel_glowny->p_prawy = wektor_wezlow.at(index_wezla_2);

        //usuniecie tych dwoch wezlow z wektora
        if (index_wezla_1 < index_wezla_2) {
            wektor_wezlow.erase(wektor_wezlow.begin() + index_wezla_2);
            wektor_wezlow.erase(wektor_wezlow.begin() + index_wezla_1);
        }
        else {
            wektor_wezlow.erase(wektor_wezlow.begin() + index_wezla_1);
            wektor_wezlow.erase(wektor_wezlow.begin() + index_wezla_2);
        }

        //dodanie nowego wezla do wektora
        wektor_wezlow.push_back(wezel_glowny);
    }

}

void przypisz_kod(wezel* wezel, std::string tablica_kodow[])
{

    // sprawdzenie czy nie jestesmy na ostatnim wezle
    if (wezel->p_lewy == nullptr && wezel->p_prawy == nullptr)
    {
        int index_symbolu = wezel->index_tablicy;
        tablica_kodow[index_symbolu] = wezel->kod;
        return;
    }

    std::string kod_aktualnego = wezel->kod;
    std::string kod_nizszego_prawego = wezel->p_prawy->kod;
    std::string kod_nizszego_lewego = wezel->p_lewy->kod;

    wezel->p_lewy->kod = kod_aktualnego + kod_nizszego_lewego;
    wezel->p_prawy->kod = kod_aktualnego + kod_nizszego_prawego;

    // rekurencja
    przypisz_kod(wezel->p_lewy, tablica_kodow);
    przypisz_kod(wezel->p_prawy, tablica_kodow);
}

void oznacz_brak_kodu(std::string tablica_kodow[]) {
    for (int i = 0; i < liczba_bajtow; i++)
    {
        if (tablica_kodow[i] == "")
        {
            tablica_kodow[i] = "9";
        }
    }
}

void zapisz_bajty_dla_odkodowania(std::ofstream& plik_wyjsciowy, std::string tablica_kodow[]) {
    for (int i = 0; i < liczba_bajtow; i++)
    {
        plik_wyjsciowy << tablica_kodow[i] << " ";
    }

    plik_wyjsciowy << "\n" << "*" << "\n";
}

void wpisz_zakodowane_bajty(std::vector<int> kolejnosc, std::ofstream& plik_wyjsciowy, std::string tablica_kodow[]) {

    for (int i = 0; i < kolejnosc.size(); i++)
    {
        plik_wyjsciowy << tablica_kodow[kolejnosc.at(i)] << " ";
    }
}

void zapisz_kody_do_bufora(std::string kody_bajtow_pobrane[], std::ifstream& plik_wejsciowy) {

    for (int i = 0; i < liczba_bajtow; i++)
    {
        plik_wejsciowy >> kody_bajtow_pobrane[i];
    }

    //pominiecie gwiazdki
    std::string pojedynczy;
    plik_wejsciowy >> pojedynczy;
}

void dekoduj(std::ifstream& plik_wejsciowy, std::ofstream& plik_wyjsciowy, std::string kody_bajtow_pobrane[]) {

    std::string pojedynczy;
    while (!plik_wejsciowy.eof())
    {
        plik_wejsciowy >> pojedynczy;
        for (int i = 0; i < liczba_bajtow; i++)
        {
            if (!pojedynczy.compare(kody_bajtow_pobrane[i]))
            {
                //przekonwertowanie
                unsigned char symbol = i;
                plik_wyjsciowy.put(symbol);
                break;
            }
        }
    }
}

void zwolnij_pamiec(wezel* wezel)
{
    if (wezel == nullptr)
    {
        return;
    }

    zwolnij_pamiec(wezel->p_lewy);
    zwolnij_pamiec(wezel->p_prawy);

    delete wezel;
}

void pozytywny_komunikat(std::string komunikat) {

    std::cout << std::endl;
    SetConsoleTextAttribute(h, 10);
    std::cout << komunikat << std::endl;
    SetConsoleTextAttribute(h, 7);
}

void negatywny_komunikat(std::string komunikat) {

    std::cout << std::endl;
    SetConsoleTextAttribute(h, 4);
    std::cout << komunikat << std::endl;
    SetConsoleTextAttribute(h, 7);
}