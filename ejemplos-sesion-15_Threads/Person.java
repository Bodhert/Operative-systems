import java.util.Random;

public class Person implements Runnable {

    private Garden garden;
    private Random random;

    public Person(Garden garden) {
	this.garden = garden;
	this.random = new Random();
    }

    private boolean setSide() {
	return Math.abs(random.nextInt()) % 2 == 0;
    }

    public void run() {
	while (true) {
	    // Esperar afuera:
	    try {
		Thread.sleep(Math.abs(random.nextInt()) % 1000);
	    } catch(InterruptedException ie) { }
	    if (setSide()) {
		garden.leftEntry();
	    }
	    else {
		garden.rightEntry();
	    }
	    // Esperar adentro:
	    try {
		Thread.sleep(Math.abs(random.nextInt()) % 1000);
	    } catch(InterruptedException ie) { }
	    if (setSide()) {
		garden.leftExit();
	    }
	    else {
		garden.leftExit();
	    }
	}
    }
}
