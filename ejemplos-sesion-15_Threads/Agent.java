import java.util.Random;

public class Agent implements Runnable {

    private Table table;

    public Agent(Table table) {

	this.table = table;
    }

    public void run() {

	Random random = new Random();
	while (true) {
	    
	    System.out.println("Agent is preparing materials for a smoker");
	    // Preparing parts of the cigarette
	    try {
	       Thread.sleep(Math.abs(random.nextInt()) % 1000);
	    } catch(InterruptedException ie) { }

	    CigaretteParts cp = 
		CigaretteParts.fromOrdinal(Math.abs(random.nextInt()));

	    table.putMaterial(cp);
	    System.out.println("Agent is waiting for smoker");
	    table.waitForSignal();
	}
    }
}
