#include "ProcesareCereri.h"

bool ProcesareCereri::exista_timestamp(const string &ts) const
{
    for (auto it : timestamps)
    {
        if (it == ts)
            return true;
    }
    return false;
}

int ProcesareCereri::an_din_timestamp(const string &ts)
{
    if (ts.size() < 4)
        return 0;
    return stoi(ts.substr(0, 4));
}

void ProcesareCereri::sortare_dupa_timestamp()
{
    sort(lista_cereri_valide.begin(), lista_cereri_valide.end(), [](Cerere *x, Cerere *y)
         { return x->get_timestamp() < y->get_timestamp(); });
}

void ProcesareCereri::init_lista_active(vector<Tehnician *> &tehnicieni)
{
    active.clear();
    for (auto t : tehnicieni)
    {
        active[t] = vector<Cerere *>();
    }
}

int ProcesareCereri::nr_cereri_active(Tehnician *t) const
{
    auto it = active.find(t);
    if (it == active.end())
        return 0;
    return (int)it->second.size();
}

int ProcesareCereri::incarcare_tehnician(Tehnician *t) const
{
    auto it = active.find(t);
    if (it == active.end())
        return 0;

    int s = 0;
    for (auto c : it->second)
    {
        s = s + c->get_durata_ramasa();
    }
    return s;
}

Tehnician *ProcesareCereri::alege_tehnician(Cerere *c, vector<Tehnician *> &tehnicieni)
{
    Tehnician *tehnician_selectat = nullptr;
    int incarcare_minima = 0;

    for (auto t : tehnicieni)
    {

        if (!t->poate_repara(c->get_tip(), c->get_marca()))
            continue;

        if (nr_cereri_active(t) >= 3)
            continue;

        int incarcare_curenta = incarcare_tehnician(t);
        if (tehnician_selectat == nullptr || incarcare_curenta < incarcare_minima)
        {
            tehnician_selectat = t;
            incarcare_minima = incarcare_curenta;
        }
    }

    return tehnician_selectat;
}

void ProcesareCereri::citire_fisier(const string &fisier, Receptioner &receptioner, const GestiuneElectrocasnice &gest_electro)
{
    ifstream fin(fisier);
    if (!fin)
        throw invalid_argument("Nu  se poate deschide fisierul de cereri!");

    string linie;
    int nr_linie = 0;

    while (getline(fin, linie))
    {
        nr_linie++;

        if (linie.empty())
            continue;

        istringstream iss(linie);

        int id, complexitate;
        string tip, marca, model, data, ora;

        if (!(iss >> id >> tip >> marca >> model >> data >> ora >> complexitate))
        {
            cout << "Eroare la citire: Cerere necorespunzatoare pe linia " << nr_linie << ", cauza: format gresit\n";
            continue;
        }

        if (complexitate < 1 || complexitate > 5)
        {
            cout << "Eroare la citire: Cerere necorespunzatoare pe linia " << nr_linie
                 << ", cauza: complexitate invalida\n";
            continue;
        }

        string ts = data + " " + ora;

        receptioner.inregistrare_cerere(id);

        Cerere *c = new Cerere(id, tip, marca, model, ts);
        if (exista_timestamp(ts))
        {
            cout << "Eroare la citire: Cerere necorespunzatoare  pe linia " << nr_linie << ", cauza: timestamp duplicat\n";
            delete c;
            continue;
        }
        timestamps.push_back(ts);

        Electrocasnic *e = gest_electro.cauta_electrocasnic(tip, marca, model);
        if (!e)
        {
            c->cerere_invalida();
            lista_cereri_invalide.push_back(c);
            cout << "Eroare la citire: Cerere invalida pe linia " << nr_linie << ", cauza: aparat necunoscut\n";
            continue;
        }

        int an_curent = an_din_timestamp(ts);
        c->seteaza_parametri(complexitate, e->get_an_fabricatie(), e->get_pret_catalog(), an_curent);

        lista_cereri_valide.push_back(c);
    }
    sortare_dupa_timestamp();

    cout << "Cereri invalide (id): ";
    if (lista_cereri_invalide.empty())
        cout << "-\n";
    else
    {
        for (auto c : lista_cereri_invalide)
            cout << c->get_id() << " ";
        cout << "\n";
    }
}

void ProcesareCereri::distribuire_cereri(int timp_curent, vector<Tehnician *> &tehnicieni)
{
    vector<Tehnician *> teh_cu_cereri;

    for (auto it = lista_cereri_valide.begin(); it != lista_cereri_valide.end();)
    {
        Cerere *c = *it;
        Tehnician *t = alege_tehnician(c, tehnicieni);

        if (t == nullptr)
        {
            it++;
            continue;
        }

        bool a_primit = false;
        for (auto x : teh_cu_cereri)
        {
            if (x == t)
            {
                a_primit = true;
                break;
            }
        }

        if (a_primit)
        {
            it++;
            continue;
        }

        active[t].push_back(c);

        cout << "[Timp " << timp_curent << "] Tehnician " << t->get_id()
             << " primeste cererea cu id " << c->get_id() << "\n";

        teh_cu_cereri.push_back(t);
        it = lista_cereri_valide.erase(it);
    }
}

