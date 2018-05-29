// EjemploThread05java
// Muestra como crear un hilo a partir de la interface Runnable
// y tambien muestra que la variable de referencia t:Thread puede
// ser asignada a otro hilo que corre independiente.
// compilar: javac EjemploThread05.java
// ejecutar: java EjemploThread05

class EjemploThread implements Runnable {

    private int value = 0;

    public void run() {
	value++;
	System.out.println("Thread: " + Thread.currentThread() 
			   + " value: " + value);
    }
}

public class EjemploThread05 {

    public static void main(String args[]) {

	Runnable hilo = new EjemploThread();

	Thread t = new Thread(hilo, "Ejemplo hilo 1-05");

	t.start();
	System.out.println("Thread: " + Thread.currentThread());
	try {
	    t.join();
	}
	catch (InterruptedException ie) { }

	t = new Thread(hilo, "Ejemplo hilo 2-05");
	t.start();

	try {
	    t.join();
	}
	catch (InterruptedException ie) { }

    }
}
