#pragma once
#include "TypeTable.hpp"
#include <algorithm>

class TypeManager {
public:
    /**
     * Devuelve la prioridad de un tipo según su ID.
     * Si el tipo es inválido (id < 0), retorna 0.
     */
    static int priority(const TypeTable &TT, int typeId) {
        if (typeId < 0) return 0;
        return typeId; 
    }

    // =============================================================
    //  Implementación directa en el .hpp
    // =============================================================

    /**
     * Obtiene el tipo de mayor prioridad usando la tabla de tipos.
     * Si alguno es inválido, retorna -1.
     */
    static int maxType(const TypeTable &TT, int t1, int t2) {
        int p1 = priority(TT, t1);
        int p2 = priority(TT, t2);
        if (p1 == 0 || p2 == 0) return -1;
        return (p1 >= p2) ? t1 : t2;
    }

    /**
     * Obtiene el mayor tipo solo comparando IDs.
     */
    static int maxType(int t1, int t2) {
        return (t1 >= t2) ? t1 : t2;
    }

    /**
     * Obtiene el tipo de menor prioridad usando la tabla de tipos.
     * Si alguno es inválido, retorna -1.
     */
    static int minType(const TypeTable &TT, int t1, int t2) {
        int p1 = priority(TT, t1);
        int p2 = priority(TT, t2);
        if (p1 == 0 || p2 == 0) return -1;
        return (p1 <= p2) ? t1 : t2;
    }

    /**
     * Obtiene el menor tipo solo comparando IDs.
     */
    static int minType(int t1, int t2) {
        return (t1 <= t2) ? t1 : t2;
    }

    /**
     * Regla de ampliación de tipos.
     * Si ambos tipos son iguales, se conserva; si no, se retorna tipo2.
     */
    static int amplify(int dir, int tipo1, int tipo2) {
        if (tipo1 == tipo2) return tipo1;
        return tipo2; 
    }

    /**
     * Regla de reducción de tipos.
     * Si ambos son iguales, se conserva; si no, se retorna tipo2.
     */
    static int reduce(int dir, int tipo1, int tipo2) {
        if (tipo1 == tipo2) return tipo1;
        return tipo2;
    }

    /**
     * Alias en español para hacerlo compatible con las pruebas.
     */
    static int ampliar(int dir, int t1, int t2) { return amplify(dir, t1, t2); }
    static int reducir(int dir, int t1, int t2) { return reduce(dir, t1, t2); }
};
