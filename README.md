# Informatik Bachelor HTW Dresden

Hier sind einige Unterlagen (Skripte, Übungen, Praktika) vom Studiengang Bachelor Informatik der HTW Dresden zu finden. Zusammengestellt von Jonatan Strube.
Alle Dateien sind (solange nicht anders besprochen) aussschließlich für den privaten Gebrauch zugelassen.

## Repository

Da in diesem Repo einige Binärdateien (pdfs usw.) liegen, wird git lfs (https://git-lfs.github.com/) verwendet. Zum Klonen muss daher ggf. folgendes befolgt werden (Quelle: https://github.com/github/git-lfs/issues/911#issuecomment-169998792):

// Skip smudge - We'll download binary files later in a faster batch

git lfs install --skip-smudge

// Do git clone here

git clone ...

// Fetch all the binary files in the new clone

git lfs pull

// Reinstate smudge

git lfs install --force

## LaTeX

Zum kompilieren der *.tex*-Dateien innerhalb der */Modulname*-Ordner ist in (fast) jedem Fall der */LaTeX_master*-Ordner notwendig. Die Ordnerstruktur muss auch beibehalten werden. Ansonsten müssten die jeweiligen *\include{}*-Einträge angepasst werden.

## Copyright

### Dateien von mir

In der Regel sind im Ordner */Modulname* erst die *.tex*- und dazugehörigen *.pdf*-Dateien zu finden. Diese sind von mir erstellt. Der Inhalt ist auf die im Dokument verwiesenen Professoren zurückzuführen. Die Zusammenstellung, gestalterische Umsetzung, Kommentare usw. sind von mir.

Des weiteren sind im Ordner */Modulname/Praktikum/prak##* Umsetzungen von Praktika zu finden, die von mir erarbeitet sind.

Der Ordner */LaTeX_master* enthält das TeX-Headerfile, das Grundlage für (fast) alle anderen *.tex*-Dateien ist. Dies ist komplett, inklusive package-Auswahl und Macros, von mir zusammengestellt. 


Diese von mir erstellten Dateien dürfen beliebig für den privaten Gebrauch weiter verwendet werden. Beim Übernehmen von größeren Text- bzw. Code-Passagen wäre es höflich mich als Quelle zu erwähnen.

Ohne meine explizite Zustimmung ist es nicht erlaubt die von mir erstellten Dateien:
- Über den privaten Gebrauch hinaus gehend zu verwenden. 
- Außerhalb dieses Repos hochzuladen und anzubieten.

### Dateien von dritten

Bei den Dokumenten (oder Abschnitten innerhalb von Dokumenten), die nicht von mir sind, ist dieses in der Regel ersichtlich. So beispielsweise die Dokumente mit Übungs- und Praktikumsaufgaben.

In der Regel wurden diese Dokumente von der öffentlich zugänglichen Seite des jeweiligen Lehrstuhls runter geladen.

Rechte zur Nutzung und Weiterverteilung müssen dort entsprechend erfragt werden.

## Kennzeichnung der Commits

### Semesterbetrieb
Commit | Emoji
----------  | -------------
Mitschrift (Aktualisierung) | :pencil: `:pencil:`
Übung/Praktikum | :ledger: `:ledger:`

### Projektentwicklung (Belege usw.)

Commit | Emoji
----------  | -------------
Initial Commit | :tada: `:tada:`
Version Tag | :bookmark: `:bookmark:`
Neues Feature | :sparkles: `:sparkles:`
Bugfix | :bug: `:bug:`
Documentation | :books: `:books:`
Refactoring | :package: `:package:`
Performance | :bicyclist: `:bicyclist:`
Kosmetisches | :art: `:art:`
Tests | :clipboard: `:clipboard:`
Deprecation | :poop: `:poop:`
Work In Progress (WIP) | :construction: `:construction:`
Other | [Link](http://www.emoji-cheat-sheet.com/)
