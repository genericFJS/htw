# Ordner festlegen in dem Dateien gespeichert/gelesen werden sollen
#setwd("/home/MEIN_LIEBLINGS_ORDNER")

################

# Bsp zur Kurvendiskussion

f<-function(x){x^2* (log(x))^4}
x<-seq(0.00001,2,length.out = 20000)

#pdf("bsp1_bild1.pdf",width=10,height=10)   zum Abspeichern als pdf (start)
plot(x,f(x),type="l",lwd=2,main="f(x)=x^2 * (log(x))^4")
xe<-c(1,exp(-2))
points(xe,f(xe),col="red",pch=19,cex=1.5)
xw<-c(exp(-3-sqrt(3)),exp(-3+sqrt(3)))
points(xw,f(xw),col="blue",pch=3,cex=2,lwd=2)
#dev.off()     zum Abspeichern als pdf (stop)


#pdf("bsp1_bild2.pdf",width=10,height=10)
plot(x,f(x),type="l",lwd=2,xlim=c(0,0.04),ylim=c(0,0.2),main="f(x)=x^2 * (log(x))^4")
points(xw,f(xw),col="blue",pch=3,cex=2,lwd=2)
#dev.off()


################

# Ellipse

t<-seq(0,2*pi,length.out = 2000)
a<-2
b<- 0.7
phi<- pi/5
plot(a*cos(t),b*sin(t),asp=1,type="l",lwd=2,main=paste("x(t)=",a,"cos(t), y(t)=",b,"sin(t), t_0=",phi/pi,"pi",sep=""),col="blue")
lines(a*cos(t),a*sin(t),asp=1,type="l",lwd=2)
lines(b*cos(t),b*sin(t),asp=1,type="l",lwd=2)
text(a+0.071,-0.1,"a",cex=1.3)
text(-a-0.071,-0.1,"-a",cex=1.3)
text(b+0.071,-0.1,"b",cex=1.3)
text(-b-0.071,-0.1,"-b",cex=1.3)
lines(c(0,0),c(-10,10),col="gray")
lines(c(-10,10),c(0,0),col="gray")
lines(c(0,a*cos(phi),a*cos(phi)),c(0,a*sin(phi),0))
t2<-seq(0,phi,length.out = 100)
lines(0.5*cos(t2),0.5*sin(t2))
text(0.35,0.1,expression(t[0]),cex=2)
text(-0.2,b*sin(phi),expression(y(t[0])),cex=1.5)
text(a*cos(phi),-0.2,expression(x(t[0])),cex=1.5)
lines(c(0,a*cos(phi)),c(b*sin(phi),b*sin(phi)),lty=2)
points(c(a*cos(phi),b*cos(phi),a*cos(phi)), c(a*sin(phi),b*sin(phi),b*sin(phi)),col="red",pch=19)


################

# Halbkreis in Polarkoordinaten

a<-8
phimin<-0; phimax<-pi/2
phi<-seq(phimin,phimax,length.out = 200)
t0g<-c(0,15,30,45,60,75,90)
t0b<-t0g*pi/180
r<- a*cos(phi)
x<-r * cos(phi)
y<-r * sin(phi)
plot(x,y,asp=1,type="l",lwd=2,main=paste("Plot von r(phi)=",a,"cos(phi),  mit phi aus [",phimin,",",phimax/pi,"pi ]",sep=""),col="blue",xaxs="i")
for (i in 1:length(t0b)){
  abline(0,tan(t0b[i]))
  text(a/1.5*cos(t0b[i]),a/1.5*sin(t0b[i]),t0g[i],xpd=T)
}


################

# Kardioide in Polarkoordinaten

a<-8
phimin<-0; phimax<-2*pi
phi<-seq(phimin,phimax,length.out = 500)
t0g<-c(0,120,240)
t0b<-t0g*pi/180
r<- a*(1+cos(phi))
x<-r * cos(phi)
y<-r * sin(phi)
plot(x,y,asp=1,type="l",lwd=1,main=paste("Plot von r(phi)=",a,"cos(phi),  mit phi aus [",phimin,",",phimax/pi,"pi ]",sep=""),col="blue",xaxs="i")
abline(v=0);abline(h=0)
lines(x,y,lwd=2,col="blue")
r<- a*(1+cos(t0b))
x<-r * cos(t0b)
y<-r * sin(t0b)
points(x,y,col="red",pch=19,cex=2)
abline(v=x[1],col="red",lwd=2)
abline(v=x[2],col="red",lwd=2)
lines(c(0,20*cos(t0b[2])),c(0,20*sin(t0b[2])) ,col="gray")
lines(c(0,20*cos(t0b[3])),c(0,20*sin(t0b[3])) ,col="gray")
text(a/1.5*cos(t0b[2]),a/1.5*sin(t0b[2]),t0g[2],xpd=T)
text(a/1.5*cos(t0b[3]),a/1.5*sin(t0b[3]),t0g[3],xpd=T)


################

# 3d Schraubenlinie
library(scatterplot3d)
t <- seq(0,6*pi,0.01)
x <- sin(t)
y <- cos(t)
z <- 5*t
{
 # x11()      # keep old plot and open a new plotting window
  scatterplot3d(x,y,z,highlight.3d=TRUE,col.axis="blue",
                col.grid="lightblue", main="Plot of a Function R -> R^3", pch=20)
}

