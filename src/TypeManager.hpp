#pragma once
#include "TypeTable.hpp"
#include <algorithm>

class TypeManager {
public:
    // --- Logica de prioridad  ---
    static int priority(const TypeTable &TT, int typeId) {
        // Si no podemos consultar la tabla por alguna razon, usamos el ID
        if (typeId < 0) return 0;
        return typeId; 
    }

    // =============================================================
    // IMPLEMENTACION DIRECTA (INLINE) PARA QUE NO NECESITES .CPP
    // =============================================================

    // maxType 
    static int maxType(const TypeTable &TT, int t1, int t2) {
        int p1 = priority(TT, t1);
        int p2 = priority(TT, t2);
        if (p1 == 0 || p2 == 0) return -1;
        return (p1 >= p2) ? t1 : t2;
    }

    // maxType para los TESTS 
    static int maxType(int t1, int t2) {
        return (t1 >= t2) ? t1 : t2;
    }

    // minType 
    static int minType(const TypeTable &TT, int t1, int t2) {
        int p1 = priority(TT, t1);
        int p2 = priority(TT, t2);
        if (p1 == 0 || p2 == 0) return -1;
        return (p1 <= p2) ? t1 : t2;
    }

    // minType para los TESTS 
    static int minType(int t1, int t2) {
        return (t1 <= t2) ? t1 : t2;
    }

    // amplify 
    static int amplify(int dir, int tipo1, int tipo2) {
        if (tipo1 == tipo2) return tipo1;
        return tipo2; 
    }

    // reduce 
    static int reduce(int dir, int tipo1, int tipo2) {
        if (tipo1 == tipo2) return tipo1;
        return tipo2;
    }

    // alias
    static int ampliar(int dir, int t1, int t2) { return amplify(dir, t1, t2); }
    static int reducir(int dir, int t1, int t2) { return reduce(dir, t1, t2); }
};