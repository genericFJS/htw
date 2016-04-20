#Newton Verfahren

# Funktion zum Durchfuerhen eines Interations-Schritts
tang<-function(xn){
  abline(f(xn)-f1(xn)*xn,f1(xn),col="blue")             # zeichnet Tangente; abline(a,b) zeichnet gerade mit Achsenabschnitt a und Anstieg b
  points(xn,f(xn),col="red",pch=19)                     # Aktuellen Punkt fuer Tangente Rot markieren
  lines(c(xn,xn),c(f(xn),-100000),lty=2,col="red" )     # Rote senkrechte gestrichelte Linie
  xn<-xn-f(xn)/f1(xn)                                   # xn aktualisieren
}

# Bsp 1
xmin<- -1; xmax<-3; x0<-3
f<-function(x){x^2 }    # Funktion
f1<-function(x){2*x}     # erste Ableitung

# Bsp 2
xmin<- -1; xmax<-3; x0<- 0.8
f<-function(x){x-cos(x) }    # Funktion
f1<-function(x){1+sin(x)}     # erste Ableitung

# Bsp 3
xmin<- -1; xmax<-6.1; x0<- 3
f<-function(x){0.2*x^4   - 3*x^2 }    # Funktion
f1<-function(x){0.8*x^3 -  6*x}     # erste Ableitung


# Plot der Funktion und der x-Achse
x<-seq(xmin,xmax,length.out = 200)
plot(x,f(x),type="l",lwd=3,xaxs="i",yaxs="i")
abline(0,0)

# initialisieren
xn<-x0

# Newton starten
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
xn<-tang(xn)
# noch 100 mal interieren
for(i in 1:100){
  xn<-tang(xn)
}
# xn ausgeben (unsere approximative Nullstelle)
xn
# Test ob Funktionswert wirklich (fast) 0 ist
f(xn)
