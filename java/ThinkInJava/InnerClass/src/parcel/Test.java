package parcel;

class Test {
	public static void main(String[] args) {
		Parcel3 i = new Parcel3();
		Contents c = i.cont();
		Destination d = i.dest("Tanzania");
		// Illegal -- can't access private class;
		//! Parcel3.PContents c = i.new PContents();
	}
}