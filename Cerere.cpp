#include "Cerere.h"

Cerere::Cerere(int i, const string &t, const string &m, const string &md, const string &ts)
    : id(i), tip(t), marca(m), model(md), timestamp(ts) {}

void Cerere::seteaza_parametri(int comp, int an_fabricatie, double pret_catalog, int an_curent)
{
    complexitate = comp;
    int vechime = an_curent - an_fabricatie;
    if (vechime < 0)
        vechime = 0;
    durata_estimata = vechime * complexitate;
    durata_ramasa = durata_estimata;
    pret_reparatie = pret_catalog * durata_estimata;
}

void Cerere::cerere_invalida()
{
    status = 0;
}

void Cerere::incepere_reparatie()
{
    if (status == 1)
        status = 2;
}

void Cerere::simulare_trecere_timp()
{
    if (status != 2)
        return;

    if (durata_ramasa > 0)
        durata_ramasa--;

    if (durata_ramasa == 0)
        status = 3;
}

bool Cerere::finalizare_reparatie() const
{
    return status == 3;
}

int Cerere::get_id() const
{
    return id;
}

string Cerere::get_tip() const
{
    return tip;
}

string Cerere::get_marca() const
{
    return marca;
}

string Cerere::get_model() const
{
    return model;
}

string Cerere::get_timestamp() const
{
    return timestamp;
}

int Cerere::get_complexitate() const
{
    return complexitate;
}

int Cerere::get_durata_estimata() const
{
    return durata_estimata;
}

int Cerere::get_durata_ramasa() const
{
    return durata_ramasa;
}

double Cerere::get_pret_reparatie() const
{
    return pret_reparatie;
}

int Cerere::get_status() const
{
    return status;
}
