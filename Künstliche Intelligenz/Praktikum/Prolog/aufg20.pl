% Bonus: Schritte Zeilenweise ausgeben:
printP(P) :- maplist(writeln, P), nl.

% Bonus: Suchfunktion mit formatierter Ausgabe und Infos zur benötigten Zeit:
findPath(M, S, H, R) :- 
  get_time(T1),
  START = [M, [S, H], R], goal(GOAL), idDfs(START, GOAL, P), printP(P),
  get_time(T2),
  DeltaT is round((T2- T1)*1000)/1000,
  write('Weg in '), write(DeltaT), write(' s gefunden.\n'), nl, !.
  
% --------------------------------------------------------------------------------

:- [idDfs].

% Suchfunktion mit unformatierter Ausgabe:
findPath(M, S, H, R, P) :- START = [M, [S, H], R], goal(GOAL), idDfs(START, GOAL, P).

% Liste aller Wege (Wegraster: (0,0) ist oben links und (7,5) ist unten rechts):
weg0(P1, P2) :- member((P1, P2), [
	% Horizontale Wege (Zeilenweise):
	((0,0), (1,0)),
	((1,0), (2,0)),
	((3,0), (4,0)),
	((1,1), (2,1)),
	((2,1), (3,1)),
	((4,1), (5,1)),
	((5,1), (6,1)),
	((6,1), (7,1)),
	((2,2), (3,2)),
	((3,2), (4,2)),
	((6,2), (7,2)),
	((3,3), (4,3)),
	((5,3), (6,3)),
	((6,3), (7,3)),
	((0,4), (1,4)),
	((1,4), (2,4)),
	((2,4), (3,4)), 
	((5,4), (6,4)),
	((3,5), (4,5)),
	((4,5), (5,5)),
	((5,5), (6,5)),
	% Vertikale Wege (Zeilenweise):
	((0,0), (0,1)),
	((1,0), (1,1)),
	((4,0), (4,1)),
	((5,0), (5,1)),
	((6,0), (6,1)),
	((7,0), (7,1)),
	((1,1), (1,2)),
	((2,1), (2,2)),
	((6,1), (6,2)),
	((0,2), (0,3)),
	((2,2), (2,3)),
	((3,2), (3,3)),
	((5,2), (5,3)),
	((6,2), (6,3)),
	((0,3), (0,4)),
	((1,3), (1,4)),
	((3,3), (3,4)),
	((5,3), (5,4)),
	((7,3), (7,4)),
	((0,4), (0,5)),
	((1,4), (1,5)),
	((2,4), (2,5)),
	((3,4), (3,5)),
	((5,4), (5,5)),
	((7,4), (7,5))
]).

% Überprüfe, ob ein Weg zwischen benachbarten Punkten 1 und 2 existiert:
weg(P1, P2) :- weg0(P1, P2); weg0(P2, P1).

% Gültige Übergänge:
adj([M1, [], R1], [M1, [], R2]) :- member(M1,R1), delete(R1,M1,R2).	% Rose schneiden
adj([M1, [],  R], [M2, [],  R]) :- weg(M1, M2).						% Mit Werkzeug bewegen
adj([M1, W1,  R], [M1, W2,  R]) :- member(M1,W1), delete(W1,M1,W2).	% Werkzeug aufheben
adj([M1,  W,  R], [M2,  W,  R]) :- W \== [], weg(M1, M2).			% Ohne alle Werkzeuge bewegen

% Das Ziel: keine Rosen mehr zu schneiden!
goal([_,  _, []]).

% Zum Testen der Funktion:
% Einfach: findPath((0,0), (0,1), (1,0), [(1,1), (3,1)]).
% Mittel: findPath((0,0), (0,1), (1,0), [(7,5)]).
% Schwer: findPath((0,0), (7,5), (0,5), [(7,0), (0,0)]).
% Schwerer: findPath((0,0), (7,5), (0,5), [(7,0), (0,0), (3,5), (7,3), (2,0), (1,1)]).