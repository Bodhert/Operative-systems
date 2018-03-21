// EjemploThread07java
// Muestra como interrumpir un hilo sin utilizar funciones
// bloqueantes, sino que el hilo ignora tres intentos de
// interrupciones y en el cuarto muere.

// compilar: javac EjemploThread07.java
// ejecutar: java EjemploThread07

class EjemploThread implements Runnable {

    private int value = 0;
    private int intentos = 0;

    public void run() {

	boolean toEnd = false;

	while (!toEnd) {
	    value++;
	    if (value % 100 != 0) {
		Thread t = Thread.currentThread();
		System.out.println("Thread: " + t +
				   " trabajando: " + value);
		if (t.isInterrupted()) {
		    if (++intentos % 4 == 0) {
			toEnd = true;
		    }
		}
	    }
	}
	System.out.println("Thread: " + Thread.currentThread() + 
			   " ya he decidido morir");
    }

}

public class EjemploThread07 {

    public static void main(String args[]) {
	Runnable hilo = new EjemploThread();
	Thread t = new Thread(hilo, "Ejemplo hilo 07");
	t.start();
	System.out.println("Thread: " + Thread.currentThread());

	try {
	    Thread.currentThread().sleep(5000);
	} catch (InterruptedException ie) { }

	int value = 10;
	for (int i = 0; i < value; i++) {
	    t.interrupt();
	}
	try {
	    t.join();
	} catch (InterruptedException ie) { }
    }
}
