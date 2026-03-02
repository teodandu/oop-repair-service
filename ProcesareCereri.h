#pragma once
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream> 
#include "Cerere.h"
#include "GestiuneElectrocasnice.h"
#include "Tehnician.h"
#include "Receptioner.h"


class ProcesareCereri{
    private:
             vector<Cerere*> lista_cereri_valide;   
             vector<Cerere*> lista_cereri_invalide;    
             vector<Cerere*> lista_cereri_finalizate;
             vector<string> timestamps;
             vector<pair<Tehnician*, Cerere*>> reparatii_finalizate;
             map<Tehnician*, vector<Cerere*>> active; 


            bool exista_timestamp(const string&) const;
            static int an_din_timestamp(const string&);
            void sortare_dupa_timestamp();
            void init_lista_active(vector<Tehnician*>&);
            Tehnician* alege_tehnician(Cerere*, vector<Tehnician*>&);
            int incarcare_tehnician(Tehnician*) const;
            int nr_cereri_active(Tehnician*) const;
            void distribuire_cereri(int, vector<Tehnician*>&);
            void procesare_cereri_active(int);
            void afisare_cereri_asteptare() const;
            void afisare_aparate_nereparabile() const;

    public:
            ProcesareCereri() = default;
            void citire_fisier(const string&,Receptioner&,const GestiuneElectrocasnice&);
            void simulare_cereri(vector<Tehnician*>&, int);
            Tehnician* tehnician_cu_cea_mai_lunga_reparatie() const;
            int durata_maxima_reparatie() const;
            const vector<Cerere*>& get_cereri_asteptare() const;
            ~ProcesareCereri();
};