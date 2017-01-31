:- ['8puzzle-adj'].
:- [idas].
:- [idDfs].

% Heuristik Hamming-Distanz
h0(9,_,0). % Leerstelle zählt nicht
h0(_,9,0).
h0(A,A,0).
h0(_,_,1).

h(Board, HD) :-
	flatten(Board, B),
	goal(GoalB), flatten(GoalB,G),
	maplist(h0, B, G, Diffs),
	sumlist(Diffs, HD), !.
	
solution(Board, Sol) :- goal(G), idas(Board, G, Sol).

%solution([[9,1,2], [4,6,3], [7,5,8]], Sol), print(Sol).