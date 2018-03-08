package innerscopes;

interface Destination {
	String readLabel();
}

interface Contents {
	int value();
}

public class Wrapping {

	private int i;
	
	public Wrapping(int x) {
		i = x;
	}
	
	public int value() {
		return i;
	}
}