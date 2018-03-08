package innerscopes;

interface Selector {
	boolean end();
	Object current();
	void next();
}

public class Sequence {
	
	private Object[] obj;
	private int next = 0;
	
	public Sequence(int size) {
		obj = new Object[size];
	}
	
	public void add(Object x) {
		if (next < obj.length) {
			obj[next] = x;
			++next;
		}
	}
	
	// C++中虽然也可以实现嵌套类，但在C++中嵌套类里是不能直接访问主类中的成员变量的，
	// 因为C++中的嵌套类没有指向封装类（主类）对象的链接，而java中的内部类（其实也就
	// 是嵌套类）则可以通过一个指向主类（封装类）对象的链接很方便的直接访问主类中的成
	// 员变量，方便是方便了，不过C++还是一贯坚持他的严谨作风。
	private class SSelector implements Selector {
		int i = 0;
		
		public boolean end() {
			return (i == obj.length);
		}
		
		public Object current() {
			return obj[i];
		}
		
		public void next() {
			if (i < obj.length) {
				++i;
			}
		}
	}
	
	public Selector getSelector() {
		return new SSelector();
	}
	
	public static void main(String[] args) {
		Sequence s = new Sequence(10);
		for (int i = 0; i < 10; ++i) {
			s.add(Integer.toString(i));
		}
		Selector s1 = s.getSelector();
		while (!s1.end()) {
			System.out.println((String)s1.current());
			s1.next();
		}
		
		s1 = s.getSelector();
		while (!s1.end()) {
			System.out.println((String)s1.current());
			s1.next();
		}
		
		System.exit(0);
	}
}