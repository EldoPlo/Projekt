#include "Bot.hpp"


Bot::Bot(int _odwaga, const std::string _nazwa) : Gracz(_nazwa), odwaga(_odwaga) {};


void Bot::dobierzKarte(Kasyno& kasyno) {
    std::cout << "Bot dobiera kartę." << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    while (getSumaPunktow() < odwaga && !czySpasowal()) {
        std::cout << odwaga << std::endl;
        Karta* karta = kasyno.dajKarte();
        if (karta == nullptr) {
            spasuj();
        }
        wezKarte(karta);
        std::cout << "Bot dobrał kartę." << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        wyswietlKarty();
        std::cout << "-----------------------------------" << std::endl;
    }
    spasuj();
}


std::string Bot::nadajIdentyfikator() {
    return "Bot"; 
}


Bot* Bot::stworzGraczaKomputerowego(int typGracza) {
    int limitPunktow;
    switch (typGracza) {
        case 1: 
            limitPunktow = 20;
            break;
        case 2: 
            limitPunktow = 17;
            break;
        case 3: 
            limitPunktow = 14;
            break;
        default:
            limitPunktow = 17; 
            break;
    }
    return new Bot(limitPunktow, "Bot" + std::to_string(typGracza)); 
}