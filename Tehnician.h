#pragma once
#include "Angajat.h"
#include "Competente.h"
using namespace std;

class Tehnician:public Angajat{
 protected:
    vector<Competente> competente;
    double valoare_reparatii = 0.0;
public:
    Tehnician(int, const string&, const string&, const string&, const string&, const tm&, const vector<Competente>&);
    void suma_reparatii(double);
    double salariu() const override;
    string tip() const override;
    bool poate_repara(const string&, const string&) const;
    void afisare() const override;
    ~Tehnician() override = default;



};