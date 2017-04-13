%kind(name, geschlecht, mutter, vater).
kind(robert, mann, wilhelm, frieda).
kind(sandra, frau, kurt, lisa).
kind(thomas, mann, winfried, elke).
kind(christine, frau, hans, paula).
kind(eva, frau, thomas, christine).
kind(jan, mann, robert, sandra).
kind(jens, mann, robert, sandra).
kind(julia, frau, robert, sandra).
kind(jutta, frau, robert, sandra).
kind(anne, frau, jan, eva).
kind(anke, frau, jan, eva).
kind(tim, mann, jens, heike).

% X bruder von Y:
bruder(X,Y):- kind(X,mann,V,M) , kind(Y,_,V,M), not(X=Y). 
% X schwester von Y:
schwester(X,Y):- kind(X,frau,V,M) , kind(Y,_,V,M), not(X=Y). 
% X ist vorfahr von Y:
direkterVorfahr(X,Y):- kind(Y,_,X,_); kind(Y,_,_,X).	
% X enkel von Y:
% eigene Lösung ohne direkterVorfahr: enkel(X,Y):- kind(X,_,V,M), (kind(V,_,Y,_) ; kind(M,_,Y,_) ; kind(V,_,_,Y) ; kind(M,_,_,Y)).
enkel(X,Y):- direkterVorfahr(Z, X), direkterVorfahr(Y, Z). 
% X ist onkel von Y:
% eigene Lösung ohne direkterVorfahr: onkel(X,Y):- kind(Y,_,V,M) , (bruder(X,V) ; bruder(X,M)) .	
onkel(X,Y):- direkterVorfahr(Z,Y), bruder(X,Z).
% X ist onkel von Y:
% eigene Lösung ohne direkterVorfahr: tante(X,Y):- kind(Y,_,V,M) , (schwester(X,V) ; schwester(X,M)) .	
tante(X,Y):- direkterVorfahr(Z,Y), schwester(X,Z). 