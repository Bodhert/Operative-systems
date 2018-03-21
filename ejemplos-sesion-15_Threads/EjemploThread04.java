// EjemploThread04.java
// Muestra como crear un hilo a partir de la interface Runnable
// y tambien muestra que los hilos no se pueden reiniciar.
// compilar: javac EjemploThread04.java
// ejecutar: java EjemploThread04

class EjemploThread implements Runnable {

    public void run() {

	System.out.println("Thread: " + Thread.currentThread());
    }
}

public class EjemploThread04 {

    public static void main(String args[]) {

	Runnable hilo = new EjemploThread();

	Thread t = new Thread(hilo, "Ejemplo hilo 04");
	t.start();
	System.out.println("Thread: " + Thread.currentThread());

	try {
	    t.join();
	}
	catch (InterruptedException ie) { }

	t.start();

	try {
	    t.join();
	}
	catch (InterruptedException ie) { }

    }
}
