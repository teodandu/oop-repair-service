#pragma once
#include <iostream>
#include <string>
using namespace std;

class Competente{
private:
    string tip;
    string marca;
public:
    Competente(const string&, const string&);
    string get_tip() const;
    string get_marca() const;
    string descriere() const;
};