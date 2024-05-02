#ifndef GRACZ_HPP
#define GRACZ_HPP

#include "Karta.hpp"



class Kasyno;
class Gracz {
private:
    Karta* karty[10];
    int iloscKart;
    int sumaPunktow;
    bool spasowal;
    std::string nazwa;

protected:
    void graczPociagnal(Kasyno &kasyno);
    void spasuj();

public:
    Gracz();
    Gracz(const char* _nazwa);
    void wezKarte(Karta* _karta);
    void wyswietlKarty();
    int getSumaPunktow();
    bool czySpasowal();
    virtual void dobierzKarte(Kasyno &kasyno);
    void graczSpasowal(Kasyno &kasyno);
    const std::string& getNazwa();
   
    virtual bool isBot() const { return false; }
    ~Gracz();
};

#endif /* GRACZ_HPP */
