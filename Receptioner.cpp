#include "Receptioner.h"

Receptioner::Receptioner(int i, const string &n, const string &p, const string &c, const string &o, const tm &data)
    : Angajat(i, n, p, c, o, data) {}

void Receptioner::inregistrare_cerere(int id)
{
    if (id <= 0)
        throw invalid_argument("Id invalid!");
    cereri_inregistrate.push_back(id);
}

double Receptioner::salariu() const
{
    return salariu_baza + bonus_fidelitate() + prima_transport();
}

string Receptioner::tip() const
{
    return "Receptioner";
}

void Receptioner::afisare() const
{
    Angajat::afisare();
    cout << "Cereri inregistrate: ";
    for (int id : cereri_inregistrate)
    {
        cout << id << " ";
    }
    cout << "\n";
}