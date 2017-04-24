% Recursive Descent Parser für L = {a^n b^n | n >= 0}
% Anfrage: s([a,a,a,b,b,b], []).

s(In, Rest) :-	% S -> aSb 
	match(a, In, R1),
	s(R1, R2),
	match(b, R2, Rest).
s(L, L).	% S -> epsilon

match(X, [X|Rest], Rest).