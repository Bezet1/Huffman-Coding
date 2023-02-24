/**
@file
@brief Zalaczanie bibiliotek, naglowki funkcji oraz struktury i stale globalne
*/

#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstddef>
#include <vector>
#include <string>
#include <sstream>

const int liczba_bajtow = 256; ///< stala globalna, liczba wszystkich mozliwych bajtow

///@brief Struktura wezla uzywanego do tworzenia drzewa
struct wezel
{
    int czestosc_wystepowania; ///< ilosc danego bajtu w pliku
    int index_tablicy; ///< numer bajtu 0-256
    std::string kod; ///< kod binarny nadany w celu zakodowania
    struct wezel* p_lewy; ///< wskaznik do mlodszego lewego wezla
    struct wezel* p_prawy; ///< wskaznik do mlodszego prawego wezla
};

/**@brief Alokowanie pamieci oraz tworzenie wezla, uzywanego do zbudowanie drzewa
@param wystepowanie ilosc danego bajtu w pliku
@return wskaznik stworzonego wezla
*/
wezel* stworzWezel(int wystepowanie);

/**@brief Sprawdzenie czy uzytkownik wpisal poprawna liczbe argumentow
@param liczba ilosc agrumentow wpisana podczas startowania programu
@retval TRUE program dziala dalej
@retval FALSE program sie konczy oraz wypisywana jest wiadomosc
*/
bool sprawdz_argumenty(int liczba);

/**@brief Przypisanie referencyjnie argumentow do zmiennych: wejscia, wyjscia oraz operacji
@param argv tablica argumentow wpisanych podczas startowania programu
@param input nazwa pliku wejsciowego
@param output nazwa pliku wyjsciowego
@param operacja operacja programu wpisana jako agrument (kodowanie, dekodowanie)
@retval TRUE program dziala dalej
@retval FALSE program sie konczy oraz wypisywana jest wiadomosc
*/
bool przypisz_argumenty(char* argv[], std::string& input, std::string& output, std::string& operacja);

/**@brief Otwieranie pliku wejsciowego oraz sprawdzanie czy plik ten zostal otwarty poprawnie.
@param nazwa nazwa pliku wejsciowego
@param plik referencyjne przekazanie pliku
@retval TRUE funckja zwraca referencyjnie otwarty plik, program dziala dalej
@retval FALSE program sie konczy oraz wypisana jest wiadomosc
*/
bool otworz_wejsciowy(std::string nazwa, std::ifstream& plik);

/**@brief Otwieranie pliku wyjsciowego oraz sprawdzanie czy plik ten zostal otwarty poprawnie.
@param nazwa nazwa pliku wyjsciowego
@param plik referencyjne przekazanie pliku
@retval TRUE funckja zwraca referencyjnie otwarty plik, program dziala dalej
@retval FALSE program sie konczy oraz wypisana jest wiadomosc
*/
bool otworz_wyjsciowy(std::string nazwa, std::ofstream& plik);

/**@brief Przejscie calego pliku wejsciowego oraz zliczenie poszczegolnych bajtow oraz przypisanie ich kolejnosci do wektora
@param kolejnosc wektor w ktorym jest zapisywana kolejnosc wystepowania bajtow w pliku wejsciowym
@param tablica_bajtow tablica z iloscia wystepowania kazdego bajtu w pliku wejsciowym
@param plik_wejsciowy referencyjne przekazanie pliku wejsciowego
*/
void zlicz_bajty_i_zapisz(std::vector<int>& kolejnosc, int tablica_bajtow[], std::ifstream& plik_wejsciowy);

/**@brief Tworzenie wezlow przy pomocy funckji stworzWezel() oraz dodanie do wektora tych wezlow, w ktorych czestosc wystepowanie poszczegolnych bajtow jeste wieksza od zera
@param wektor wektor wskaznikow wezlow, w ktorym przychowywane sa wszyskie wezly
@param tablica tablica z iloscia wystepowania kazdego bajtu w pliku wejsciowym
*/
void dodaj_wezly(std::vector<wezel*>& wektor, int tablica[]);

