% IDA*-Suche

% f: Heuristische Bewertungsfunktion
% h: Heuristische Kostenschätzfunktion
% [Head|Tail]: Aktueller Pfad, Head: aktueller Knoten 
f([Head|Tail], F) :- 
	length(Tail, G),
	h(Head, H),
	F is G+H. 

% Node: aktueller Knoten
% Goal: Zielknoten
% Path: Liste der Knoten auf dem Pfad bis Node
% ReturnPath: Rückgabe, wenn ein Pfad zum Ziel gefunden wurde
% adj: Adjazenz eines Knotens
flDfs(Node, Goal, Path, FLimit, ReturnPath) :-
	Node == Goal, reverse(Path, ReturnPath);
	adj(Node,NewNeighbor), not(member(NewNeighbor,Path)),
	f([NewNeighbor|Path], F), F =< FLimit,
	flDfs(NewNeighbor, Goal, [NewNeighbor|Path], FLimit, ReturnPath).

idasLoop(Start, Goal, FLimit, ReturnPath) :-
	flDfs(Start, Goal, [Start], FLimit, ReturnPath);
	% Schranke für f wird um kleinstmögliche Schrittweite erhöht (einfach zu programmieren)
	idasLoop(Start, Goal, FLimit+1, ReturnPath).

idas(Start, Goal, ReturnPath) :-
	% Da f zulässig ist, sind die Kosten bis zum Ziel mindestens FL
	f([Start], FLimit),
	idasLoop(Start, Goal, FLimit, ReturnPath).
	 
	 
