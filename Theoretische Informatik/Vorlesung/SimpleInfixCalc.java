package parsers;

public class SimpleInfixCalc {
	String input;
	int pos;

	int x = 1;
	int y = 2;
	int z = 3;
	
	int parse(String input) {
		this.input = input + '#';
		pos = 0;
		int e = E(); match('#');
		return e;
	}

	int E() {
		int e = T();
		while(next() == '+' || next() == '-')
			if(next() == '+') {
				match('+');	e += T();
			} else {
				match('-');	e -= T();
			}
		return e;
	}

	int T() {
		int t = F();
		while(next() == '*' || next() == '/')
			if(next() == '*') {
				match('*'); t *= F();
			} else {
				match('/'); t /= T();
			}
		return t;
	}
	
	int F() {
		int f;
		if(next() == '(') {
			match('('); f = E(); match(')');
		}
		else f = Num();
		return f;
	}
	
	int Num() {
		switch(next()) {
			case 'x': match('x'); return x;
			case 'y': match('y'); return y;
			case 'z': match('z'); return z;
			default: throw new IllegalArgumentException(next() + " unexpected");
		}
	}
	
	char next() {
		return input.charAt(pos);
	}

	void match(char c) {
		if(next() == c) pos++;
		else throw new IllegalArgumentException(c + " unexpected");
	}

	public static void main(String[] args) {
		SimpleInfixCalc c = new SimpleInfixCalc();
		System.out.println(c.parse("x+y*z/y-x"));
	}
}