/**@brief Przeszukiwanie wektora wezlow w celu znalezienia dwoch takich, w ktorych czestosc wystepowanie jest najmniejsza.
Nastepnie tworzenie nowego wezla o liczebnosci sumy tych dwoch oraz polaczenie ich z nowym wezlem. Usuniecie dwoch najmniejsz wezlow z wektora.
Na koncu dodanie nowego wezla do vektora.
Calosc jest powtarzana do momentu gdy wszystkie wezly utworza drzewo.
@param wektor_wezlow wektor wskaznikow wezlow w ktorym znajduja sie wszystkie wezly z liczebnoscia bajtow
*/
void stworz_drzewo(std::vector<wezel*>& wektor_wezlow);

/**@brief Rekurencyjne przypisywanie kodu do kazdego wezla. Pobieranie kodu z mlodszego wezla oraz laczenie go z kodem tego starszego
@param wezel najstarszy wezel drzewa od ktorego zaczyna sie funkcja
@param tablica_kodow tablica w ktorej zapisywane sa przekonwertowane bajty
*/
void przypisz_kod(wezel* wezel, std::string tablica_kodow[]);

/**@brief Przypisanie "9" do wolnych miejsc tablicy kodow (zalozenie ze ta wartosc oznacza brak danego bajtu w pliku wejsciowym)
@param tablica_kodow tablica w ktorej zapisywane sa przekonwertowane bajty
*/
void oznacz_brak_kodu(std::string tablica_kodow[]);

/**@brief Zapisanie na poczatku pliku wyjsciowego wszystkich kodow bajtow w kolejnosci aby bylo mozliwe dekodowanie
@param plik_wyjsciowy przekazanie pliku wyjsciowego
@param tablica_kodow tablica w ktorej zapisywane sa przekonwertowane bajty
*/
void zapisz_bajty_dla_odkodowania(std::ofstream& plik_wyjsciowy, std::string tablica_kodow[]);

/**@brief Wpisywanie zakodowanych bajtow do pliku wyjsciowego w odpowiedniej kolejnosci
@param kolejnosc wektor, w ktorym zapisana jest kolejnosc wystepowania bajtow z pliku wejsciowego
@param plik_wyjsciowy referencyjne przekazanie pliku wyjsciowego
@param tablica_kodow tablica w ktorej zapisywane sa przekonwertowane bajty
*/
void wpisz_zakodowane_bajty(std::vector<int> kolejnosc, std::ofstream& plik_wyjsciowy, std::string tablica_kodow[]);

/**@brief Pobranie 256 kodow z pierwszych linijek zakodowanego pliku aby ustalic jak bajty zostaly zakodowane
@param kody_bajtow_pobrane tablica w ktorej zapisywane sa kody kazdego z bajtow
@param plik_wejsciowy referencyjne przekazanie pliku wejsciowego
*/
void zapisz_kody_do_bufora(std::string kody_bajtow_pobrane[], std::ifstream& plik_wejsciowy);

/**@brief Czytanie pojedynczo wszystkich kodow, sprawdzanie do ktorego bajta odnosi sie dany kod oraz zapisanie odczytanego bajta do pliku wyjsciowego
@param plik_wejsciowy referencyjne przekazanie pliku wejsciowego
@param plik_wyjsciowiy referencyjne przekazanie pliku wyjsciowego
@param kody_bajtow_pobrane tablica w ktorej zapisywane sa kody kazdego z bajtow
*/
void dekoduj(std::ifstream& plik_wejsciowy, std::ofstream& plik_wyjsciowy, std::string kody_bajtow_pobrane[]);

/**@brief Zwalnianie pamieci, przechodzac po calym drzewie, zaczynajac od najmlodszego wezla
@param wezel wskaznik najmlodszego wezla w drzewie
*/
void zwolnij_pamiec(wezel* wezel);

/**@brief Wyswietlenie komunikatu w konsoli na zielono
@param komunikat wiadomosc, ktora chcemy wyswietlic
*/
void pozytywny_komunikat(std::string komunikat);

/**@brief Wyswietlenie komunikatu w konsoli na czerwono
@param komunikat wiadomosc, ktora chcemy wyswietlic
*/
void negatywny_komunikat(std::string komunikat);