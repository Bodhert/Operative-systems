public class MainBoundedGarden {

    public static void main(String args[]) {

	ICounter counter = new BoundedCounter(0,30);
	Garden garden = new Garden(counter);

        for (int i = 0; i < 200; i++) {
	    Thread t = new Thread(new Person(garden));
	    t.start();
	} 

	while(true) {
	    try {
		Thread.sleep(100);
	    } catch(InterruptedException ie) {
	    }
	    System.out.println("User in garden: " + garden.getUserInGarden());
	}
    }
}
