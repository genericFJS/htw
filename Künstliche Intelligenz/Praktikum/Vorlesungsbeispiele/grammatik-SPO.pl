% Satzbestandteile identifizieren
% Wer jagt wen?
% Wer oder was: Subjekt
% Wen oder was: Akkusativobjekt
satz(In, Rest, Subj, AkkObj, Verb) :- nominal_phrase(In, R, Subj), verbal_phrase(R, Rest, AkkObj, Verb).
nominal_phrase(In, Rest, Was) :- artikel(In, R), nomen(R, Rest, Was).
verbal_phrase(In, Rest, AkkObj, Verb) :- verb(In, R, Verb), nominal_phrase(R, Rest, AkkObj).
artikel(In, Rest) :- match(eine, In, Rest); match(die, In, Rest).
verb(In, Rest, Verb) :- 
	match(jagt, In, Rest), Verb = jagt;
	match(sieht, In, Rest), Verb = sieht.

nomen(In, Rest, Was) :- 
	match(katze, In, Rest), Was = katze;
	match(maus, In, Rest), Was = maus.
match(X, [X|Rest], Rest).
