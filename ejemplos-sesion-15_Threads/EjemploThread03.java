// EjemploThread03.java
// Muestra como crear un hilo a partir de la interface Runnable
// compilar: javac EjemploThread03.java
// ejecutar: java EjemploThread03

class EjemploThread implements Runnable {

    public void run() {

	System.out.println("Thread: " + Thread.currentThread());
    }
}

public class EjemploThread03 {

    public static void main(String args[]) {

	Runnable hilo = new EjemploThread();

	Thread t = new Thread(hilo, "Ejemplo hilo 03");

	t.start();

	System.out.println("Thread: " + Thread.currentThread());

	try {
	    t.join();
	}
	catch (InterruptedException ie) { }
    }
}
