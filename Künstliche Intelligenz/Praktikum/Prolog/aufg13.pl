% Bilde Stammfunktion stammF(Funktion, Variable, Ergebnis)
% --------------------
% Teile Polynome auf:
stammF(F_a - F_b, X, StammF_a - StammF_b) :- stammF(F_a, X, StammF_a), stammF(F_b, X, StammF_b).
stammF(F_a + F_b, X, StammF_a + StammF_b) :- stammF(F_a, X, StammF_a), stammF(F_b, X, StammF_b).
% Bilde Stammfunktionen von Polynom:
% 0
stammF(0, _, 0).
stammF(0*X, X, 0).
% c
stammF(C, X, C*X) :- number(C).
% x
stammF(X, X, 0.5*X^2).
% c*x
stammF(C*X, X, C2*X^2) :- number(C), C2 is (C*0.5).
% x^n
stammF(X^N, X, C2*X^N2) :- N2 is (N+1), C2 is (1/N2).
% c*x^n
stammF(C*X^N, X, C2*X^N2) :- number(C), N2 is (N+1), C2 is (C*(1/N2)).
% --------------------
% Setze Grenze in Stammfunktion ein grenzStammF(Funktion, Variable, Grenze, Ergebnis)
% --------------------
% Teile Stammfunktionen der Polynome auf
grenzStammF(F_a + F_b, X, G, E) :- grenzStammF(F_a, X, G, E_a), grenzStammF(F_b, X, G, E_b), E is (E_a + E_b).
grenzStammF(F_a - F_b, X, G, E) :- grenzStammF(F_a, X, G, E_a), grenzStammF(F_b, X, G, E_b), E is (E_a - E_b).
grenzStammF(F_a * F_b, X, G, E) :- grenzStammF(F_a, X, G, E_a), grenzStammF(F_b, X, G, E_b), E is (E_a * E_b).
% Berechne Einzelteile
% c
grenzStammF(C, _, _, C) :- number(C).
% x
grenzStammF(X, X, G, G).
% x^n
grenzStammF(X^N, X, G, E) :- number(N), E is (G^N).
% --------------------
% Berechne bestimmtes Integral bestInt(Funktion, Variable, (untere) Grenze 1, (obere) Grenze 2, Ergebnis)
% --------------------
bestInt(F, X, G1, G2, E) :- number(G1), number(G2), atomic(X), stammF(F, X, StammF), grenzStammF(StammF, X, G1, E1), grenzStammF(StammF, X, G2, E2), E is (E2 - E1).