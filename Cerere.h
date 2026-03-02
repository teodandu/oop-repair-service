#pragma once
#include <iostream>
#include <string>
using namespace std;

class Cerere{
   private: 
            int id;
            string tip;
            string marca;
            string model;
            string timestamp;
            int complexitate = 0;     
            int durata_estimata = 0;  
            int durata_ramasa = 0;
            double pret_reparatie = 0.0;
            int status = 1;  //// 0-invalid, 1-asteptare, 2-in curs, 3-finalizata

   public:
            Cerere(int,const string&,const string&,const string&,const string&);
            void seteaza_parametri(int,int,double,int);
            void cerere_invalida();
            void incepere_reparatie();
            void simulare_trecere_timp();
            bool finalizare_reparatie() const;
            int get_id() const;
            string get_tip() const;
            string get_marca() const;
            string get_model() const;
            string get_timestamp() const;
            int get_complexitate() const;
            int get_durata_estimata() const;
            int get_durata_ramasa() const;
            double get_pret_reparatie() const;
            int get_status() const;

};