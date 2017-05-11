command(Command, PositionsBefore, PositionsAfter) :- 
moveCommand(Command, Color, To), 
position(PositionsBefore, ColorAb, PositionAb, ColorBb, PositionBb), 
position(PositionsAfter, ColorAa, PositionAa, ColorBa, PositionBa).

position(PositionsString, ColorA, PositionA, ColorB, PositionB) :- 
color(PositionsString, Rest1, ColorA) , % Farbe 1
stuff(Rest1, Rest2),
%(match(Rest1, rook, Rest1) ; match(Rest1, is, Rest1)),	% eleminiere rook
%(match(Rest1, is, Rest2), match (Rest2, at, Rest3)),	% eliminiere is und/oder at
(match(Rest3)).
 
% finde Farbe:
color(Elemente, Rest, Color) :- match(black, Elemente, Rest, Color) ; match(white, Elemente, Rest, Color).

% Eliminiere unwichtiges:
stuff(Elemente, Rest) :- match(black, Elemente, Rest, % Abbruchkriterium
stuff(Elemente, Rest) :- (), 

match(X, [X|Rest], Rest, X).