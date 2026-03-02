#include "MasinaSpalat.h"

MasinaSpalat::MasinaSpalat(const string &m, const string &md, int an, double pret, double cap)
    : Electrocasnic("MasinaSpalat", m, md, an, pret), capacitate(cap) {}

double MasinaSpalat::get_capacitate() const
{
    return capacitate;
}

void MasinaSpalat::afisare() const
{
    cout << "Masina de spalat: \n";
    cout << "Marca si model: " << marca << " " << model << "\n";
    cout << "An: " << an_fabricatie << "\n";
    cout << "Pret: " << pret_catalog << "\n";
    cout << "Capacitate: " << capacitate << " kg\n";
}
