#include "Electrocasnic.h"

Electrocasnic::Electrocasnic(const string &t, const string &m, const string &md, int an, double pret)
    : tip(t), marca(m), model(md), an_fabricatie(an), pret_catalog(pret) {}

string Electrocasnic::get_tip() const
{
     return tip;
}

string Electrocasnic::get_marca() const
{
     return marca;
}

string Electrocasnic::get_model() const
{
     return model;
}

int Electrocasnic::get_an_fabricatie() const
{
     return an_fabricatie;
}

double Electrocasnic::get_pret_catalog() const
{
     return pret_catalog;
}

string Electrocasnic::cheie() const
{
     return tip + "_" + marca + "_" + model;
}
