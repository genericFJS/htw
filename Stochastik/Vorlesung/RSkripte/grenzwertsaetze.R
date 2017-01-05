# Grenzwertsaetze

# 1. Gesetz der grossen Zahlen

# 1a Bernoulli ZV (Muenze)
n<-5000
plot(c(-300,100000),c(0.5,0.5),pch=19,cex=0.1,ylim=c(0.35,0.65),xlim=c(0,n),type="l",col="yellow",lwd=39,xaxs="i",xlab="n",ylab="relative Anzahl Kopf bei n Würfen")
lines(c(-300,100000),c(0.5,0.5))
for (j in 1:6){
  x<-rbinom(n,1,0.5)
  a<-c()
  for (i in 1:length(x)){
    a[i]<-sum(x[1:i])/i
  }
  lines(a,pch=19,cex=0.1,type="l",col=j)
}

# 1b Poisson ZV
n<-5000
plot(c(-300,100000),c(3,3),pch=19,cex=0.1,ylim=c(2,4),xlim=c(0,n),type="l",col="yellow",lwd=29,xaxs="i",xlab="n",ylab="relative Anzahl Kopf bei n Würfen")
lines(c(-300,100000),c(3,3))
for (j in 1:6){
  x<-rpois(5000,3)
  a<-c()
  for (i in 1:length(x)){
    a[i]<-sum(x[1:i])/i
  }
  lines(a,pch=19,cex=0.1,type="l",col=j)
}

# 1c irgendeine diskret ZV
w<-c(1,4,9)   # werte
p<-c(0.2,0.3,0.5) # wk
ew<-sum(w*p) # Erwartungswert berechnen

n<-5000
plot(c(-300,100000),c(ew,ew),pch=19,cex=0.1,ylim=c(5.5,6.5),xlim=c(0,n),type="l",col="yellow",lwd=29,xaxs="i",xlab="n",ylab="relative Anzahl Kopf bei n Würfen")
lines(c(-300,100000),c(ew,ew))
for (j in 1:6){
  x0<-runif(n)
  x<-rep(w[3],n)
  x[x0<=(p[1]+p[2])] <- w[2]
  x[x0<=p[1]] <- w[1]
  a<-c()
  for (i in 1:length(x)){
    a[i]<-sum(x[1:i])/i
  }
  lines(a,pch=19,cex=0.1,type="l",col=j)
}


# 2. Zentraler Grenzwertsatz am Wuerfel

##### Wuerfel-Summe
par(xpd=F)
rec.fct<-function(x){
  c(x+1,x+2,x+3,x+4,x+5,x+6)
}

wfl.sum<-function(n){
  x<-1:6
  if (n>1){
    for(i in 1:(n-1)){
      x<-rec.fct(x)
    }
  }
  return(table(x)/sum(table(x)))
}
s2<-sum((1:6)^2)/6- (sum(1:6)/6)^2

plt.fct<-function(n){
  w=wfl.sum(n)
  x<-seq(from = min(as.numeric(names(w))),to = max(as.numeric(names(w))), length.out = 100)
  #x<-seq(from = 0,to = 50, length.out = 100)
  plot(x,dnorm(x,mean = 3.5*(n),sd =sqrt(s2*(n))),type="l",xlab = "x_i",ylab= "p_i",cex.axis=2,lwd=3.5)
  #plot(x,dnorm(x,mean = 3.5*(n),sd =sqrt(s2*(n))),type="l",xlab = "x_i",ylab= "p_i",cex.axis=2,lwd=3.5,xlim=c(1,50),ylim=c(0,0.25))
  lines(w,type = "p",col="red",pch=19,cex=2)
}

plt.fct(1)
plt.fct(2)
plt.fct(3)
plt.fct(4)
plt.fct(5)
plt.fct(6)
plt.fct(9)

# Glivenko-Cantelli (einzelne Bilder, immer neue Realsierungen)
gc.fun<-function(n){
  x2<-rexp(n)
  x<-seq(from = 0,to = 10,length.out = 100)
  plot(x,pexp(x),type="l", col="red", lwd=5)
  
  x<-sort(x2[1:n])
  y<-0:length(x)/length(x)
  plot(stepfun(x,y),add=TRUE, col="blue", lwd=4)
  lines(c(x[length(x)],1000),c(1,1), col="blue", lwd=4)
}

gc.fun(4)
gc.fun(10)
gc.fun(23)
gc.fun(50)
gc.fun(100)
gc.fun(400)

# GC (Verfeinerung, Auswahl aus einer Realisierung)
vec<-c(3,5,10,15,50,100)
x2<-rexp(max(vec))
for (i in 1:6){
  pdf(file=paste("gliv_cant_",i,".pdf",sep=""))
  x<-seq(from = 0,to = 10,length.out = 100)
  plot(x,pexp(x),type="l", col="red", lwd=5)
  
  x<-sort(x2[1:vec[i]])
  y<-0:length(x)/length(x)
  plot(stepfun(x,y),add=TRUE, col="blue", lwd=4)
  lines(c(x[length(x)],1000),c(1,1), col="blue", lwd=4)
  dev.off()
}


