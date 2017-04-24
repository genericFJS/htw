question(Q, A) :- 
	place-question(Q, Where, What),
	answer(A, Where, What).
 	
% Question analysis
place-question(Q, Where, What) :- 
	(match(in, Q, R1); R1 = Q), 
	(match(what, R1, R2); match(which, R1, R2)),
	place1(R2, R3, Where),
	match2(is, the, R3, R4),
	place2(R4, R5, What),
	(match(on, R5, []); match(in, R5, []); match2(located, in, R5, []); R5 = []).
	
place1(R1, R2, Where) :- 
	match_x(street, R1, R2, Where);
	match_x(town, R1, R2, Where);
	match_x(city, R1, R2, Where).

place2(R1, R2, What) :- 
	match_x(hotel, R1, R2, What);
	match_x(restaurant, R1, R2, What);
	match_x(shop, R1, R2, What).

% Answer construction
answer(A, Where, What) :-
	((place(What, _, Place), (Where = town; Where = city));
	(place(What, Place, _), Where = street)),
	flatten([the, What, is, in, Place], A).

% Word matching
match(X, [X|Rest], Rest).
match2(X1, X2, [X1, X2|Rest], Rest).
match_x(X, [X|Rest], Rest, X). % matched word is 4. parameter 

% Knowledge base
place(hotel, [petersburger, straße], dresden).
place(restaurant, [weiße, gasse], dresden).
place(shop, königstraße, stuttgart).
