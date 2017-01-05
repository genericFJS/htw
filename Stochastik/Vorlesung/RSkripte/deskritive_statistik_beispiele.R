# Neue Boxplotfunktion (mit Definiton der Quantile wie in der Vorlesung)
boxplot2<-function(x,y=NA,lwd=2,b1=0.3,b2=0.1,xname="x",yname="y",main=""){
  if(is.na(y[1])){
    q<-quantile(x,type = 2)
    plot(c(1-b1,1+b1),c(q[3],q[3]),type = "l",lwd=lwd*3,xlim=c(0,2),ylim<-c(min(x),max(x)),xlab = "",ylab="",xaxt="n",main=main)
    axis(1, at=1, labels=c("x"))
    lines(c(1-b1,1+b1,1+b1,1-b1,1-b1),c(q[2],q[2],q[4],q[4],q[2]),lwd=lwd)
    lines(c(1,1),c(q[4],q[5]),lty=2,lwd=lwd)
    lines(c(1,1),c(q[2],q[1]),lty=2,lwd=lwd)
    lines(c(1-b2,1+b2),c(q[1],q[1]),lwd=lwd)
    lines(c(1-b2,1+b2),c(q[5],q[5]),lwd=lwd)
  } else {
    q<-quantile(x,type = 2)
    plot(c(1-b1,1+b1),c(q[3],q[3]),type = "l",lwd=lwd*3,xlim=c(0,3),ylim<-c(min(c(x,y)),max(c(x,y))),xlab = "",ylab="",xaxt="n",main=main)
    axis(1, at=1:2, labels=c("x","y"))
    lines(c(1-b1,1+b1,1+b1,1-b1,1-b1),c(q[2],q[2],q[4],q[4],q[2]),lwd=lwd)
    lines(c(1,1),c(q[4],q[5]),lty=2,lwd=lwd)
    lines(c(1,1),c(q[2],q[1]),lty=2,lwd=lwd)
    lines(c(1-b2,1+b2),c(q[1],q[1]),lwd=lwd)
    lines(c(1-b2,1+b2),c(q[5],q[5]),lwd=lwd)
    q<-quantile(y,type = 2)
    lines(c(2-b1,2+b1),c(q[3],q[3]),type = "l",lwd=lwd*3,xlim=c(0,3),ylim<-c(min(x),max(x)),xlab = "x",ylab="",xaxt="n")
    lines(c(2-b1,2+b1,2+b1,2-b1,2-b1),c(q[2],q[2],q[4],q[4],q[2]),lwd=lwd)
    lines(c(2,2),c(q[4],q[5]),lty=2,lwd=lwd)
    lines(c(2,2),c(q[2],q[1]),lty=2,lwd=lwd)
    lines(c(2-b2,2+b2),c(q[1],q[1]),lwd=lwd)
    lines(c(2-b2,2+b2),c(q[5],q[5]),lwd=lwd)
  }
}

#######################################################
# BEISPIEL 1
#######################################################

x <- c(4,2,6,3,3,1,5,2,2,1,0,4,2,5,5,3,7,2,1,3)
h<- table(x)

#x <- c(203, 463, 87, 101, 4, 142)
pdf("stabdiagramm.pdf")
plot(h, type='h', xlab='a_j (Anzahl der Störungen)', ylab='h_j',cex.axis=2,lwd=3.5,cex=2,cex.lab = 2)
dev.off()
pdf("stabdiagramm2.pdf")
plot(h/length(x), type='h', xlab='a_j (Anzahl der Störungen)', ylab='w_j',cex.axis=2,lwd=3.5,cex=2,cex.lab = 2)
dev.off()

#### Kreisdiagramm
pdf("kreisdiagramm.pdf")
pie(h,cex=3)
dev.off()

#### emp. VF
pdf("emp_vf.pdf")
plot(ecdf(x),main="",cex.axis=2,lwd=3.5,cex=2,cex.lab = 2,ylab="s_n(x)")
dev.off()


pdf("Boxplot.pdf",width = 4,height=7)
#boxplot(x,lwd=2)
boxplot2(x,lwd=2)
dev.off()


#######################################################
# BEISPIEL 2
#######################################################
#### (Bsp mit stetigen Daten)


n<-100
set.seed(12)
x<- rexp(n,rate = 0.0005)
x<-round(x,1)
hist(x)
length(table(x))
M<-cbind(sort(x),1,1:n, 1/n, (1:n)/n )
colnames(M)<-c("a_j","h_j", "h_1+...+h_j","w_j","w_1+...+w_j")
head(M)
# M per Hand in Excel kopieren und als pdf exportieren, dann in die Folien einfuegen

