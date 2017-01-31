satz(In, Rest) :- nominal_phrase(In, R), verbal_phrase(R, Rest).
nominal_phrase(In, Rest) :- artikel(In, R), nomen(R, Rest).
verbal_phrase(In, Rest) :- verb(In, R), nominal_phrase(R, Rest).
artikel(In, Rest) :- match(eine, In, Rest); match(die, In, Rest).
verb(In, Rest) :- match(jagt, In, Rest); match(sieht, In, Rest).
nomen(In, Rest) :- match(katze, In, Rest); match(kater, In, Rest); match(maus, In, Rest).

match(X, [X|Rest], Rest).