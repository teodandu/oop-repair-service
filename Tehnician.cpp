#include "Tehnician.h"

Tehnician::Tehnician(int i, const string &n, const string &p, const string &c, const string &o, const tm &data,
                     const vector<Competente> &lista) : Angajat(i, n, p, c, o, data), competente(lista) {}

void Tehnician::suma_reparatii(double suma)
{
    if (suma > 0)
        valoare_reparatii = valoare_reparatii + suma;
}

double Tehnician::salariu() const
{
    return salariu_baza + bonus_fidelitate() + prima_transport() + 0.02 * valoare_reparatii;
}

string Tehnician::tip() const
{
    return "Tehnician";
}

bool Tehnician::poate_repara(const string &tip, const string &marca) const
{
    for (auto it = competente.begin(); it != competente.end(); it++)
    {
        if (it->get_tip() == tip && it->get_marca() == marca)
            return true;
    }
    return false;
}

void Tehnician::afisare() const
{
    Angajat::afisare();
    cout << "Competente:";
    for (auto it = competente.begin(); it != competente.end(); it++)
    {
        cout << it->descriere() << "\n";
    }
}