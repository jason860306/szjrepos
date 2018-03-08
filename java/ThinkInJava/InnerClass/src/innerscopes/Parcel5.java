package innerscopes;

public class Parcel5 {

	private void internalTracking(boolean b) {
		if (b) {
			// 该类会随机着其它类一起编译，并不受这里的判断条件影响而导致只有在满足条件时才编译。
			class TrackingSlip {
				private String id;
				TrackingSlip(String s) {
					id = s;
				}
				String getSlip() {
					return id;
				}
			}
			TrackingSlip ts = new TrackingSlip("slip");
			String s = ts.getSlip();
		}
		// Can't use it here! out of scope;
		//! TrackingSlip ts = new TrackingSlip("x");
	}

	public void track() {
		internalTracking(true);
	}
	
	public static void main(String[] args) {
		Parcel5 p = new Parcel5();
		p.track();
	}
}