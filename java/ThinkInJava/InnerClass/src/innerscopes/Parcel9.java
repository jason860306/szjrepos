package innerscopes;

// Using "instance initialization" to perform construction on an anonymous inner class
public class Parcel9 {
	public Destination dest(final String dest, final float price) {
		return new Destination() {
			private int cost;
			// Instance initialization for each object;
			{
				cost = Math.round(price);
				if (cost > 100) {
					System.out.println("Over budget!");
				}
			}
			private String label = dest;
			public String readLabel() {
				Object[] obj = new Object[2];
				obj[0] = label;
				obj[1] = Integer.valueOf(cost);
				return String.format("%1$s,%2$d",obj);
			}
		};
	}
	
	public Destination dest1(String dest, float price) {
		class PDestination implements Destination {
			private int cost;
			private String label;
			public PDestination(String str, float price) {
				cost = Math.round(price);
				if (cost > 100) {
					System.out.println("Over budget!");
				}
				label = str;
			}
			public String readLabel() {
				Object[] obj = new Object[2];
				obj[0] = label;
				obj[1] = Integer.valueOf(cost);
				return String.format("%1$s,%2$d", obj);
			}
		}
		return new PDestination(dest, price);
	}
	
	public static void main(String[] args) {
 		Parcel9 p = new Parcel9();
		Destination d = p.dest("Tanzania", 101.395F);
		System.out.println(d.readLabel());
		d = p.dest1("Hongkong",  101.395F);
		System.out.println(d.readLabel());
		System.exit(0);
	}
}