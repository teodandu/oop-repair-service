#include "GestiuneAngajati.h"

void GestiuneAngajati::adauga_angajat(Angajat *a)
{
    if (!a)
        throw invalid_argument("Nu se poate adauga un angajat invalid");

    angajati.push_back(a);
}

bool GestiuneAngajati::sterge_angajat(int id)
{
    for (auto it = angajati.begin(); it != angajati.end(); it++)
    {
        if ((*it)->get_id() == id)
        {
            delete (*it);
            angajati.erase(it);
            return true;
        }
    }
    return false;
}

Angajat *GestiuneAngajati::cauta_dupa_cnp(const string &cnp) const
{
    for (auto it = angajati.begin(); it != angajati.end(); it++)
        if ((*it)->get_cnp() == cnp)
            return (*it);
    return nullptr;
}

void GestiuneAngajati::afiseaza_dupa_cnp(const string &cnp) const
{
    Angajat *a = cauta_dupa_cnp(cnp);
    if (!a)
    {
        cout << "Nu exista angajat cu acest CNP!\n";
        return;
    }
    a->afisare();
}

void GestiuneAngajati::afisare_lista() const
{
    cout << "Lista angajati: ";
    for (auto it : angajati)
    {
        it->afisare();
        cout << "\n";
    }
}

bool GestiuneAngajati::service_functional() const
{
    int nr_tehn = 0, nr_rec = 0, nr_sup = 0;

    for (auto a : angajati)
    {
        if (dynamic_cast<Tehnician *>(a))
            nr_tehn++;
        else if (dynamic_cast<Receptioner *>(a))
            nr_rec++;
        else if (dynamic_cast<Supervizor *>(a))
            nr_sup++;
    }

    return (nr_tehn >= 3 && nr_rec >= 1 && nr_sup >= 1);
}

GestiuneAngajati::~GestiuneAngajati()
{
    for (auto it : angajati)
        delete it;
    angajati.clear();
}