#### Stabdiagramm
h<- table(x)

# unuebersichtliches Stabdiagramm
pdf("stabdiagramm3.pdf")
plot(h, type='h', xlab='a_j (Anzahl der Störungen)', ylab='h_j',cex.axis=2,lwd=1.5,cex=2,cex.lab = 2)
dev.off()               

# unuebersichtliches Kreisdiagramm
pdf("kreisdiagramm2.pdf")
pie(h,cex=0.6)
dev.off()               

#### Boxplot
pdf("Boxplot2.pdf",width = 4,height=7)
boxplot(x,range=0,lwd=3)
dev.off()

#### Klassierte Tabelle
kl<-c(0,1000,2000,3000,4000,5000,6000,7000,8000,9000)
k<-length(kl)-1
H<-data.frame(matrix(data=NA,nrow=k,ncol = 6))
#colnames(H)<-c("$j$","Klasse $K_j$", "abs. Haufigkeit $h_j$", "rel" )
H[,1]<-1:k
for (i in 1:k){
  H[i,2]<- paste("[",kl[i],",",kl[i+1],")",sep="")
  H[i,3]<- sum( (x>=kl[i]) & (x < kl[i+1]) )
  H[i,4]<- 0.5*(kl[i]+kl[i+1])
  H[i,5]<- H[i,3]/n
  H[i,6]<- H[i,5]
  if (i>1){
    H[i,6]<- H[i,5] + H[i-1,6]
  }
}
(H)

#### histogramm
pdf("hist1.pdf")
hist(x,ylab="Häufigkeit",xlab="Klassen",main="",cex.axis=2,lwd=2.5,cex=2,cex.lab = 1.4)
dev.off()
pdf("hist2.pdf")
kl<-c(0,500,1000,1500,2000,3000,4000,5000,6000,7000,9000)
hist(x,breaks = kl,ylab="",xlab="Klassen",main="",cex.axis=2,lwd=2.5,cex=2,cex.lab = 1.4)
dev.off()

#### emp VF
pdf("emp_vf2.pdf")
plot(ecdf(x),main="",cex.axis=2,lwd=1.5,cex=0.61,cex.lab = 1.7,ylab="s_n(x)")
dev.off()

#### Verteilungsfunktion aus klassierten Daten
kl<-c(0,1000,2000,3000,4000,5000,6000,7000,8000,9000)
k<-length(kl)-1
y<-rep(0,length(x))
for (i in 1:k){
  y[x>=kl[i]]<- kl[i]
}

ytab<-as.vector(table(y))
Fy<-c()

for (i in 1:length(ytab)){
  Fy[i]<-sum(ytab[1:i])/sum(ytab)
}
pdf("emp_vf3.pdf")
plot(c(-1000,kl),c(0,0,Fy),type="l",xlab = "x", ylab="Verteilungsfunktion für klassierte Daten")
points(c(-1000,kl),c(0,0,Fy),pch=19)
dev.off()




#######################################################
# BEISPIEL 3
#######################################################
#### (2 dimensional mit stetigen Daten)

#### Streudiagramm
pdf("streudiagramm_ozon.pdf")
plot(airquality$Ozone,airquality$Temp,pch=19,cex=1.5,cex.lab = 1.7,ylab="y",cex.axis=2,xlab="x")
dev.off()

#### Diskretisieren
oz<-(airquality$Ozone<50) + 2*((airquality$Ozone>=50) & (airquality$Ozone<100)) +  3*(airquality$Ozone>=100)
tm<-(airquality$Temp>=75) +0
table(oz,tm)

pdf("streudiagramm_ozon2.pdf")
plot(airquality$Ozone,airquality$Temp,pch=19,cex=1.5,cex.lab = 1.7,ylab="y",cex.axis=2,xlab="x")
abline(75,0,lwd=2.5,col="red")
abline(v = 50,lwd=2.5,col="blue")
abline(v = 100,lwd=2.5,col="blue")
dev.off()

#### Regressionsgerade
pdf("streudiagramm_ozon_mit_regression.pdf")
plot(airquality$Ozone,airquality$Temp,pch=19,cex=1.5,cex.lab = 1.7,ylab="y",cex.axis=2,xlab="x")
abline(lm(airquality$Temp~airquality$Ozone), col="red",lwd=4)
dev.off()

