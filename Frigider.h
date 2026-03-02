#pragma once
#include "Electrocasnic.h"

class Frigider:public Electrocasnic{
    bool are_congelator;

public:
    Frigider(const string&, const string&, int, double, bool);
    bool get_congelator() const;
    string areCongelator() const;
    void afisare() const override;
    ~Frigider() override = default;
};
