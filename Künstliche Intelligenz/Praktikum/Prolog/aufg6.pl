ort(dresden).	% nicht nötig
strasse(hochschulstrasse).	% nicht nötig
strasseInOrt(hochschulstrasse,dresden).
regnet(dresden).

nass(Y) :- regnet(X), strasseInOrt(Y,X).