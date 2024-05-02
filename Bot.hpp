#ifndef BOT_HPP
#define BOT_HPP

#include "Gracz.hpp"
#include "Kasyno.hpp"

class Bot : public Gracz {
private:
    int odwaga;

public:
    Bot(int _odwaga);

    void dobierzKarte(Kasyno& kasyno) override;

    std::string nadajIdentyfikator();
    static Bot stworzGraczaKomputerowego(int typGracza);
};

#endif // BOT_HPP