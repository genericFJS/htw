:- [idDfs].

ort(X) :- member(X, [tuer, mitte, fenster]).
% Bedeutung der Listen: [Affe, Banane, Stuhl, Affe auf Stuhl]
adj0([A1,B,S,f], [A2,B,S,f]) :- ort(A1), ort(A2).   % laufen
adj0([A1,B,A1,f], [A2,B,A2,f]) :- ort(A1), ort(A2). % Stuhl schieben
adj0([A,B,A,f], [A,B,A,t]).                         % auf Stuhl steigen
goal([A,A,_,t]).                                    % Banane greifen

adj(X,Y) :- adj0(X,Y); adj0(Y,X).

solution(Path) :- Start = [tuer, mitte, fenster, f], goal(Goal), idDfs(Start,Goal,Path).
