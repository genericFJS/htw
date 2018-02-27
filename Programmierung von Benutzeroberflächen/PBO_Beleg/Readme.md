# ProcessView #

Diese App stellt eine interaktive Webseite als One-Pager dar. 

Dazu wurde die CSS Bibliothek [Bootstrap 4](https://getbootstrap.com/), das JavaScript-Framework [VUE](https://vuejs.org/) und die selbst gewählte Javascript-Bibliothek zur Visualisierung von Informationen [Highcharts](https://www.highcharts.com/).

Als Ausgangsdaten zur Darstellung wurde ein vorgegebener Datensatz im JSON-Format genutzt. Dazu wurde eigenständig einen Schwerpunkt zur Visualisierung entwickelt und umgesetzt (wie unterhalb beschrieben). 

## Visualisierung ##

- Strukturierter Aufbau der Seite mit Header, Navigation und Footer (mit entsprechenden kontextbezogenem Inhalt)
- Übersicht aller Prozesse, Orte und Stakeholder im Steckbrief/Kartenformat
- Detailansicht vom Nutzer ausgewählten Prozessen/Stakeholder (inklusive damit zusammenhängenden Medien)
- Graphische Statistiken zur Zeitspanne der Teilprozesse und Anzahl der Projekte pro Stakeholder

## Funktionen ##

- Sortierung der Übersichten (bspw. nach ID oder Name)
- Filterung der Übersichten (bspw. nur aktive)
- Auswahl einer Karte zur Detailansicht dieser
- Detailansicht mit expliziten (Name, Beschreibung, …) und impliziten (zugehörige Stakeholder/aktive Prozesse) Informationen und ggf. Medien (Bilder/pdfs)
- Verlinkung zu entsprechend gefilterten Übersichten der zugehörigen Stakeholdern/aktiven Prozessen in der Detailansicht
- Zurück-Button in der Detailansicht
- Übersetzung der englischen JSON-Schlüssel
- Graphische Statistik mit klickbaren Balken zur entsprechender Detailansicht
- und viele mehr

## Bearbeiter ##
- Falk-Jonatan-Strube (s74053)
- Simon Retsch (s74077)