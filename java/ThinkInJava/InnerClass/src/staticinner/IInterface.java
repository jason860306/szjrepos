package staticinner;

public class IInterface {
	static class Inner {
		
		int i, j, k;
		
		public Inner() {
		}
		
		void f() {
			
		}
	}
}

class TestBed {

	TestBed() {
		
	}
	
	void f() {
		System.out.println("f()");
	}
	
	// 为运行程序，请使用"java TestBed.Tester"命令，可将这个类用于测试，但不需在
	// 最终发行版本中包含它
	public static class Tester {
		public static void main(String[] args) {
			TestBed t = new TestBed();
			t.f();
		}
	}
}