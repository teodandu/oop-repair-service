#include "Angajat.h"

const double Angajat::salariu_baza = 4000.0;

bool Angajat::verificare_nume_prenume(const string &n)
{
    return (n.size() >= 3 && n.size() <= 30);
}

bool Angajat::verificare_cnp(const string &c)
{
    if (c.size() != 13)
        return false;

    for (char i : c)
    {
        if (i < '0' || i > '9')
            return false;
    }

    int cifra = c[0] - '0';
    if (cifra < 1 || cifra > 8)
        return false;

    int luna = (c[3] - '0') * 10 + (c[4] - '0');
    if (luna < 1 || luna > 12)
        return false;

    int cifre_an = (c[1] - '0') * 10 + (c[2] - '0');
    int an;
    if (cifra == 1 || cifra == 2)
        an = 1900 + cifre_an;
    else if (cifra == 3 || cifra == 4)
        an = 1800 + cifre_an;
    else if (cifra == 5 || cifra == 6)
        an = 2000 + cifre_an;
    else
        an = 1900 + cifre_an;

    bool bisect = ((an % 4 == 0 && an % 100 != 0) || (an % 400 == 0));

    int zi = (c[5] - '0') * 10 + (c[6] - '0');

    int zile_luna;
    if (luna == 2)
    {
        if (bisect)
            zile_luna = 29;
        else
            zile_luna = 28;
    }
    else if (luna == 4 || luna == 6 || luna == 9 || luna == 11)
        zile_luna = 30;
    else
        zile_luna = 31;

    if (zi < 1 || zi > zile_luna)
        return false;

    int judet = (c[7] - '0') * 10 + (c[8] - '0');
    if (!((judet >= 1 && judet <= 46) || (judet == 51 || judet == 52) || (judet == 70)))
        return false;

    int nr_secvential = (c[9] - '0') * 100 + (c[10] - '0') * 10 + (c[11] - '0');
    if (nr_secvential < 1 || nr_secvential > 999)
        return false;

    int constanta[12] = {2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9};
    int s = 0;

    for (int i = 0; i < 12; i++)
    {
        s = s + (c[i] - '0') * constanta[i];
    }

    int rest = s % 11;
    int cifra_c;
    if (rest < 10)
        cifra_c = rest;
    else
        cifra_c = 1;

    if (cifra_c != (c[12] - '0'))
        return false;

    return true;
}

int Angajat::vechime() const
{
    time_t t = time(nullptr);
    tm prezent = *localtime(&t);
    int ani = prezent.tm_year - data_angajare.tm_year;
    if (prezent.tm_mon < data_angajare.tm_mon ||
        (prezent.tm_mon == data_angajare.tm_mon && prezent.tm_mday < data_angajare.tm_mday))
    {
        ani--;
    }

    if (ani < 0)
        ani = 0;
    return ani;
}

double Angajat::bonus_fidelitate() const
{
    return (vechime() / 3) * 0.05 * salariu_baza;
}

double Angajat::prima_transport() const
{
    if (oras != "Bucuresti")
        return 400;
    return 0;
}

int Angajat::varsta_la_angajare() const
{
    int cifra = cnp[0] - '0';
    int an = (cnp[1] - '0') * 10 + (cnp[2] - '0');
    int luna = (cnp[3] - '0') * 10 + (cnp[4] - '0');
    int zi = (cnp[5] - '0') * 10 + (cnp[6] - '0');

    if (cifra == 1 || cifra == 2)
        an = an + 1900;
    else if (cifra == 3 || cifra == 4)
        an = an + 1800;
    else if (cifra == 5 || cifra == 6)
        an = an + 2000;
    else
        an = an + 1900;

    int varsta = (data_angajare.tm_year + 1900) - an;
    if (data_angajare.tm_mon + 1 < luna || (data_angajare.tm_mon + 1 == luna && data_angajare.tm_mday < zi))
    {
        varsta--;
    }

    return varsta;
}

Angajat::Angajat(int i, const string &n, const string &p, const string &c, const string &o, const tm &data)
    : id(i), nume(n), prenume(p), cnp(c), oras(o), data_angajare(data)
{

    if (!(verificare_nume_prenume(n) && verificare_nume_prenume(p)))
        throw invalid_argument("Nume/prenume invalid!");
    if (!verificare_cnp(c))
        throw invalid_argument("CNP invalid!");
    if (varsta_la_angajare() < 16)
        throw invalid_argument("Nu are minim 16 ani!");
}

void Angajat::set_nume(const string &n)
{
    if (!verificare_nume_prenume(n))
        throw invalid_argument("Nume invalid!");
    nume = n;
}

void Angajat::set_prenume(const string &p)
{
    if (!verificare_nume_prenume(p))
        throw invalid_argument("Prenume invalid!");
    prenume = p;
}

int Angajat::get_id() const
{
    return id;
}

string Angajat::get_cnp() const
{
    return cnp;
}

void Angajat::afisare() const
{
    cout << "Id: " << id << "\n";
    cout << "Tip angajat: " << tip() << "\n";
    cout << "Nume si prenume: " << nume << " " << prenume << "\n";
    cout << "CNP: " << cnp << "\n";
    cout << "Oras: " << oras << "\n";
    cout << "Data angajare: " << data_angajare.tm_mday << "." << data_angajare.tm_mon + 1 << "." << data_angajare.tm_year + 1900 << "\n";
    cout << "Salariu: " << salariu() << "\n";
}

string Angajat::get_nume() const
{
    return nume;
}

string Angajat::get_prenume() const
{
    return prenume;
}

double Angajat::get_salariu() const
{
    return salariu();
}