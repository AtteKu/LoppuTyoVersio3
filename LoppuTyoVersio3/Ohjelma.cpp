// Atte Kukkonen
// Harjoitustyö 2024, C++-ohjelmoinnin perusteet, TAMK, testi


#include <iostream>
#include <locale>
#include <vector>
#include <numeric>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <limits>
#include <fstream>

// Rakenteen määrittely, joka sisältää varauksen tiedot
struct Varaus {
    int varausnumero;
    int huonenumero;
    std::string varaajannimi;
    int yot;
    double hinta;
};

// Tarkistaa, onko varaukset-tiedosto olemassa ja luo sen, jos ei ole
void luoVarauksetTiedosto(const std::string& tiedostonimi) {
    std::ifstream tiedosto(tiedostonimi);
    if (!tiedosto) {
        std::ofstream uusiTiedosto(tiedostonimi);
        if (uusiTiedosto) {
            uusiTiedosto << "Varausnumero Huonenumero Varaajannimi Yot Hinta\n";
            std::cout << "Luodaan uusi tiedosto: " << tiedostonimi << std::endl;        
        }
    }
}

// Muuntaa merkkijonon pieniksi kirjaimiksi
std::string muunnaPieniksiKirjaimiksi(const std::string& merkkijono) {
    std::string tulos = merkkijono;
    std::transform(tulos.begin(), tulos.end(), tulos.begin(), ::tolower);
    return tulos;
}


// Tallentaa varaukset tiedostoon
void tallennaVaraukset(const std::vector<Varaus>& varaukset, const std::string& tiedostonimi) {
    std::ofstream tiedosto(tiedostonimi);
    if (!tiedosto) {
        std::cout << "Tiedoston avaaminen epäonnistui tallentamista varten.\n";
        return;
    }
    tiedosto << "Varausnumero Huonenumero Varaajannimi Yot Hinta\n";
    for (const auto& varaus : varaukset) {
        tiedosto << varaus.varausnumero << " " << varaus.huonenumero << " " << "\"" << varaus.varaajannimi << "\"" << " " << varaus.yot << " " << varaus.hinta << "\n";
    }
}

// Lukee varaukset tiedostosta
void lueVaraukset(std::vector<Varaus>& varaukset, const std::string& tiedostonimi) {
    std::ifstream tiedosto(tiedostonimi);
    if (!tiedosto) {
        std::cout << "Tiedoston avaaminen epäonnistui lukemista varten.\n";
        return;
    }
    std::string otsikkorivi;
    std::getline(tiedosto, otsikkorivi);

    Varaus varaus;
    std::string nimi;

    // Luetaan varauksen tiedot tiedostosta
    while (tiedosto >> varaus.varausnumero >> varaus.huonenumero >> std::ws && std::getline(tiedosto, varaus.varaajannimi, '"') && std::getline(tiedosto, varaus.varaajannimi, '"') && tiedosto >> varaus.yot >> varaus.hinta) {
        varaukset.push_back(varaus);
    }
}

// Tarkistaa, onko huone varattu
bool onkoVarattu(int huonenumero, const std::vector<Varaus>& varaukset) {
    for (const auto& varaus : varaukset) {
        if (varaus.huonenumero == huonenumero) {
            return true;
        }
    }
    return false;
}

// Luo sattunaisen varausnumeron
int luoVarausnumero() {
    return rand() % 90000 + 10000; // Arpoo varausnumeron välillä 10000-99999
}


// Lisää uuden varauksen ja poistaa varatun huonenumero vapaiden huoneiden listasta
void lisaaVaraus(int huonenumero, const std::string& nimi, int yot, double hinta, std::vector<Varaus>& varaukset, std::vector<int>& vapaatHuoneet) {
    Varaus uusiVaraus;
    uusiVaraus.varausnumero = luoVarausnumero();
    uusiVaraus.huonenumero = huonenumero;
    uusiVaraus.varaajannimi = nimi;
    uusiVaraus.yot = yot;
    uusiVaraus.hinta = hinta;
    varaukset.push_back(uusiVaraus);
    std::cout << "Varaus tehty onnistuneesti! Varausnumero: " << uusiVaraus.varausnumero << "\n";

    // Poistetaan varattu huonenumero vapaiden huoneiden listasta
    vapaatHuoneet.erase(std::remove(vapaatHuoneet.begin(), vapaatHuoneet.end(), huonenumero), vapaatHuoneet.end());
}

