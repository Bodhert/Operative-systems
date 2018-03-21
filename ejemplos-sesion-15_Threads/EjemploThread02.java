// EjemploThread02
// Muestra como crear un hilo en java heredando de la clase Thread
// compilar: $ javac EjemploThread02.java
// ejecutar: $ java EjemploThread02
public class EjemploThread02 extends Thread {

    public EjemploThread02(String name) {
	super(name);
    }

    // Este es el punto de entrada de un hilo
    public void run() {
	System.out.println("Thread run: " + Thread.currentThread());
    }

    public static void main(String args[]) {

	Thread t = new EjemploThread02("Hilo ejemplo02");

	System.out.println("Thread main: " + Thread.currentThread());
	t.start();
	try {
	    t.join();
	} catch (InterruptedException ie) { }
    }
}
