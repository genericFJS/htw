## Einfaches AND/XOR-Netzwerk erstellen ##

- Eingabeneuronen Funktionen:
	- act_identity
	- out-identity
- Sonstige Neuronen Funktionen:
	- act_logistic
	- out_identity
- Neuronen über "Layer" hinzufügen (Tools-Create):
	- Height gibt die Anzahl der Neuronen an.
- Connections:
	- immer Feed-Forward
- Datensatz:
	- and_train.pat
	- über File-Open öffnen
- Anzeigen:
	- Fehler anzeigen (View-Error Graph)
	- Control Panel (Tools-Control Panel)
	- Projektion (alle Neuronen markieren, dann View-Projection)
- Neuronen:
	- AND: 2 Eingang, 1 Ausgang
	- XOR: 2 Eingang, 2 Hidden, 1 Ausgang

## 4-Klassen-Abbildung ##
Daten liegen in 4 Klassen verteilt (Abbildung 13/14)
- 2 Eingabeneuronen (Koordinaten)
- 2 Hiddenschichten (2 Geraden trennen 4 Klassen). Bei späteren Beispielen sind die Punkte sehr "unschön" verteilt, da lohnen sich auch mehr Hiddenschichten
- Für jede Klasse ein Ausgabeneuron

Hinweis bei Binärkodierung: Kodierung ist zusätzlich zur Zuordnung -> dauert deshalb länger. Durch Kodierung werden die Kategorien entfremdet, was nachteilig ist, da wir nach Gemeinsamkeiten suchen.

## Doppelspirale ##
- 2 Eingänge
- 2 Hidden-Layer (weil konvex und konkav):
	- 1.: 25 Neuronen
	- 2.: 10 Neuronen
	- (Anzahl der Neuronen ist Erfahrungswert)
- 1 Ausgang (0/1 für Klasse)