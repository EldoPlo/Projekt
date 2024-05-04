#include "Kasyno.hpp"
#include "Bot.hpp"
 #include <fstream>
  #include <iomanip> 

Kasyno::Kasyno(int _rozmiarTalii) : rozmiarTalii(_rozmiarTalii), iloscKartWydanych(0), aktualnyGracz(0) {
    srand(time(NULL)); 
    int i = 0;
    for (int kolor = 0; kolor < 4; kolor++) {
        for (int wartosc = 0; wartosc < 13; wartosc++) {
            talia[i] = new Karta(kolor, wartosc);
            i++;
        }
    }
    imionaGraczy = new std::string[iloscGraczy]; 
}

Kasyno::Kasyno() : Kasyno(52) {}

Karta* Kasyno::dajKarte() {
    if (iloscKartWydanych < rozmiarTalii) {
        iloscKartWydanych++;
       
        return talia[iloscKartWydanych - 1];
    }
    else {
        return nullptr;
    }
}

void Kasyno::inicjalizujKasyno() {
    iloscGraczy = getNumberOfPlayers();
    iloscBotow = getNumberOfBots();
    imionaGraczy = new std::string[iloscGraczy + iloscBotow];
     gracze = new Gracz*[iloscGraczy + iloscBotow];

    for (int i = 0; i < iloscGraczy; i++)
    {
        imionaGraczy[i] = getPlayerName(i + 1);
        gracze[i] = new Gracz(imionaGraczy[i]);
    }
    for (int i = iloscGraczy; i < iloscGraczy + iloscBotow; ++i) {
        int typGracza;
        do {
            std::cout << "Wybierz typ gracza komputerowego (1 - ryzykujący, 2 - normalny, 3 - zachowawczy): ";
            std::cin >> typGracza;
           
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (typGracza < 1 || typGracza > 3);
        
        std::cout << "Dodawanie gracza komputerowego " << i + 1 << "..." << std::endl;
        gracze[i] = Bot::stworzGraczaKomputerowego(typGracza);
        std::cout << "Dodano gracza komputerowego " << i + 1 << " (" << dynamic_cast<Bot*>(gracze[i])->nadajIdentyfikator() << std::to_string(i) << ")" << std::endl;
        imionaGraczy[i] = "Bot" + std::to_string(i + 1);
        std::cout << "Imię gracza komputerowego " << i + 1 << ": " << imionaGraczy[i] << std::endl;
    }

   

    std::cout << "Ilość graczy: " << iloscGraczy << std::endl;
    std::cout << "Ilość botow: " << iloscBotow << std::endl;
}

void Kasyno::graj() {
    inicjalizujKasyno();
    tasujTalie();
    rozdajPoczatkoweKarty();
    std::cout << "Początkowe karty graczy:" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    for (int i = 0; i < iloscGraczy + iloscBotow; i++) {
        std::cout << "Gracz " << i + 1 << " (" << imionaGraczy[i] << "): ";
        std::cout << "-----------------------------------" << std::endl;
        gracze[i]->wyswietlKarty(); 
        std::cout << "  Suma punktów: " << gracze[i]->getSumaPunktow() << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    while (aktualnyGracz < iloscGraczy + iloscBotow) {
        while (!gracze[aktualnyGracz]->czySpasowal()) { 
            std::cout << "Gracz " << aktualnyGracz + 1 << " (" << imionaGraczy[aktualnyGracz] << "): ";
            std::cout << "-----------------------------------" << std::endl;
            gracze[aktualnyGracz]->wyswietlKarty(); 
            std::cout << "  Suma punktów: " << gracze[aktualnyGracz]->getSumaPunktow() << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            gracze[aktualnyGracz]->dobierzKarte(*this); 
        }
        aktualnyGracz++;
    }

    decideWhoWon(); 
}

void Kasyno::decideWhoWon() {
    int* sumaPunktowGraczy = new int[iloscGraczy];
    for (int i = 0; i < iloscGraczy + iloscBotow; ++i) {
        sumaPunktowGraczy[i] = gracze[i]->getSumaPunktow();
    }

    int winningPlayer = determineWinner(sumaPunktowGraczy);
    switch (winningPlayer) {
        case -1:
            std::cout << "Wszyscy gracze przekroczyli 21 punktów. Remis!" << std::endl;
            break;
        case -2:
            std::cout << "Remis!" << std::endl;
            break;
        default:
            std::cout << "Gracz " << winningPlayer + 1 << " (" << imionaGraczy[winningPlayer] << ") wygrał!" << std::endl;
            break;
    }

    delete[] sumaPunktowGraczy;
}


int Kasyno::determineWinner(int* sumaPunktowGraczy) {
    int maxPoints = -1;
    int winningPlayer = -1;
    bool draw = false;
    bool allBusted = true;

    for (int i = 0; i < iloscGraczy + iloscBotow; ++i) {
        if (sumaPunktowGraczy[i] <= 21) {
            allBusted = false;
            if (sumaPunktowGraczy[i] > maxPoints) {
                maxPoints = sumaPunktowGraczy[i];
                winningPlayer = i;
                draw = false;
            } else if (sumaPunktowGraczy[i] == maxPoints) {
                draw = true;
            }
        }
    }

    if (allBusted) {
        return -1; 
    } else if (draw) {
        return -2; 
    } else {
        return winningPlayer; 
    }
}

void Kasyno::rozdajPoczatkoweKarty() {
    std::cout << "Rozdawanie początkowych kart..." << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    for (int i = 0; i < iloscGraczy + iloscBotow; i++) {
        
        
        if (dynamic_cast<Bot*>(gracze[i]) != nullptr) { 
            
            imionaGraczy[i] = dynamic_cast<Bot*>(gracze[i])->nadajIdentyfikator() + std::to_string(i);
           
        }

        for (int j = 0; j < 2; j++) {
              
            gracze[i]->wezKarte(dajKarte()); 
        }
    }
}

void Kasyno::tasujTalie() {
    for (int i = 0; i < rozmiarTalii; i++) {
        int losowyIndex = rand() % rozmiarTalii;
        Karta* temp = talia[i];
        talia[i] = talia[losowyIndex];
        talia[losowyIndex] = temp;
    }
}

int Kasyno::getNumberOfPlayers() {
    int numberOfPlayers;
    do {
        std::cout << "Podaj liczbę graczy (od 1 do 3): ";
        if (std::cin >> numberOfPlayers && numberOfPlayers >= 1 && numberOfPlayers <= 3) {
            break; 
        } else {
            std::cout << "Niepoprawna liczba graczy. Podaj liczbę od 1 do 3." << std::endl;
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
    } while (true);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    return numberOfPlayers;
}

int Kasyno::getNumberOfBots() {
    int numberOfBots;
    do {
        std::cout << "Podaj liczbę botów (od 0 do 3): ";
        if (std::cin >> numberOfBots && numberOfBots >= 0 && numberOfBots <= 3) {
            break; 
        } else {
            std::cout << "Niepoprawna liczba graczy. Podaj liczbę od 0 do 3." << std::endl;
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
    } while (true);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    return numberOfBots;
}

std::string Kasyno::getPlayerName(int playerNumber) {
    std::string playerName;
    do {
        std::cout << "Podaj nazwę gracza " << playerNumber << " (maksymalnie 20 znaków): ";
        std::getline(std::cin, playerName);
        if (!playerName.empty() && playerName.length() <= 20) {
            break; 
        } else {
            std::cout << "Nazwa gracza nie może być pusta ani przekraczać 20 znaków. Wprowadź nazwę gracza ponownie." << std::endl;
        }
    } while (true);
    return playerName;
}

void Kasyno::zapiszStanGryDoPliku(const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku);

    plik << std::setw(10) << std::left << "Gracz" << "Karty"<< "           Suma" << std::endl;
    plik << std::setw(30) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

    for (int i = 0; i < iloscGraczy + iloscBotow; ++i) {
        Gracz* gracz = gracze[i];
        std::string imie = imionaGraczy[i];

        plik << std::setw(10) << std::left << imie;
        plik << gracz->wyswietlKartydoPliku() << "  " << gracz->getSumaPunktow() << std::endl; 
    }

    plik.close();
}

Kasyno::~Kasyno() {
    for (int i = 0; i < rozmiarTalii; i++) {
        delete talia[i];
    }
    delete[] gracze;
    delete[] imionaGraczy;
}
