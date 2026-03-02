#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Angajat.h"
#include "Tehnician.h"
#include "Receptioner.h"
#include "Supervizor.h"
using namespace std;


class GestiuneAngajati{
    private:
              vector<Angajat*> angajati;
    public:
               GestiuneAngajati()=default;
               GestiuneAngajati(const GestiuneAngajati&)=delete;
               GestiuneAngajati& operator=(const GestiuneAngajati&)=delete;
               void adauga_angajat(Angajat* a);
               bool sterge_angajat(int id);
               Angajat* cauta_dupa_cnp(const string& cnp) const;
               void afiseaza_dupa_cnp(const string&) const;
               void afisare_lista() const;
               bool service_functional() const;
               ~GestiuneAngajati();


};