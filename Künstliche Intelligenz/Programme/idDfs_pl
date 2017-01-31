% Iterative Tiefensuche (Iterative deepening depth-first search)

% Node: aktueller Knoten
% Goal: Zielknoten
% Path: Liste der Knoten auf dem Pfad bis Node
% ReturnPath: Rückgabe, wenn ein Pfad zum Ziel gefunden wurde
dlDfs(Node, Goal, Path, DepthLimit, ReturnPath) :-
	Node = Goal, reverse(Path, ReturnPath);
	DepthLimit > 0,
	adj(Node,NewNeighbor), not(member(NewNeighbor,Path)),
	dlDfs(NewNeighbor, Goal, [NewNeighbor|Path], DepthLimit-1, ReturnPath).

idDfsLoop(Start, Goal, D, ReturnPath) :-
	dlDfs(Start, Goal, [Start], D, ReturnPath);
	% Wenn die Tiefensuche mit Schranke D nicht erfolgreich war, wird mit Schranke D+1 weitergesucht.
	idDfsLoop(Start, Goal, D+1, ReturnPath).

idDfs(Start, Goal, ReturnPath) :- idDfsLoop(Start, Goal, 1, ReturnPath).
