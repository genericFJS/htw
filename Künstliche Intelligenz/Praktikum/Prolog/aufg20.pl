:- [idDfs].

findPath(M, S, H, R, P) :- X = [M, S, H, R], goal(Y), idDfs(X, Y, P), printP(P).

% Wegraster: (0,0) ist oben links und (7,5) ist unten rechts
% Horizontale Wege (Zeilenweise):
weg0((0,0), (1,0)).
weg0((1,0), (2,0)).
weg0((3,0), (4,0)).
weg0((1,1), (2,1)).
weg0((2,1), (3,1)).
weg0((4,1), (5,1)).
weg0((5,1), (6,1)).
weg0((6,1), (7,1)).
weg0((2,2), (3,2)).
weg0((3,2), (4,2)).
weg0((6,2), (7,2)).
weg0((3,3), (4,3)).
weg0((5,3), (6,3)).
weg0((6,3), (7,3)).
weg0((0,4), (1,4)).
weg0((1,4), (2,4)).
weg0((2,4), (3,4)).
weg0((5,4), (6,4)).
weg0((3,5), (4,5)).
weg0((4,5), (5,5)).
weg0((5,5), (6,5)).
% Vertikale Wege (Zeilenweise):
weg0((0,0), (0,1)).
weg0((1,0), (1,1)).
weg0((4,0), (4,1)).
weg0((5,0), (5,1)).
weg0((6,0), (6,1)).
weg0((7,0), (7,1)).
weg0((1,1), (1,2)).
weg0((2,1), (2,2)).
weg0((6,1), (6,2)).
weg0((0,2), (0,3)).
weg0((2,2), (2,3)).
weg0((3,2), (3,3)).
weg0((5,2), (5,3)).
weg0((6,2), (6,3)).
weg0((0,3), (0,4)).
weg0((1,3), (1,4)).
weg0((3,3), (3,4)).
weg0((5,3), (5,4)).
weg0((7,3), (7,4)).
weg0((0,4), (0,5)).
weg0((1,4), (1,5)).
weg0((2,4), (2,5)).
weg0((3,4), (3,5)).
weg0((5,4), (5,5)).
weg0((7,4), (7,5)).

weg(P1, P2) :- (weg0(P1, P2); weg0(P2, P1)).

adj0([M1, M1, M1, [M1|R]], [M1, M1, M1, R]).			% Rose schneiden
adj0([M1, M1, M1, R], [M2, M2, M2, R]) :- weg(M1, M2).	% Mit Gartenschere und Gartenhandschuhen bewegen
adj0([M1, M1, H, R], [M2, M2, H, R]) :- weg(M1, M2).	% Mit Gartenschere bewegen (bis Gartenhandschuhe gefunden)
adj0([M1, S, M1, R], [M2, S, M2, R]) :- weg(M1, M2).	% Mit Gartenhandschuhen bewegen (bis Gartenschere gefunden)
adj0([M1, G, H, R], [M2, G, H, R]) :- weg(M1, M2).		% Bewegen, bis ein Werkzeug gefunden.

adj(X,Y) :- (adj0(X,Y); adj0(Y,X)).

goal([M, M, M, []]).
    
printP(P) :- maplist(writeln, P), write('\n').
% findPath((0,0), (7,5), (0,5), [(7,0), (0,0)], P).
% findPath((0,0), (0,1), (1,0), [(1,1), (3,1)], P).