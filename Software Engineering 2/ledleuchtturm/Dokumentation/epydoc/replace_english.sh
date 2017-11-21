sed -i -- 's/{Package /{Paket /g' *.tex
sed -i -- 's/{Module /{Modul /g' *.tex
sed -i -- 's/{Modules}/{Module}/g' *.tex
sed -i -- 's/{Functions}/{Funktionen}/g' *.tex
sed -i -- 's/{Variables}/{Variablen}/g' *.tex
sed -i -- 's/(Section /(Unterabschnitt /g' *.tex
sed -i -- 's/, p.~/, S.~/g' *.tex
sed -i -- 's/textbf{Description}/textbf{Beschreibung}/g' *.tex
sed -i -- 's/textbf{Value:/textbf{Wert:/g' *.tex
sed -i -- 's/textbf{Author:}/textbf{Autor:}/g' *.tex
sed -i -- 's/textbf{Parameters}/textbf{Parameter}/g' *.tex
sed -i -- 's/textbf{Return Value}/textbf{R"uckgabewert}/g' *.tex
sed -i -- 's/textit{continued on next page}/ldots/g' *.tex