d(X,X,1).
d(C,X,0) :- atomic(C), C \== X.
d(-F,X,-DF) :- d(F,X,DF).
d(C*F,X,C*DF) :- d(C,X,0), d(F,X,DF).
d(F+G,X,DF+DG) :- d(F,X,DF), d(G,X,DG).
d(F-G,X,DF-DG) :- d(F,X,DF), d(G,X,DG).
d(F^N,X,N*F^M*DF) :- number(N), M is N-1, d(F,X,DF).

s0(0+A,A).
s0(A+0,A).
s0(1*A,A).
s0(A*1,A).
s0(A,A).