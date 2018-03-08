package staticinner;

class WithInner {
	class Inner {}
}

public class InheritInner extends WithInner.Inner {

	// Won't compile
//	public InheritInner() {
//
//	}

	InheritInner(WithInner wi) {
		wi.super();
		// super();
	}
	
	public static void main(String[] args) {
		WithInner wi = new WithInner();
		InheritInner ii = new InheritInner(wi);
	}
}