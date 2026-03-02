#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include <stdexcept>
using namespace std;

class Angajat {
protected:
    const int id;
    string nume;
    string prenume;
    string cnp;
    string oras;
    tm data_angajare{};
    
    static const double salariu_baza;
    static bool verificare_nume_prenume(const string&);
    static bool verificare_cnp(const string&);
    int vechime() const;
    double bonus_fidelitate() const; 
    double prima_transport() const; 
    int varsta_la_angajare() const;

public:
    Angajat(int, const string&, const string&, const string&, const string&, const tm&);
    void set_nume(const string&);
    void set_prenume(const string&);
    int get_id() const; 
    string get_cnp() const;
    virtual double salariu() const = 0;
    virtual string tip() const = 0;
    virtual void afisare() const;
    string get_nume() const;
    string get_prenume() const;
    double get_salariu() const;
    virtual ~Angajat()=default;
};
