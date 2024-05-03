#include "Bot.hpp"

// Implementacja konstruktora klasy Bot
Bot::Bot(int _odwaga, const std::string _nazwa) : Gracz(_nazwa), odwaga(_odwaga) {};

// Implementacja metody dobierzKarte dla gracza komputerowego
void Bot::dobierzKarte(Kasyno& kasyno) {
    std::cout << "Gracz komputerowy dobiera kartę." << std::endl;
    while (getSumaPunktow() < odwaga && !czySpasowal()) {
        std::cout << odwaga << std::endl;
        Karta* karta = kasyno.dajKarte();
        if (karta == nullptr) {
            spasuj();
        }
        wezKarte(karta);
        std::cout << "Gracz komputerowy dobrał kartę." << std::endl;
    }
    spasuj();
}


std::string Bot::nadajIdentyfikator() {
    return "Bot"; 
}


Bot* Bot::stworzGraczaKomputerowego(int typGracza) {
    int limitPunktow;
    switch (typGracza) {
        case 1: // Gracz ryzykujący
            limitPunktow = 20;
            break;
        case 2: // Gracz normalny
            limitPunktow = 17;
            break;
        case 3: // Gracz zachowawczy
            limitPunktow = 14;
            break;
        default:
            limitPunktow = 16; // Domyślny limit punktów dla gracza normalnego
            break;
    }
    return new Bot(limitPunktow, "Bot" + std::to_string(typGracza)); 
}