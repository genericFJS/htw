satz(In, Rest, S, O, V) :- nominal_phrase(In, R, S), verbal_phrase(R, Rest, O, V).
nominal_phrase(In, Rest, E) :- artikel(In, R), nomen(R, Rest, E).
verbal_phrase(In, Rest, O, V) :- verb(In, R, V), nominal_phrase(R, Rest, O).
artikel(In, Rest) :- match(eine, In, Rest, _); match(die, In, Rest, _).
verb(In, Rest, V) :- match(jagt, In, Rest, V); match(sieht, In, Rest, V).
nomen(In, Rest, E) :- match(katze, In, Rest, E); match(kater, In, Rest, E); match(maus, In, Rest, E).

match(X, [X|Rest], Rest, X).	% match erweitern, dass es das gemachte zurück gibt!