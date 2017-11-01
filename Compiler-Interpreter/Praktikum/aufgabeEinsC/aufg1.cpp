#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void lex(char * pX);
double fac();
double term(void);
double expr(void);

typedef struct morph {
	int     mc;		// morphem-code (siehe unten)
	double  dval;	// Zahl (wenn Zahl)
	char    cval;	// Zeichen (wenn Operand)
}MORPHEM;

enum mcodes {
	mempty,	// leer
	mop,	// Operant
	mdbl	// Zahl (ggf. "." für Gleitkomma)
};

static MORPHEM m;

void lex(char * pX) {
	static char * px;
	/* Initialisierung (wird nur beim ersten Aufruf (mit Eingabezeile) aufgerufen): */
	if (pX != NULL) {
		m.mc = mempty;
		px = pX;
	}
	/* lexikalische Analyse (sonst) */
	// wenn EOL: leer
	if (*px == '\0') {
		m.mc = mempty;
	} else {
		// überspringe Leerzeichen/Tabulatoren
		for (; *px == ' ' || *px == '\t'; px++);
		// Wenn nächstes Zeichen Zahl (oder Float-Seperator) ist: 
		if (isdigit(*px) || *px == '.') {
			m.dval = strtod(px, &px);	// Setze dval auf zu Zahl konvertierten Char (setzt auch Pointer weiter)
			m.mc = mdbl;
		} else
			switch (*px) {
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
				m.cval = *px++;	// Setze cval auf den entsprechenden Char (und setze Pointer weiter)
				m.mc = mop;
				break;
			default:
				printf("wrong ...: %c\n­ canceling  ­­\n", *px);
				exit(1);
			}
	}
}

double fac() {
	double tmp;
	if (m.mc == mop) {	// wenn Operand, dann Klammer berücksichtigen:
		if (m.cval == '(') {
			lex(NULL);
			tmp = expr();
			if (m.mc != mop || m.cval != ')')
				exit(1);
			lex(NULL);
		} else
			exit(1);
	} else
		if (m.mc == mdbl) {
			tmp = m.dval;
			lex(NULL);
		} else
			exit(1);
		return tmp;
}

double term(void) {
	double tmp = fac();	// Faktor berechnen
	if (m.mc == mop && m.cval == '*') {	// wenn aktuelle Stelle Operand * ist:
		lex(NULL);
		tmp *= term();	// Multipliziere mit Term
	}
	return tmp;
}

double expr(void) {
	double tmp = term();	// Term berechnen
	if (m.mc == mop && m.cval == '+') {	// wenn aktuelle Stelle Operand + ist:
		lex(NULL);
		tmp += expr();	// Addiere Expression
	}
	return tmp;
}

int main(int argc, char*argv[]) {
	//char str[4] = "2+3";
	//char *pBuf = str;
	char *pBuf = argv[1];
	printf("%s\n", pBuf);
	lex(pBuf);
	printf("%lf\n", expr());
	//printf("%lf\n", 1.0);
	return 0;
}