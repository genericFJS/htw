satz(In, Rest) :- 
	nominal_phrase(_, nom, In, R), % Subjekt (Nominativ, wer oder was?) 
	verbal_phrase(R, Rest).

nominal_phrase(Genus, Kasus, In, Rest) :- 
	artikel(Genus, Kasus, In, R), nomen(Genus, R, Rest).

verbal_phrase(In, Rest) :- 
	verb_intransitiv(In, Rest);
	verb_transitiv(In, R), nominal_phrase(_, akk, R, Rest). % Objekt (Akkusativ, wen oder was?)

artikel(m, nom, In, Rest) :- match(A, In, Rest), member(A, [ein, der]).
artikel(f, nom, In, Rest) :- match(A, In, Rest), member(A, [eine, die]).
artikel(m, akk, In, Rest) :- match(A, In, Rest), member(A, [einen, den]).
artikel(f, akk, In, Rest) :- match(A, In, Rest), member(A, [eine, die]).

verb_intransitiv(In, Rest) :- match(V, In, Rest), member(V, [jagt, schläft, rennt]).
verb_transitiv(In, Rest) :- match(V, In, Rest), member(V, [jagt, sieht]).

nomen(m, In, Rest) :- match(kater, In, Rest).
nomen(f, In, Rest) :- match(V, In, Rest), member(V, [katze, maus]).

match(X, [X|Rest], Rest).