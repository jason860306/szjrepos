package parcel;

public class Parcel1 {

	class Contents {
		private int i = 11;
		public int value() {
			return i;
		}
	}
	
	class Destination {
		private String label;
		public Destination(String whereTo) {
			// TODO Auto-generated constructor stub
			label = whereTo;
		}
		String readLabel() {
			return label;
		}
	}

	// Using inner classes looks just like using any other class, within Parcel1;
	public void ship(String dest) {
		Contents c = new Contents();
		Destination d = new Destination(dest);
	}
	
	public static void main(String[] args) {
		Parcel1 i = new Parcel1();
		i.ship("Tanzania");
		System.exit(0);
	}
}
