package innerscopes;

public class Parcel6 {
	public Contents cont() {
		//该语法与下面cont1函数功能等价
		return new Contents() {
			private int i = 11;
			public int value() {
				return i;
			}
		}; // Semicolon required in this case
	}
	
	public Contents cont1() {
		class PContents implements Contents {
			private int i = 11;
			public int value() {
				return i;
			}
		}
		return new PContents();
	}
	
	public static void main(String[] args) {
		Parcel6 p = new Parcel6();
		Contents c = p.cont();
		c = p.cont1();
		System.exit(0);
	}
}