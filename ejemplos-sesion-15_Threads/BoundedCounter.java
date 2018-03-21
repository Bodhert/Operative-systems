public class BoundedCounter 
   implements ICounter {

    private int value;
    private int maxvalue;

    public BoundedCounter(int value, int maxvalue) {
	this.value = value;
	this.maxvalue = maxvalue;
    }
    
    public synchronized void incr() {

	while (value == maxvalue) {
	    try {
		wait();
	    } catch(InterruptedException ie) { }
	}
	value++;
    }

    public synchronized void decr() {
      
	if (value == maxvalue) {
	    notifyAll();
	}
	value--;
    }

    public synchronized int getValue() {
	return value;
    }
}
