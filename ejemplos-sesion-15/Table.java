public class Table {

    private CigaretteParts accp = CigaretteParts.NOTHING;
    private boolean signaled = false;

    public Table() {
    }

    public synchronized void putMaterial(CigaretteParts cp) {
	accp = cp;
	signaled = false;
	notifyAll();
    }

    public synchronized void waitFor(CigaretteParts cp) {

	while (accp == CigaretteParts.NOTHING &&
	       !accp.equals(cp)) {
	    try {
		wait();
	    } catch(InterruptedException ie) { }
	}
	accp = CigaretteParts.NOTHING;
    }

    public synchronized void waitForSignal() {
	while(!signaled) {
	    try {
		wait();
	    } catch(InterruptedException ie) { }
	}
	signaled = false;
	accp = CigaretteParts.NOTHING;
    }

    public synchronized void setSignal() {
	signaled = true;
	notifyAll();
    }
}

