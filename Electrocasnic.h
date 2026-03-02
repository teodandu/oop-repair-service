#pragma once
#include <iostream>
#include <string>
using namespace std;

class Electrocasnic {
protected:
    string tip;
    string marca;
    string model;
    int an_fabricatie;
    double pret_catalog;

public:
    Electrocasnic( const string&, const string& , const string& , int , double);
    virtual void afisare() const = 0;
    string get_tip() const;
    string get_marca() const;
    string get_model() const;
    int get_an_fabricatie() const;
    double get_pret_catalog() const;
    string cheie() const; 
    virtual ~Electrocasnic() = default;

   
};
