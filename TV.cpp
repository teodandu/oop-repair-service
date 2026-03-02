#include "TV.h"

TV::TV(const string &m, const string &md, int an, double pret, double diag, const string &unit)
    : Electrocasnic("TV", m, md, an, pret), diagonala(diag), unitate(unit) {}

double TV::getDiagonala() const
{
    return diagonala;
}

string TV::getUnitate() const
{
    return unitate;
}

void TV::afisare() const
{
    cout << "TV: \n";
    cout << "Marca si model: " << marca << " " << model << "\n";
    cout << "An: " << an_fabricatie << "\n";
    cout << "Pret: " << pret_catalog << "\n";
    cout << "Diagonala: " << diagonala << " " << unitate << "\n";
}

