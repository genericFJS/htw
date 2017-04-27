d(X,X,1).
d(C,X,0) :- atomic(C), C \== X.
d(-F,X,-DF) :- d(F,X,DF).
d(C*F,X,C*DF) :- d(C,X,0), d(F,X,DF).
d(F+G,X,DF+DG) :- d(F,X,DF), d(G,X,DG).
d(F-G,X,DF-DG) :- d(F,X,DF), d(G,X,DG).
d(F^N,X,N*F^M*DF) :- number(N), M is N-1, d(F,X,DF).

% s zerlegt die Gleichung rekursiv
s(A+B,C) :- s(A,CA), s(B,CB), s0(CA+CB,C).
s(A*B,C) :- s(A,CA), s(B,CB), s0(CA*CB,C).
s(A,A).
% s0 vereinfacht nicht-rekursiv
s0(A*B,C) :- number(A), number(B), C is A*B.
s0(A+B,C) :- number(A), number(B), C is A+B.
s0(0+A,A).
s0(A+0,A).
s0(1*A,A).
s0(A*1,A).
s0(A,A).
 
% s0(1*x+3*2+0,D).