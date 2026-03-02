#pragma once
#include "Electrocasnic.h"

class MasinaSpalat:public Electrocasnic{
    double capacitate;

public:
    MasinaSpalat( const string&, const string&, int, double, double);
    double get_capacitate() const;
    void afisare() const override;
    ~MasinaSpalat() override = default;
};