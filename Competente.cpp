#include "Competente.h"

Competente::Competente(const string &t, const string &m) : tip(t), marca(m) {}

string Competente::get_tip() const
{
    return tip;
}

string Competente::get_marca() const
{
    return marca;
}

string Competente::descriere() const
{
    return tip + " " + marca;
}