void ProcesareCereri::procesare_cereri_active(int timp_curent)
{
    for (auto it = active.begin(); it != active.end(); it++)
    {
        Tehnician *t = it->first;
        vector<Cerere *> &vec = it->second;

        if (vec.empty())
            continue;

        Cerere *c = vec[0];
        if (c->get_status() == 1)
        {
            c->incepere_reparatie();
        }

        c->simulare_trecere_timp();

        if (!c->finalizare_reparatie() && c->get_status() == 2)
        {
            cout << "[Timp " << timp_curent << "] Tehnician " << t->get_id()
                 << " proceseaza cererea cu id " << c->get_id()
                 << " (raman " << c->get_durata_ramasa() << " unitati de timp)\n";
        }
    }

    for (auto it = active.begin(); it != active.end(); it++)
    {
        Tehnician *t = it->first;
        vector<Cerere *> &vec = it->second;

        if (vec.empty())
            continue;

        Cerere *c = vec[0];
        if (c->finalizare_reparatie())
        {
            cout << "[Timp " << timp_curent << "] Tehnician " << t->get_id()
                 << " finalizeaza cererea " << c->get_id() << "\n";

            t->suma_reparatii(c->get_pret_reparatie());
            lista_cereri_finalizate.push_back(c);

            reparatii_finalizate.push_back({t, c});

            vec.erase(vec.begin());
        }
    }
}

void ProcesareCereri::afisare_cereri_asteptare() const
{
    cout << "Cereri in asteptare:";
    if (lista_cereri_valide.empty())
    {
        cout << "-\n";
        return;
    }

    for (auto it = lista_cereri_valide.begin(); it != lista_cereri_valide.end(); it++)
    {
        cout << (*it)->get_id();
        if (it + 1 != lista_cereri_valide.end())
            cout << ", ";
    }
    cout << "\n";
}

void ProcesareCereri::afisare_aparate_nereparabile() const
{
    vector<string> aparate;
    for (auto a : lista_cereri_invalide)
    {
        aparate.push_back(a->get_marca() + " " + a->get_model());
    }

    cout << "Aparate nereparabile sortate dupa aparitii:\n";

    if (aparate.empty())
    {
        cout << "-\n";
        return;
    }

    sort(aparate.begin(), aparate.end());
    vector<pair<string, int>> rezultat;
    string curent = aparate[0];
    int nr = 1;

    for (int i = 1; i < aparate.size(); i++)
    {
        if (aparate[i] == curent)
        {
            nr++;
        }
        else
        {
            rezultat.push_back({curent, nr});
            curent = aparate[i];
            nr = 1;
        }
    }
    rezultat.push_back({curent, nr});

    sort(rezultat.begin(), rezultat.end(), [](const pair<string, int> &x, const pair<string, int> &y)
         { return x.second > y.second; });

    for (auto it = rezultat.begin(); it != rezultat.end(); ++it)
    {
        cout << it->first << " -> " << it->second << " aparitii\n";
    }
}

void ProcesareCereri::simulare_cereri(vector<Tehnician *> &tehnicieni, int nr_tics)
{
    init_lista_active(tehnicieni);
    sortare_dupa_timestamp();

    for (int timp = 1; timp <= nr_tics; timp++)
    {
        procesare_cereri_active(timp);
        distribuire_cereri(timp, tehnicieni);
        afisare_cereri_asteptare();
        cout << "\n";
    }
}

int ProcesareCereri::durata_maxima_reparatie() const
{
    if (reparatii_finalizate.empty())
        return 0;

    int durata_max = reparatii_finalizate[0].second->get_durata_estimata();
    for (int i = 1; i < reparatii_finalizate.size(); i++)
    {
        int durata_curenta = reparatii_finalizate[i].second->get_durata_estimata();
        if (durata_curenta > durata_max)
            durata_max = durata_curenta;
    }
    return durata_max;
}

Tehnician *ProcesareCereri::tehnician_cu_cea_mai_lunga_reparatie() const
{
    if (reparatii_finalizate.empty())
        return nullptr;

    Tehnician *teh_max = reparatii_finalizate[0].first;
    int durata_max = reparatii_finalizate[0].second->get_durata_estimata();

    for (int i = 1; i < reparatii_finalizate.size(); i++)
    {
        int durata_curenta = reparatii_finalizate[i].second->get_durata_estimata();
        if (durata_curenta > durata_max)
        {
            durata_max = durata_curenta;
            teh_max = reparatii_finalizate[i].first;
        }
    }
    return teh_max;
}

const vector<Cerere *> &ProcesareCereri::get_cereri_asteptare() const
{
    return lista_cereri_valide;
}

ProcesareCereri::~ProcesareCereri()
{
    for (auto c : lista_cereri_valide)
        delete c;
    lista_cereri_valide.clear();

    for (auto c : lista_cereri_invalide)
        delete c;
    lista_cereri_invalide.clear();

    for (auto c : lista_cereri_finalizate)
        delete c;
    lista_cereri_finalizate.clear();

    for (auto it = active.begin(); it != active.end(); it++)
    {
        it->second.clear();
    }
    active.clear();

    timestamps.clear();
}