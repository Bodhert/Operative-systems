// EjemploThread06java
// Muestra como interrumpir un hilo
// compilar: javac EjemploThread06java
// ejecutar: java EjemploThread06

class EjemploThread implements Runnable {


    public void run() {

	boolean toEnd = false;

	while (!toEnd) {

	    System.out.println("Thread: " + Thread.currentThread());

	    try {
		Thread.currentThread().sleep(1000);
	    } catch (InterruptedException ie) {
		System.out.println("Thread: " + Thread.currentThread() +
				   " fue interrunpido va a terminar");
		toEnd = false;
	    }
	}
    }
}

public class EjemploThread06 {

    public static void main(String args[]) {
	Runnable hilo = new EjemploThread();
	Thread t = new Thread(hilo, "Ejemplo hilo 06");

	t.start();
	System.out.println("Thread: " + Thread.currentThread());

	try {
	    Thread.currentThread().sleep(5000);
	} catch (InterruptedException ie) { }

	System.out.println("Thread: " + Thread.currentThread() +
			   "  va interrumpir el thread: " +
			   t);
	t.interrupt();

	try {
	    t.join();
	} catch (InterruptedException ie) { }

    }
}
