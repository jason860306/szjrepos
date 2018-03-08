package staticinner;

class Egg2 {
	
	protected class Yolk {
	
		public Yolk() {
			System.out.println("Egg2.Yolk()");
		}
		
		public void f() {
			System.out.println("Egg2.Yolk.f()");
		}
	}
	
	private Yolk y = new Yolk();
	
	public Egg2() {
		System.out.println("New Egg2()");
	}
	
	public void insertYolk(Yolk yy) {
		y = yy;
	}
	
	public void g() {
		y.f();
	}
}

public class BigEgg2 extends Egg2 {
	
//	public class Yolk extends Egg2.Yolk {
//		
//		public Yolk() {
//			System.out.println("BigEgg2.Yolk()");
//		}
//		
//		public void f() {
//			System.out.println("BigEgg2.Yolk.f()");
//		}
//	}

	public BigEgg2() {
		// TODO Auto-generated constructor stub
		insertYolk(new Yolk());
	}
	
	public static void main(String[] args) {
		Egg2 e2 = new BigEgg2();
		e2.g();
		// print:
		//		Egg2.Yolk()
		//		New Egg2()
		//		Egg2.Yolk()
		//		BigEgg2.Yolk()
		//		BigEgg2.Yolk.f()
	}
}
