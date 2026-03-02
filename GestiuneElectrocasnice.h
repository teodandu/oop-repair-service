#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Electrocasnic.h"
using namespace std;


class GestiuneElectrocasnice{
    private:
            vector<Electrocasnic*> electrocasnice; 

    public:
            GestiuneElectrocasnice() = default;
            GestiuneElectrocasnice(const GestiuneElectrocasnice&) = delete;
            GestiuneElectrocasnice& operator=(const GestiuneElectrocasnice&) = delete;
            void adauga(Electrocasnic*); 
            bool sterge(const string&, const string&, const string&);
            Electrocasnic* cauta_electrocasnic(const string&, const string&, const string&) const;
            void afisare_reparabile() const;
            ~GestiuneElectrocasnice();

};