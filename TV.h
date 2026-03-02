#pragma once
#include "Electrocasnic.h"

class TV:public Electrocasnic{
    double diagonala;
    string unitate; 

public:
    TV(const string&, const string&, int, double, double, const string&);
    double getDiagonala() const;
    string getUnitate() const;
    void afisare() const override;
    ~TV() override = default;
    
};