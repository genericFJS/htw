:- [idDfs].

ort(X) :- member(X, [a, b]).
% Bedeutung der Listen: [Ziege, Kohlkopf, Wolf, Fährmann]
adj0([Z1,K,W,F1], [Z2,K,W,F2]) :- 
	ort(Z1), ort(Z2), ort(F1), ort(F2), 
	Z1 == F1, Z2 == F2, 
	ok(Z1, K, W, F1), ok(Z2, K, W, F2).	% Ziege rüber fahren
adj0([Z,K1,W,F1], [Z,K2,W,F2]) :- 
	ort(K1), ort(K2), ort(F1), ort(F2), 
	K1 == F1, K2 == F2, 
	ok(Z, K1, W, F1), ok(Z, K2, W, F2).	% Kohl rüber fahren
adj0([Z,K,W1,F1], [Z,K,W2,F2]) :- 
	ort(W1), ort(W2), ort(F1), ort(F2), 
	W1 == F1, W2 == F2, 
	ok(Z, K, W1, F1), ok(Z, K, W2, F2).	% Wolf rüber fahren
adj0([Z,K,W,F1], [Z,K,W,F2]) :- 
	ort(F1), ort(F2), 
	ok(Z, K, W, F1), ok(Z, K, W, F2).	% Fährmann alleine rüber fahren

ok(Z,K,W,F) :- Z == K, Z == F; Z == W, Z == F; Z \== K , Z \== W.	% Ziege nur in Beisein vom Fährmann zusammen mit Kohlkopf und Wolf

goal([b,b,b,b]).	% alle in Pillnitz und sicher

adj(X,Y) :- adj0(X,Y); adj0(Y,X).

solution(Path) :- Start = [a, a, a, a], goal(Goal), idDfs(Start,Goal,Path).

% solution(X), write(X).