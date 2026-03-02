#pragma once
#include "Angajat.h"

class Supervizor:public Angajat{
public:
    Supervizor(int,const string&, const string&, const string&, const string&, const tm&);
    double salariu() const override;
    string tip() const override;
    void afisare() const override;
    ~Supervizor() override = default;

};