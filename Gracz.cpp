#include "Karta.hpp"
#include "Gracz.hpp"
#include <iostream>
#include "Kasyno.hpp"
#include <map>
#include <functional> 
#include <limits>
#include <cstring> // Dla funkcji strlen

Gracz::Gracz() : iloscKart(0), sumaPunktow(0), spasowal(false) {}

void Gracz::wezKarte(Karta* karta)
{
    if (iloscKart < 10)
    {
        karty[iloscKart] = karta;
        iloscKart++;
        sumaPunktow = sumaPunktow + karta->getWartosc();
    }
    
}

void Gracz::wyswietlKarty()
{
    std::cout << "Gracz " << nazwa << ": " << std::endl; // Wyświetlenie nazwy gracza
    for (int i = 0; i < iloscKart; i++)
    {
        Karta* karta = karty[i];
        std::cout << "Karta " << i+1 << ": " << karta->getFigura() << " " << karta->getKolor() << " " << karta->getWartosc() << std::endl;
    }
}

void Gracz::dobierzKarte(Kasyno& kasyno)
{
    std::map<char, std::function<void()>> actions = {
        {'T', std::bind(&Gracz::graczPociagnal, this, std::ref(kasyno))},
        {'N', std::bind(&Gracz::spasuj, this)}
    };

    char odpowiedz;
    do {
        std::cout << "Czy chcesz pociągnąć kartę? Jeśli tak, wpisz T. Jeśli chcesz spasować, wpisz N: ";
        std::cin >> odpowiedz;

        if (actions.find(odpowiedz) != actions.end()) {
            actions[odpowiedz](); 
            break;
        } else {
            std::cout << "Niepoprawna odpowiedź. Wprowadź T jeśli chcesz pociągnąć kartę lub N jeśli chcesz spasować." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (true);
}

void Gracz::graczPociagnal(Kasyno &Kasyno)
{
    Karta *karta = Kasyno.dajKarte();
    if (karta == nullptr)
    {
        spasuj();
    }

    wezKarte(karta);
    std::cout << "----------------- " << std::endl;
    std::cout << "Dobrałeś kartę: " << karta->getFigura() << " " << karta->getKolor() << " " << std::endl;
    std::cout << "----------------- " << std::endl;
    std::cout << "Twoja suma punktów wynosi teraz: " << sumaPunktow << std::endl;
    std::cout << "----------------- " << std::endl;

    if (sumaPunktow > 21)
    {
        std::cout << "Twoje Karty : " << std::endl;
        wyswietlKarty();
        std::cout << "----------------- " << std::endl;
        std::cout << "Przekroczyłeś 21 punktów!" << std::endl;
        std::cout << "----------------- " << std::endl;
        spasuj();
    }
}

int Gracz::getSumaPunktow()
{
    return sumaPunktow;
}

bool Gracz::czySpasowal() 
{
    return spasowal;
}

void Gracz::spasuj()
{
    spasowal = true;
}

const std::string& Gracz::getNazwa()
{
    return nazwa;
}

Gracz::~Gracz()
{
    for (int i = 0; i < iloscKart; i++)
    {
        delete karty[i];
    }
}