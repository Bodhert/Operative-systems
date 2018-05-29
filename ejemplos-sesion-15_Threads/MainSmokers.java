public class MainSmokers {

    public static void main(String args[]) {

	Table table = new Table();

        for (int i = 0; i < 3; i++) {
	    Thread t = new Thread(new Smoker(CigaretteParts.fromOrdinal(i), 
					     table));
	    t.start();
	} 
	Thread t = new Thread(new Agent(table));
	t.start();
	try {
	    t.join();
	} catch(InterruptedException ie) { }
    }
}
