package innerscopes;

public class Parcel7 {

	public Wrapping wrap(int x) {
		// Base constructor call; 功能等价于下面的wrap1函数
		return new Wrapping(x) {
			public int value() {
				return super.value() * 47;
			}
		}; // Semiconlon required
	}
	
	public Wrapping wrap1(int x) {
		class MyWrapping extends Wrapping {
			public MyWrapping(int x) {
				super(x);
			}
		}
		return new MyWrapping(x);
	}
	
	public static void main(String[] args) {
		Parcel7 p = new Parcel7();
		Wrapping w = p.wrap(10);
		System.out.println(w.value());
		w = p.wrap1(11);
		System.out.println(w.value());
	}
}