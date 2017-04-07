terrorv(Y) :- anf(X,Y), terror(X).
terror(X) :- mitgl(X,Y) , terrorv(Y).
terror("Terrorist").
org("ADAC").
mitgl("August Meier", "ADAC").
mitgl("Abul-Hasan Al Muhajir", "IS").
anf("Terrorist","IS").
strafbar(X) :- verkauf(X,Y,Z), waffe(Y), terror(Z).
verkauf("Omar Abdul Al-Hassan", "M16", "Abul-Hasan Al Muhajir").
verkauf("Bernd Müller", "Auto", "August Meier").
waffe("M16").