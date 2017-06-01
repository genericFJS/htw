% Heuristische Bewertungsfunktion
% [H|T]: Pfad zum aktuellen Knoten H
f([H|T],Y) :- g([H|T],Y1), h(H,Y2), Y is Y1+Y2.
g(L,Y) :- length(L,Y1), Y is Y1-1.
h(X,Y) :- Y is 0. % Ändern! Hier muß eine Kostenschätzfunktion angegeben werden.

% A*-Suche
% [H|T]: Sortierte Liste der noch zu untersuchenden Knoten
% Closed: Liste der Knoten, die bereits untersucht wurden
% Die Knoten müssen hier Pfade zum aktuellen, eigentlichen Knoten sein, damit f dessen Bewertung berechnen kann.
hs([H|T], Closed) :-
	goal(H);
	Cl = [H|Closed],
	findall(Node, (adj(H, Node), not(member(Node, Cl))), NewNeighbors),
	append(T, NewNeighbors, Queue),
	fsort(Queue, SortedQ),
	hs(SortedQ, Cl).
	
% Sortieren der Liste gemäß der Werte von f
fsort(List, Sorted) :- 
        map_list_to_pairs(f, List, Pairs), 
        keysort(Pairs, SortedPairs), 
        pairs_values(SortedPairs, Sorted). 