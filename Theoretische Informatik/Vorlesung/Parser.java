package parsers;

public class Parser {
	String input;
	int pos;

	boolean parse(String input0) {
		input = input0 + "#";
		pos = 0;
		return S() && match('#');
	}
	
	boolean S() {
		if(next() == 'a')
			return match('a') && S() && match('b');
		else return true;
	}

	char next() {
		return input.charAt(pos);
	}

	boolean match(char c) {
		if(next() == c) {
			pos++;
			return true;
		} 
		else return false;
	}

	public static void main(String[] args) {
		Parser p = new Parser();
		System.out.println(p.parse("aabb"));
	}
}