%		f z k w
sicher([F,F,_,_]).
sicher([_,Z,K,W]) :- Z \== K, Z \== W.

%     f z k w
adj0([0,0,K,W], [1,1,K,W]).	% Ziege übersetzen
adj0([0,Z,0,W], [1,Z,1,W]).	% Kohl übersetzen
adj0([0,Z,K,0], [1,Z,K,1]).	% Wolf übersetzen
adj0([0,Z,K,W], [1,Z,K,W]).	% Leerfahrt

adj(X,Y) :- (adj0(X,Y); adj0(Y,X)), sicher(X), sicher(Y).

solution(P) :- X = [0,0,0,0], Y = [1,1,1,1], idDfs(X,Y,P).
:- [idDfs].