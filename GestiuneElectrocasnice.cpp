#include "GestiuneElectrocasnice.h"

void GestiuneElectrocasnice::adauga(Electrocasnic *e)
{
    if (!e)
        throw invalid_argument("Nu se poate adauga un electrocasnic invalid");

    for (auto it = electrocasnice.begin(); it != electrocasnice.end(); it++)
    {
        if ((*it)->cheie() == e->cheie())
        {
            cout << "Exista deja modelul: " << e->cheie() << "\n";
            delete e;
            return;
        }
    }
    electrocasnice.push_back(e);
}

bool GestiuneElectrocasnice::sterge(const string &tip, const string &marca, const string &model)
{
    for (auto it = electrocasnice.begin(); it != electrocasnice.end(); it++)
    {
        if ((*it)->cheie() == tip + "_" + marca + "_" + model)
        {
            delete (*it);
            electrocasnice.erase(it);
            return true;
        }
    }
    return false;
}

Electrocasnic *GestiuneElectrocasnice::cauta_electrocasnic(const string &tip, const string &marca, const string &model) const
{
    for (auto it = electrocasnice.begin(); it != electrocasnice.end(); it++)
    {
        if ((*it)->cheie() == tip + "_" + marca + "_" + model)
            return (*it);
    }
    return nullptr;
}

void GestiuneElectrocasnice::afisare_reparabile() const
{
    if (electrocasnice.empty())
    {
        cout << "Nu exista electrocasnice reparabile inregistrate.\n";
        return;
    }

    cout << "Lista electrocasnice reparabile: ";
    for (auto it : electrocasnice)
    {
        it->afisare();
    }
}

GestiuneElectrocasnice::~GestiuneElectrocasnice()
{
    for (auto it : electrocasnice)
    {
        delete it;
    }
    electrocasnice.clear();
}
