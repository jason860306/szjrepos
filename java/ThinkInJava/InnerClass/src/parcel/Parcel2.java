package parcel;

public class Parcel2 {

	class Contents {
		private int i = 11;
		public int value() {
			return i;
		}
	}
	
	class Destination {
		private String label;
		Destination(String whereTo) {
			label = whereTo;
		}
		String readLabel() {
			return label;
		}
	}
	
	public Destination to(String s) {
		return new Destination(s);
	}
	
	public Contents cont() {
		return new Contents();
	}
	
	public void ship(String dest) {
		Contents c = cont();
		Destination d = to(dest);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated constructor stub
		Parcel2 i = new Parcel2();
		i.ship("Tanzania");
		Parcel2 j = new Parcel2();
		// Defining handles to inner classes;
		Parcel2.Contents c = j.cont();
		Parcel2.Destination d = j.to("Borneo");
	}
}
