#include "Interval.hpp"

// Définition des constantes statiques
const Interval Interval::empty =
    Interval(+std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
const Interval Interval::universe =
    Interval(-std::numeric_limits<double>::infinity(), +std::numeric_limits<double>::infinity());
