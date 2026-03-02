#include "Frigider.h"

Frigider::Frigider(const string &m, const string &md, int an, double pret, bool congelator)
    : Electrocasnic("Frigider", m, md, an, pret), are_congelator(congelator) {}

bool Frigider::get_congelator() const
{
    return are_congelator;
}

string Frigider::areCongelator() const
{
    if (are_congelator)
        return "DA";
    else
        return "NU";
}

void Frigider::afisare() const
{
    cout << "Frigider: \n";
    cout << "Marca si model: " << marca << " " << model << "\n";
    cout << "An: " << an_fabricatie << "\n";
    cout << "Pret: " << pret_catalog << "\n";
    cout << "Are congelator?" << areCongelator() << "\n";
}