// Hakee varausta varausnumeron perusteella
bool haeVarausnumerolla(int varausnumero, const std::vector<Varaus>& varaukset) {
    for (const auto& varaus : varaukset) {
        if (varaus.varausnumero == varausnumero) {
            std::cout << "Varausnumero: " << varaus.varausnumero << "\nVaraajan nimi: " << varaus.varaajannimi << "\nHuonenumero: " << varaus.huonenumero << "\nYöt: " << varaus.yot << "\nHinta: " << varaus.hinta << " euroa" << std::endl;
            return true;
        }
    }
    std::cout << "Varausta ei löytynyt.\n";
    return false;
}

// Hakee varausta varaajan nimen perusteella
void haeNimella(const std::string& nimi, const std::vector<Varaus>& varaukset) {
    bool found = false;
    std::string nimiPienilla = muunnaPieniksiKirjaimiksi(nimi);
    for (const auto& varaus : varaukset) {
        if (muunnaPieniksiKirjaimiksi(varaus.varaajannimi) == nimiPienilla) {
            std::cout << "Varausnumero: " << varaus.varausnumero << "\nVaraajan nimi: " << varaus.varaajannimi << "\nHuonenumero: " << varaus.huonenumero << "\nYöt: " << varaus.yot << "\nHinta: " << varaus.hinta << " euroa\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Varausta ei löytynyt.\n";
    }
}

// Lukee kokonaisluvun ja käsittelee mahdolliset syötteen virheet
bool lueKokonaisluku(int& luku) {
    std::cin >> luku;
    if (std::cin.fail()) {
        std::cin.clear(); // Palauta cin virheettömään tilaan
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tyhjennä syötepuskurin virheellinen syöte
        return false;
    }
    return true;
}

// Arpoo satunnaisen alennuksen (0%, 10%, 20%)
double Alennus() {
    int alennusProsentti = rand() % 3 * 10; // 0, 10 tai 20 prosenttia
    return 1.0 - alennusProsentti / 100.0;
}

int main() {
    std::setlocale(LC_ALL, "Finnish_Finland.1252"); // Saadaan ääkköset käyttöön

    srand(time(0)); // Alusta satunnaislukugeneraattori

    // Tarkistetaan, onko varaukset-tiedosto olemassa, ja luodaan se tarvittaessa 
    luoVarauksetTiedosto("varaukset.txt");

    int huoneiden_lukumaara = (rand() % 131 + 20) * 2; // Tuotetaan satunnainen parillinen luku välillä 40-300
    std::cout << "Huoneiden lukumäärä: " << huoneiden_lukumaara << std::endl;

    std::vector<int> yhdenHengenHuoneet(huoneiden_lukumaara / 2);
    std::vector<int> kahdenHengenHuoneet(huoneiden_lukumaara / 2);

    


    // Täytetään yhden ja kahden hengen huoneiden vektorit
    std::iota(yhdenHengenHuoneet.begin(), yhdenHengenHuoneet.end(), 1);
    std::iota(kahdenHengenHuoneet.begin(), kahdenHengenHuoneet.end(), huoneiden_lukumaara / 2 + 1);

    std::cout << "Yhden hengen huoneita: " << yhdenHengenHuoneet.size() << std::endl;
    std::cout << "Kahden hengen huoneita: " << kahdenHengenHuoneet.size() << std::endl;

    int huonenumero;
    int yot;
    std::string varaajannimi;
    std::vector<Varaus> varaukset;

    // Luetaan varaukset tiedostosta
    lueVaraukset(varaukset, "varaukset.txt");

    // Päävalikko
    std::cout << "Liiku valikoissa antamalla haluttua toimintoa vastaava numero ja paina sen jälkeen Enter-näppäintä\n";
    while (true) {
        std::cout << "(1) Tee varaus\n(2) Hae varauksia\n(3) Sulje ohjelma\n";
        int valinta;
        if (!lueKokonaisluku(valinta) || (valinta < 1 || valinta > 3)) {
            std::cout << "Virheellinen syöte. Valitse vaihtoehto 1, 2 tai 3." << std::endl;
            continue;
        }

        if (valinta == 1) { // Varauksen teko
            while (true) {
                std::cout << "Valitse huonetyyppi: (1) Yhden hengen huone (Huoneet välillä " << yhdenHengenHuoneet.front() << " - " << yhdenHengenHuoneet.back() << "), (2) Kahden hengen huone (Huoneet välillä " << kahdenHengenHuoneet.front() << " - " << kahdenHengenHuoneet.back() << "), (3) Palaa päävalikkoon\n";

                int huonetyyppi;
                if (!lueKokonaisluku(huonetyyppi) || (huonetyyppi < 1 || huonetyyppi > 3)) {
                    std::cout << "Virheellinen syöte. Valitse vaihtoehto 1, 2 tai 3." << std::endl;
                    continue;
                }

                if (huonetyyppi == 3) { // Palaa päävalikkoon
                    break;
                }

                // Valitaan huoneen valintatapa
                std::cout << "Haluatko valita huoneen itse (1), arvotaanko se (2), vai palaa päävalikkoon (3)?\n";
                int valintatapa;
                if (!lueKokonaisluku(valintatapa) || (valintatapa < 1 || valintatapa > 3)) {
                    std::cout << "Virheellinen syöte. Valitse vaihtoehto 1, 2 tai 3." << std::endl;
                    continue;
                }

                if (valintatapa == 3) {
                    break; // Palaa päävalikkoon
                }

                // Käyttäjä valitsee huoneen itse
                if (valintatapa == 1) {
                    std::cout << "Anna haluamasi huonenumero: ";
                    if (!lueKokonaisluku(huonenumero)) {
                        std::cout << "Virheellinen syöte. Syötteen täytyy olla kokonaisluku." << std::endl;
                        continue;
                    }
                    if ((huonetyyppi == 1 && std::find(yhdenHengenHuoneet.begin(), yhdenHengenHuoneet.end(), huonenumero) == yhdenHengenHuoneet.end()) ||
                        (huonetyyppi == 2 && std::find(kahdenHengenHuoneet.begin(), kahdenHengenHuoneet.end(), huonenumero) == kahdenHengenHuoneet.end())) {
                        std::cout << "Valitsemaasi huonetta ei ole saatavilla. Yritä uudelleen." << std::endl;
                        continue;
                    }
                }
                else { // Kone arpoo huoneen
                    if (huonetyyppi == 1 && !yhdenHengenHuoneet.empty()) {
                        int index = rand() % yhdenHengenHuoneet.size();
                        huonenumero = yhdenHengenHuoneet[index];
                        yhdenHengenHuoneet.erase(yhdenHengenHuoneet.begin() + index);
                    }
                    else if (huonetyyppi == 2 && !kahdenHengenHuoneet.empty()) {
                        int index = rand() % kahdenHengenHuoneet.size();
                        huonenumero = kahdenHengenHuoneet[index];
                        kahdenHengenHuoneet.erase(kahdenHengenHuoneet.begin() + index);
                    }
                    else {
                        std::cout << "Valitsemasi huonetyyppi on loppu. Yritä uudelleen." << std::endl;
                        continue;
                    }
                }

                std::cin.ignore(); // Tyhjennä syötepuskurin uusiin syötteisiin

                // Kysytään varaajan nimi
                do { 
                    std::cout << "Anna varaajan nimi: " << std::endl;
                    std::getline(std::cin, varaajannimi);
                    if (varaajannimi.empty()) {
                        std::cout << "Nimi ei voi olla tyhjä. Yritä uudelleen." << std::endl;
                    }
                } while (varaajannimi.empty());

                // Kysytään öiden määrä
                while (true) {
                    std::cout << "Monta yötä vietätte huoneessanne? " << std::endl;
                    if (!lueKokonaisluku(yot)) {
                        std::cout << "Virheellinen syöte. Syötteen täytyy olla kokonaisluku." << std::endl;
                    }
                    else {
                        break;
                    }
                }

                // Lasketaan hinta ja alennus
                double perYovuorokausi = (huonetyyppi == 1) ? 100.0 : 150.0;
                double hintaEnnenAlennusta = yot * perYovuorokausi;
                double alennuskerroin = Alennus();
                double loppusumma = hintaEnnenAlennusta * alennuskerroin;

                std::cout << "Kokonaishintasi on " << loppusumma << " euroa (alennus " << (1 - alennuskerroin) * 100 << "%)\n";

                // Lisätään varaus
                if (huonetyyppi == 1) {
                    lisaaVaraus(huonenumero, varaajannimi, yot, loppusumma, varaukset, yhdenHengenHuoneet);
                }
                else {
                    lisaaVaraus(huonenumero, varaajannimi, yot, loppusumma, varaukset, kahdenHengenHuoneet);
                }

                // Kysytään käyttäjältä halutaanko tehdä toinen varaus
                char jatka;
                while (true) {
                    std::cout << "Haluatko varata toisen huoneen? (k/e) " << std::endl;
                    std::cin >> jatka;
                    if (jatka == 'k' || jatka == 'K') {
                        break;
                    }
                    else if (jatka == 'e' || jatka == 'E') {
                        break;
                    }
                    else {
                        std::cout << "Virheellinen valinta. Yritä uudelleen." << std::endl;
                    }
                }
                if (jatka == 'e' || jatka == 'E') {
                    break; // Palaa päävalikkoon
                }
            }
        }
        else if (valinta == 2) { // Varauksien haku
            while (true) {
                std::cout << "Haku varausnumerolla (1) tai nimellä (2), tai Palaa päävalikkoon (3): " << std::endl;
                int hakutyyppi;
                if (!lueKokonaisluku(hakutyyppi) || (hakutyyppi < 1 || hakutyyppi > 3)) {
                    std::cout << "Virheellinen syöte. Valitse vaihtoehto 1, 2 tai 3." << std::endl;
                    continue;
                }
                if (hakutyyppi == 3) {
                    break;
                }
                if (hakutyyppi == 1) {
                    while (true) {
                        std::cout << "Anna varausnumero: " << std::endl;
                        int varausnumero;
                        if (!lueKokonaisluku(varausnumero) || !haeVarausnumerolla(varausnumero, varaukset)) {
                            std::cout << "Haluatko yrittää uudelleen? (k/e): " << std::endl;
                            char uudelleen;
                            std::cin >> uudelleen;
                            if (uudelleen == 'e' || uudelleen == 'E') {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
                else if (hakutyyppi == 2) {
                    std::cout << "Anna varaajan nimi: " << std::endl;
                    std::cin.ignore(); // Varmistaa, että syötepuskurin virheellinen syöte tyhjennetään ennen uuden rivin lukemista
                    std::getline(std::cin, varaajannimi); // Luetaan varaajan nimi käyttäjältä kokonaisena rivinä, jolloin mahdolliset välilyönnit säilyvät
                    haeNimella(varaajannimi, varaukset); // Kutsutaan funktiota haeNimella, joka hakee varauksen annettua nimeä
                }
                break;
            }

        }
        else if (valinta == 3) { // Ohjelman sulku
            std::cout << "Varausjärjestelmä sulkeutuu. Kiitos! " << std::endl;

            // Tallenna varaukset tiedostoon ennen ohjelman sulkemista
            tallennaVaraukset(varaukset, "varaukset.txt");

            break;
        }
    }

    return 0;
}
