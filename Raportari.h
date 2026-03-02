#pragma once
#include <stdexcept>
#include "Angajat.h"
#include "Tehnician.h"
#include "ProcesareCereri.h"

class Raportari{
public:
    static void top_angajati(const vector<Angajat*>&, const string&);
    static void top_tehnician_durata(ProcesareCereri&, const string&);
    static void cereri_asteptare(const vector<Cerere*>&, const string&);
};