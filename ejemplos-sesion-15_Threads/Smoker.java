import java.util.Random;

public class Smoker implements Runnable {

    private CigaretteParts cp;
    private Table table;

    public Smoker(CigaretteParts cp, Table table) {
	this.cp = cp;
	this.table = table;
    }

    public void run() {
	Random random = new Random();

	while (true) {
	    table.waitFor(cp);
	    // Enjoy for a good cigarette
	    System.out.printf("smoker with %s is smoking\n", cp);
	    try {
	       Thread.sleep(Math.abs(random.nextInt()) % 1000);
	    } catch(InterruptedException ie) { }
	    table.setSignal();
	}
    }
}
