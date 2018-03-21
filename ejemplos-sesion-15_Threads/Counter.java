public class Counter 
   implements ICounter {

    private int value;

    public Counter(int value) {
	this.value = value;
    }
    
    public synchronized void incr() {
	value++;
    }

    // public void incr() {
    // 	synchronized(this) {
    // 	    value++;
    // 	}
    // }

    public synchronized void decr() {
	value--;
    }

    public synchronized int getValue() {
	return value;
    }
}
