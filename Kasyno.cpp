#include "Kasyno.hpp"
#include "Bot.hpp"

Kasyno::Kasyno(int _rozmiarTalii) : rozmiarTalii(_rozmiarTalii), iloscKartWydanych(0), aktualnyGracz(0) {
    srand(time(NULL)); 
    int i = 0;
    for (int kolor = 0; kolor < 4; kolor++) {
        for (int wartosc = 0; wartosc < 13; wartosc++) {
            talia[i] = new Karta(kolor, wartosc);
            i++;
        }
    }
    imionaGraczy = new std::string[iloscGraczy]; // Inicjalizacja tablicy imionaGraczy
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
    std::cout << "Ilość graczy: " << iloscGraczy << std::endl;
    gracze = new Gracz*[iloscGraczy];
    std:: cout << "Gracze : " << gracze << std::endl;
    imionaGraczy = new std::string[iloscGraczy];
    std::cout << "Imiona graczy : " << imionaGraczy << std::endl;
    dodajBoty();
    std::cout << "siemano" << std::endl;
}

void Kasyno::graj() {
    inicjalizujKasyno();
    tasujTalie();
    rozdajPoczatkoweKarty();
    std::cout << "Początkowe karty graczy:" << std::endl;
    for (int i = 0; i < iloscGraczy; i++) {
        std::cout << "Gracz " << i + 1 << " (" << imionaGraczy[i] << "): ";
        gracze[i]->wyswietlKarty(); // Wywołanie metody przez wskaźnik
        std::cout << "  Suma punktów: " << gracze[i]->getSumaPunktow() << std::endl;
    }

    while (aktualnyGracz < iloscGraczy) {
        while (!gracze[aktualnyGracz]->czySpasowal()) { // Wywołanie metody przez wskaźnik
            std::cout << "Gracz " << aktualnyGracz + 1 << " (" << imionaGraczy[aktualnyGracz] << "): ";
            gracze[aktualnyGracz]->wyswietlKarty(); // Wywołanie metody przez wskaźnik
            std::cout << "  Suma punktów: " << gracze[aktualnyGracz]->getSumaPunktow() << std::endl;
            std::cout << "//////////////////////////////////////" << std::endl;
            gracze[aktualnyGracz]->dobierzKarte(*this); 
        }
        aktualnyGracz++;
    }

    decideWhoWon(); 
}

void Kasyno::decideWhoWon() {
    int* sumaPunktowGraczy = new int[iloscGraczy];
    for (int i = 0; i < iloscGraczy; ++i) {
        sumaPunktowGraczy[i] = gracze[i]->getSumaPunktow();
    }

    int winningPlayer = determineWinner(sumaPunktowGraczy);
    switch (winningPlayer) {
        case -1:
            std::cout << "Wszyscy gracze przekroczyli 21 punktów. Remis!" << std::endl;
            break;
        case -2:
            std::cout << "Remis! Wszyscy gracze mają tyle samo punktów poniżej 21." << std::endl;
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

    for (int i = 0; i < iloscGraczy; ++i) {
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
        return -1; // Wszyscy przekroczyli 21
    } else if (draw) {
        return -2; // Remis
    } else {
        return winningPlayer; // Zwraca indeks zwycięzcy
    }
}

void Kasyno::rozdajPoczatkoweKarty() {
    std::cout << "Rozdawanie początkowych kart..." << std::endl;
    for (int i = 0; i < iloscGraczy; i++) {
          std::cout << "Siemanko`" << std::endl;
        if (dynamic_cast<Bot*>(gracze[i]) != nullptr) { 
            std::cout << "Siemanko" << std::endl;
           imionaGraczy[i] = dynamic_cast<Bot*>(gracze[i])->nadajIdentyfikator();
           std::cout<< "Imiona Graczy : " << imionaGraczy[i] << std::endl;
        } else {
            imionaGraczy[i] = getPlayerName(i + 1);
              std::cout << "Siemanko2" << std::endl; // W pozostałych przypadkach, pobierz nazwę gracza od użytkownika
        }
        for (int j = 0; j < 2; j++) {
              std::cout << "Siemanko4" << std::endl;
            gracze[i]->wezKarte(dajKarte()); // Wywołanie metody przez wskaźnik
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
            std::cin.clear(); // Czyścimy błąd flagi cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Usuwamy resztę wprowadzonych danych
        }
    } while (true);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Usuwamy zbędne nowe linie z bufora
    return numberOfPlayers;
}

std::string Kasyno::getPlayerName(int playerNumber) {
    std::string playerName;
    do {
        std::cout << "Podaj nazwę gracza " << playerNumber << " (maksymalnie 20 znaków): ";
        std::cin >> playerName;
        std::cout << "Player Name : " << playerName << std::endl;
        if (!playerName.empty() && playerName.length() <= 20) {
            break; // Poprawne dane, kończymy pętlę
        } else {
            std::cout << "Nazwa gracza nie może być pusta ani przekraczać 20 znaków. Wprowadź nazwę gracza ponownie." << std::endl;
        }
    } while (true);
    std::cout<< "Player Name : " << playerName << std::endl;
    return playerName;
}

void Kasyno::dodajBoty() {
    int iloscBotow;
    std::cout << "Podaj ilość botów do dodania: ";
    std::cin >> iloscBotow;

    // Czyszczenie bufora wejścia
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Tworzenie nowej tablicy imion graczy
    std::string* noweImionaGraczy = new std::string[iloscGraczy + iloscBotow];

    for (int i = 0; i < iloscGraczy; ++i) {
        noweImionaGraczy[i] = imionaGraczy[i]; // Kopiowanie istniejących imion
    }

    // Usuwanie starej tablicy imion graczy
    delete[] imionaGraczy;

    // Przypisanie nowej tablicy imion graczy
    imionaGraczy = noweImionaGraczy;

    for (int i = iloscGraczy; i < iloscGraczy + iloscBotow; ++i) {
        int typGracza;
        do {
            std::cout << "Wybierz typ gracza komputerowego (1 - ryzykujący, 2 - normalny, 3 - zachowawczy): ";
            std::cin >> typGracza;
            // Czyszczenie bufora wejścia
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (typGracza < 1 || typGracza > 3);
        
        std::cout << "Dodawanie gracza komputerowego " << i + 1 << "..." << std::endl;
        gracze[i] = stworzGraczaKomputerowego(typGracza);
        std::cout << "Dodano gracza komputerowego " << i + 1 << " (" << dynamic_cast<Bot*>(gracze[i])->nadajIdentyfikator() << ")" << std::endl;
        imionaGraczy[i] = "Bot" + std::to_string(i + 1);
        std::cout << "Imię gracza komputerowego " << i + 1 << ": " << imionaGraczy[i] << std::endl;
    }

    iloscGraczy += iloscBotow;
    std::cout << "Ilosc Graczy : "  << iloscGraczy<<std::endl; // Aktualizacja liczby graczy w kasynie
}

Gracz* Kasyno::stworzGraczaKomputerowego(int typGracza) {
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
            limitPunktow = 17; // Domyślny limit punktów dla gracza normalnego
            break;
    }
    return new Bot(limitPunktow); 
}

Kasyno::~Kasyno() {
    for (int i = 0; i < rozmiarTalii; i++) {
        delete talia[i];
    }
    delete[] gracze;
    delete[] imionaGraczy;
}
