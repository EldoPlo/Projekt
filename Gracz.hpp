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
    char nazwa[21];

protected:
    void graczPociagnal(Kasyno &kasyno);
    void spasuj();

public:
    Gracz(const std::string _nazwa);
    void wezKarte(Karta* _karta);
    void wyswietlKarty();
    int getSumaPunktow();
    bool czySpasowal();
    virtual void dobierzKarte(Kasyno &kasyno);
    void graczSpasowal(Kasyno &kasyno);
    const std::string getNazwa();
    Karta** pobierzKarty() { return karty; }
   std::string wyswietlKartydoPliku() const;
    virtual bool isBot() const { return false; }
    ~Gracz();
};

#endif /* GRACZ_HPP */
