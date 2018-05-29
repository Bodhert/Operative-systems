public class Garden  {

    public ICounter counter;

    public Garden(ICounter counter) {
	this.counter = counter;
    }

    public void leftEntry() {
	counter.incr();
    }

    public void rightEntry() {
	counter.incr();
    }

    public void leftExit() {
	counter.decr();
    }

    public void rightExit() {
	counter.decr();
    }

    public int getUserInGarden() {
	return counter.getValue();
    }
}
