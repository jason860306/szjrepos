package controller;

// The common methods for any control event

abstract public class Event {

	private long evtTime;
	
	public Event(long eventTime) {
		// TODO Auto-generated constructor stub
		evtTime = eventTime;
	}
	
	public boolean ready() {
		return System.currentTimeMillis() >= evtTime;
	}
	
	abstract public void action();
	abstract public String description();
}
