package innerscopes;

public class Parcel8 {
	
	// Argument must be final to use inside anonymous inner class;
	// 参数dest必须定义成final属性，因为java规定在定义一个匿名内部类
	// 且想使用在匿名内部类外面定义的某个对象时，则必须把这个外部的
	// 对象定义为final属性
	public Destination dest(final String dest) {
		return new Destination() {
			private String label = dest;
			public String readLabel() {
				return label;
			}
		};
	}
	
	public Destination dest1(String dest) {
		class PDestination implements Destination {
			private String label;
			public PDestination(String str) {
				label = str;
			}
			public String readLabel() {
				return label;
			}
		}
		return new PDestination(dest);
	}
	
	public static void main(String[] args) {
		Parcel8 p = new Parcel8();
		Destination d = p.dest("Tanzania");
		System.out.println(d.readLabel());
		d = p.dest1("Hongkong");
		System.out.println(d.readLabel());
		System.exit(0);
	}
}