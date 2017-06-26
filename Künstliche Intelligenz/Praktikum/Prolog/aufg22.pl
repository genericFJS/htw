% 8-puzzle_adj

% Leerstelle in Zeile verschieben
sr( [9,A,B], [A,9,B]).
sr( [A,9,B], [A,B,9]).
shiftr(X,Y) :- sr(X,Y); sr(Y,X). 
 
adjr( [X,  R2, R3], [Y,  R2, R3]) :- shiftr(X, Y).
adjr( [R1, X,  R3], [R1, Y,  R3]) :- shiftr(X, Y).
adjr( [R1, R2,  X], [R1, R2,  Y]) :- shiftr(X, Y).

% Leerstelle in Spalte verschieben
adjc( [[A1,B1,C1], [D1,E1,F1], [G1,H1,I1]], 
      [[A2,B2,C2], [D2,E2,F2], [G2,H2,I2]] ) :- 
	adjr( [[A1,D1,G1], [B1,E1,H1], [C1,F1,I1]],
	      [[A2,D2,G2], [B2,E2,H2], [C2,F2,I2]] ).  
 
% Leerstelle in Zeile oder Spalte verschieben
adj(Board1, Board2) :-
	adjr(Board1, Board2);
	adjc(Board1, Board2).
	
% Zielstellung
goal( [[1,2,3],
       [4,5,6],
       [7,8,9]] ).

% Pretty-Printer
printB(Board) :- maplist(writeln, Board), write('\n').
print(Boards) :- maplist(printB, Boards).

% 8-puzzle
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