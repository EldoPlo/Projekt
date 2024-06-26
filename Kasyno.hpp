#ifndef KASYNO_HPP
#define KASYNO_HPP

#include "Gracz.hpp"
#include "Karta.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

class Kasyno {
private:
    int rozmiarTalii;
    int iloscKartWydanych;
    Karta* talia[52];
    int iloscGraczy;
    int iloscBotow;
    Gracz** gracze;
    std::string* imionaGraczy;
    int aktualnyGracz;
    int getNumberOfBots();
    

public:
    Kasyno(int _rozmiarTalii);
    Kasyno();
    ~Kasyno();
    void zapiszStanGryDoPliku(const std::string& nazwaPliku);
    void inicjalizujKasyno();
    void graj();
    void decideWhoWon();
    void rozdajPoczatkoweKarty();
    void tasujTalie();
    int getNumberOfPlayers();
    std::string getPlayerName(int playerNumber);
    void dodajBoty();
    Gracz* stworzGraczaKomputerowego(int typGracza);
    int determineWinner(int* sumaPunktowGraczy);
    Karta* dajKarte();
};

#endif /* KASYNO_HPP */
