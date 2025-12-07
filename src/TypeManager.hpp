#pragma once
#include "TypeTable.hpp"
#include <algorithm>

class TypeManager {
public:
    // --- Lógica estática (static) ---
    
    // Versión para producción (usa TypeTable)
    static int priority(const TypeTable &TT, int typeId) {
        if (typeId < 0) return 0;
        return typeId; 
    }

    // Versión simplificada para TESTS
    static int maxType(int t1, int t2) {
        return (t1 >= t2) ? t1 : t2;
    }

    static int minType(int t1, int t2) {
        return (t1 <= t2) ? t1 : t2;
    }
    
    // ... Asegúrate de tener aquí amplify, reduce, etc ...
    static int amplify(int dir, int t1, int t2) { return (t1 == t2) ? t1 : t2; }
    static int reduce(int dir, int t1, int t2) { return (t1 == t2) ? t1 : t2; }
};