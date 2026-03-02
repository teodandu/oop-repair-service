#include "Raportari.h"
#include <fstream>
#include <algorithm>

void Raportari::top_angajati(const vector<Angajat *> &ang, const string &fisier)
{
    if (ang.empty())
    {
        cout << "Nu exista angajati pentru raport.\n";
        return;
    }

    vector<Angajat *> vec = ang;
    sort(vec.begin(), vec.end(), [](Angajat *x, Angajat *y)
         {
            if (x->get_salariu() != y->get_salariu())
                return x->get_salariu() > y->get_salariu();   
            if (x->get_nume() != y->get_nume())
                return x->get_nume() < y->get_nume();         
            return x->get_prenume() < y->get_prenume(); });

    ofstream fout(fisier);
    if (!fout)
        throw invalid_argument("Nu  se poate crea fisierul!");

    fout << "Nume,Prenume,Salariu\n";

    int n;
    if (vec.size() < 3)
        n = vec.size();
    else
        n = 3;

    for (int i = 0; i < n; i++)
    {
        fout << vec[i]->get_nume() << "," << vec[i]->get_prenume() << "," << vec[i]->get_salariu() << "\n";
    }

    fout.close();
}

void Raportari::top_tehnician_durata(ProcesareCereri &procesare, const string &fisier)
{
    Tehnician *t = procesare.tehnician_cu_cea_mai_lunga_reparatie();
    int durata_maxima = procesare.durata_maxima_reparatie();

    ofstream fout(fisier);
    if (!fout)
        throw invalid_argument("Nu se poate crea fisierul!");

    fout << "Id,Nume,Prenume,Durata_maxima_reparatie\n";

    if (!t)
    {
        fout << "-,-,-,0\n";
        fout.close();
        return;
    }

    fout << t->get_id() << "," << t->get_nume() << "," << t->get_prenume() << "," << durata_maxima << "\n";
    fout.close();
}

void Raportari::cereri_asteptare(const vector<Cerere *> &cereri, const string &fisier)
{
    ofstream fout(fisier);
    if (!fout)
        throw invalid_argument("Nu se poate crea fisierul!");

    fout << "Tip,Marca,Model,Nr_cereri\n";

    if (cereri.empty())
    {
        fout.close();
        return;
    }

    vector<Cerere *> vec = cereri;

    sort(vec.begin(), vec.end(), [](Cerere *x, Cerere *y)
         {
        if (x->get_tip() != y->get_tip())
            return x->get_tip() < y->get_tip();
        if (x->get_marca() != y->get_marca())
            return x->get_marca() < y->get_marca();
        return x->get_model() < y->get_model(); });

    Cerere *cerere_curenta = vec[0];
    int nr = 1;

    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i]->get_tip() == cerere_curenta->get_tip() && vec[i]->get_marca() == cerere_curenta->get_marca() &&
            vec[i]->get_model() == cerere_curenta->get_model())
        {
            nr++;
        }
        else
        {
            fout << cerere_curenta->get_tip() << "," << cerere_curenta->get_marca() << ","
                 << cerere_curenta->get_model() << "," << nr << "\n";
            cerere_curenta = vec[i];
            nr = 1;
        }
    }

    fout << cerere_curenta->get_tip() << "," << cerere_curenta->get_marca() << "," << cerere_curenta->get_model()
         << "," << nr << "\n";

    fout.close();
}