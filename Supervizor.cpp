#include "Supervizor.h"

Supervizor::Supervizor(int i, const string &n, const string &p, const string &c, const string &o, const tm &data)
    : Angajat(i, n, p, c, o, data) {}

double Supervizor::salariu() const
{
    return salariu_baza + bonus_fidelitate() + prima_transport() + 0.20 * salariu_baza;
}

string Supervizor::tip() const
{
    return "Supervizor";
}

void Supervizor::afisare() const
{
    Angajat::afisare();
}