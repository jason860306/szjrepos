package staticinner;

public class Parcel11 {
	
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
	
	public static void main(String[] args) {
		Parcel11 p = new Parcel11();
		// Must use instance of outer class(p) to create an instances of the inner class(c, d);
		Parcel11.Contents c = p.new Contents();
		System.out.println(c.value());
		// can't create an instance of an inner class like cplusplus
		// c = new Parcel11.Contents();
		Parcel11.Destination d = p.new Destination("Tanzania");
		System.out.println(d.readLabel());
	}
}