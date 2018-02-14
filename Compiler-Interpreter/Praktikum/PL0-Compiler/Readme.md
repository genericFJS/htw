# PL0-Compiler von Falk-Jonatan Strube #

Dieser Compiler kompiliert pl0-Dateien in ein cl0-Byteformat, das von einer entsprechenden virtuellen Maschine interpretiert werden kann.

## Kompilieren ##

Das Projekt ist in C# geschrieben. Mit der entsprechenden Visual Studio Projektdatei lässt sich der Quelltext sehr einfach ansehen und kompilieren.

Mit Mono kann es beispielsweise auch auf Linux kompiliert werden. Am einfachsten geht das auch mit dem Visual Studio Projekt: `xbuild /p:Configuration=Release /p:TargetFrameworkVersion=v4.5 /p:TargetFrameworkProfile="" PL0-Compiler.csproj`

## Ausführen ##

Der Compiler kann wie oben beschrieben selbst kompiliert werden. Alternativ stehen im Ordner `bin` für Linux und Windows fertig kompilierte Compiler bereit. Dort zu finden sind auch einige virtuelle Maschinen zur Bytecodeanalyse (`outCl0`) und zum Ausführen des Bytecodes (`runCl0`).

Die zu kompilierende Datei kann dem Compiler entweder beim Aufruf als Parameter übergeben oder nach dem Aufruf in die Kommandozeile eingegeben werden. Genau so verhält es sich mit den virtuellen Maschinen und dem Bytecode.

Zu beachten ist, dass die zu kompilierende Datei, wenn sie nicht in den `bin`-Ordner verschoben wird, mit einem relativen Pfad angegeben werden muss. Für die Datei `test.cl0` im Ordner `tests` muss also `tests/test` oder `tests/test.cl0` eingegeben werden.

### Windows ###

Zum kompilieren die Datei muss die Datei `compile.exe` ausgeführt werden. Um das Ergebnis anzusehen wird empfohlen dies über die Kommandozeile zu tun. Die dafür bereitgestellte `OpenCommandPromptHere.bat` öffnet in dem `bin`-Ordner eine solche. 

### Linux ###

Um den Compiler auf Linux auszuführen, wird Mono benötigt. Ist Mono installiert, so kann das bereitgestellte Shellskript `compile.sh` (mit optionalem Parameter) aufgerufen werden (Ausführrechte müssen natürlich gesetzt sein).

## Besonderheiten ##

Bei der Stringausgabe werden `\n` und `\t` in die entsprechenden ASCII-Codes umgewandelt. Um dies sinnvoll zu nutzen, wurde eine virtuelle Maschine angepasst, damit sie nicht nach jedem Output eine neue Zeile generiert. Diese ist, wie die anderen auch, in `bin` unter dem Dateinamen `runCl0_nl` zu finden. Ein sinnvolles Beispiel findet sich unter `tests/test-beck_nl` - führt man die kompilierte Datei mit der entsprechenden virtuellen Maschine aus, erhält man eine sehr viel übersichtlichere Ausgabe.