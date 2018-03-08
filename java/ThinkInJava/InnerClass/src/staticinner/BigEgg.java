package staticinner;

//: BigEgg.java
// An inner class cannot be overriden
// like a method

class Egg {
	
	protected class Yolk {
		public Yolk() {
			System.out.println("Egg.Yolk()");
		}
	}
	
	private Yolk y;

	public Egg() {
		// TODO Auto-generated constructor stub
		System.out.println("New Egg()");
		y = new Yolk();
	}
}

public class BigEgg extends Egg {
	
	public class Yolk {
		public Yolk() {
			System.out.println("BigEgg.Yolk()");
		}
	}
	
	public static void main(String[] args) {
		new BigEgg();
		// print:
		// New Egg()
		// Egg.Yolk()
	}
}