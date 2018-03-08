package parcel;

abstract class Contents {
	abstract public int value();
}

interface Destination {
	String readLabel();
}

public class Parcel3 {

	private class PContents extends Contents {
		private int i = 11;
		public int value() {
			return i;
		}
	}
	
	protected class PDestination implements Destination {
		private String label;
		private PDestination(String whereTo) {
			label = whereTo;
		}
		public String readLabel() {
			return label;
		}
	}
	
	public Destination dest(String s) {
		return new PDestination(s);
	}
	
	public Contents cont() {
		return new PContents();
	}
}
