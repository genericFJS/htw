s(A+B,C) :- s(A,SA), s(B,SB), s0(SA+SB,C).
s(A-B,C) :- s(A,SA), s(B,SB), s0(SA-SB,C).
s(A*B,C) :- s(A,SA), s(B,SB), s0(SA*SB,C).
s(A^B,C) :- s(A,SA),s(B,SB),s0(SA^SB,C).
s(A/B,C) :- s(A,SA),s(B,SB),s0(SA/SB,C).
s(sin(A),B) :- s(A,SA),s0(sin(SA),B).
s(log(A),B) :- s(A,SA),s0(log(SA),B).
s(cos(A),B) :- s(A,SA),s0(cos(SA),B).
s(A,A).

s0(A+B,C) :- number(A), number(B), C is A+B.
s0(A-B,C) :- number(A), number(B), C is A-B.
s0(A*B,C) :- number(A), number(B), C is A*B.
s0(0+A,A).
s0(A+0,A).
s0(0-A,-A).
s0(A-0,A).
s0(A-A,0).
s0(1*A,A).
s0(A*1,A).
s0(0*_,0).
s0(_*0,0).
s0(A^1,A).
s0(0/_,0).
s0(1/1,1).
s0(A^1,A).
s0(_^0,1).
s0(0^_,0).
s0(1^_,1).
s0(sin(0),0).
s0(cos(0),1).
s0(log(1),0).
s0(A,A).