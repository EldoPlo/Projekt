#include "Bot.hpp"

// Implementacja konstruktora klasy Bot
Bot::Bot(int _odwaga) : odwaga(_odwaga) {}

// Implementacja metody dobierzKarte dla gracza komputerowego
void Bot::dobierzKarte(Kasyno& kasyno) {
    while (getSumaPunktow() < odwaga && !czySpasowal()) {
        Karta* karta = kasyno.dajKarte();
        if (karta == nullptr) {
            spasuj();
            break;
        }
        wezKarte(karta);
        std::cout << "Gracz komputerowy dobrał kartę." << std::endl;
    }
}

// Implementacja metody nadającej identyfikator gracza wirtualnego
std::string Bot::nadajIdentyfikator() {
    return "Bot" + std::to_string(1); // Zakładam, że numer gracza wirtualnego to zawsze 1
}

// Implementacja funkcji fabrykującej gracza komputerowego zgodnie z typem
 Bot Bot::stworzGraczaKomputerowego(int typGracza) {
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
    return  Bot(limitPunktow); 
}