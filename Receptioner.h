#pragma once
#include"Angajat.h"
class Receptioner:public Angajat {
protected:
    vector<int> cereri_inregistrate;   

public:
    Receptioner(int,const string&,const string&,const string&,const string&,const tm&);
    void inregistrare_cerere(int);
    double salariu() const override;
    string tip() const override;
    void afisare() const override;
    ~Receptioner() override = default;
};