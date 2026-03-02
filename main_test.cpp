#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Angajat.h"
#include "Receptioner.h"
#include "Tehnician.h"
#include "Competente.h"
#include "Supervizor.h"
#include "Frigider.h"
#include "TV.h"
#include "MasinaSpalat.h"
#include "GestiuneElectrocasnice.h"
#include "ProcesareCereri.h"
#include "Raportari.h"
using namespace std;

static tm make_date(int an, int luna, int zi)
{
    tm t{};
    t.tm_year = an - 1900;
    t.tm_mon = luna - 1;
    t.tm_mday = zi;
    return t;
}

static void trim_end(string &s)
{
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ' || s.back() == '\t'))
        s.pop_back();
}

static vector<string> split_csv(const string &linie)
{
    vector<string> rezultat;
    string camp;
    stringstream ss(linie);
    while (getline(ss, camp, ','))
    {
        trim_end(camp);
        rezultat.push_back(camp);
    }
    return rezultat;
}

static vector<Competente> competente_default(int id)
{
    if (id % 3 == 0)
        return {Competente("TV", "LG"), Competente("MasinaSpalat", "Beko")};
    if (id % 3 == 1)
        return {Competente("TV", "Samsung"), Competente("Frigider", "Samsung")};
    return {Competente("Frigider", "LG"), Competente("MasinaSpalat", "Arctic")};
}

static void citire_angajati_csv(const string &fisier, vector<Angajat*> &ang, vector<Tehnician*> &tehnicieni,
                                Receptioner *&receptioner, Supervizor *&supervizor)
{

    ifstream fin(fisier);
    if (!fin)
        throw invalid_argument("Fisierul nu poate fi deschis!");

    string linie;
    int nr_linie = 0;

    if (getline(fin, linie))
        nr_linie++;

    while (getline(fin, linie))
    {
        nr_linie++;
        if (linie.empty())
            continue;

        auto f = split_csv(linie);

        if ((int)f.size() < 9)
        {
            cout << "Eroare " << fisier << " linia " << nr_linie << ": format gresit (campuri insuficiente)\n";
            continue;
        }

        try
        {
            int id = stoi(f[0]);
            string nume = f[1];
            string prenume = f[2];
            string cnp = f[3];
            string oras = f[4];

            int zi = stoi(f[5]);
            int luna = stoi(f[6]);
            int an = stoi(f[7]);

            string tip = f[8];
            trim_end(tip);

            tm data = make_date(an, luna, zi);

            if (tip == "Receptioner")
            {
                auto *r = new Receptioner(id, nume, prenume, cnp, oras, data);
                ang.push_back(r);
                if (!receptioner)
                    receptioner = r;
            }
            else if (tip == "Tehnician")
            {
                auto *t = new Tehnician(id, nume, prenume, cnp, oras, data, competente_default(id));
                ang.push_back(t);
                tehnicieni.push_back(t);
            }
            else if (tip == "Supervizor")
            {
                auto *s = new Supervizor(id, nume, prenume, cnp, oras, data);
                ang.push_back(s);
                if (!supervizor)
                    supervizor = s;
            }
            else
            {
                cout << "Eroare " << fisier << " linia " << nr_linie << ": tip necunoscut\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Eroare " << fisier << " linia " << nr_linie << ": " << e.what() << "\n";
        }
    }
}

static void eliberare_angajati(vector<Angajat*> &ang, vector<Tehnician*> &tehnicieni, Receptioner *&receptioner,
                               Supervizor *&supervizor)
{

    for (auto a : ang)
        delete a;
    ang.clear();
    tehnicieni.clear();
    receptioner = nullptr;
    supervizor = nullptr;
}

int main()
{
    cout << "Test Service FixItNow\n";

    cout << "Test: angajati_gresiti.csv\n";
    vector<Angajat*> ang_bad;
    vector<Tehnician*> tehn_bad;
    Receptioner *rec_bad = nullptr;
    Supervizor *sup_bad = nullptr;

    try
    {
        citire_angajati_csv("tests/angajati_gresiti.csv", ang_bad, tehn_bad, rec_bad, sup_bad);
    }
    catch (const exception &e)
    {
        cout << "Eroare la deschidere: " << e.what() << "\n";
    }
    cout << "Creati (din fisier gresit): " << ang_bad.size() << " angajati\n\n";
    eliberare_angajati(ang_bad, tehn_bad, rec_bad, sup_bad);

    cout << "Test: angajati.csv\n";
    vector<Angajat*> ang;
    vector<Tehnician*> tehnicieni;
    Receptioner *receptioner = nullptr;
    Supervizor *supervizor = nullptr;

    try
    {
        citire_angajati_csv("tests/angajati.csv", ang, tehnicieni, receptioner, supervizor);
    }
    catch (const exception &e)
    {
        cout << "Eroare la deschidere: " << e.what() << "\n";
    }

    cout << "Angajati: " << ang.size() << "\n";
    cout << "Tehnicieni: " << tehnicieni.size() << "\n";
    cout << "Receptioner: " << (receptioner ? "DA" : "NU") << "\n";
    cout << "Supervizor: " << (supervizor ? "DA" : "NU") << "\n\n";

    if (tehnicieni.size() < 3 || !receptioner || !supervizor)
    {
        cout << "Service-ul NU poate functiona.\n";
        eliberare_angajati(ang, tehnicieni, receptioner, supervizor);
        return 0;
    }

    GestiuneElectrocasnice gestiune;
    gestiune.adauga(new Frigider("Samsung", "Frost200", 2022, 3200, true));
    gestiune.adauga(new Frigider("LG", "CoolMax", 2021, 2800, false));
    gestiune.adauga(new TV("Samsung", "Q80C", 2023, 3500, 55, "inci"));
    gestiune.adauga(new TV("LG", "Nano77", 2022, 2400, 139, "cm"));
    gestiune.adauga(new MasinaSpalat("Arctic", "Wash7", 2020, 1700, 7));
    gestiune.adauga(new MasinaSpalat("Beko", "Clean9", 2021, 1900, 9));

    cout << "Electrocasnice reparabile:\n";
    gestiune.afisare_reparabile();
    cout << "\n";

    ProcesareCereri procesare;
    try
    {
        procesare.citire_fisier("tests/cereri.txt", *receptioner, gestiune);
    }
    catch (const exception &e)
    {
        cout << "Eroare la citire cereri: " << e.what() << "\n";
    }

    cout << "Simulare (10 tics)\n\n";
    procesare.simulare_cereri(tehnicieni, 10);

    try
    {
        Raportari::top_angajati(ang, "raport_top_angajati.csv");
        Raportari::top_tehnician_durata(procesare, "raport_top_tehnician_durata.csv");
        Raportari::cereri_asteptare(procesare.get_cereri_asteptare(), "raport_cereri_asteptare.csv");
        cout << "Rapoarte generate.\n";
    }
    catch (const exception &e)
    {
        cout << "Eroare la raportari: " << e.what() << "\n";
    }

    eliberare_angajati(ang, tehnicieni, receptioner, supervizor);
    cout << "Test gata\n";
    return 0;
}
