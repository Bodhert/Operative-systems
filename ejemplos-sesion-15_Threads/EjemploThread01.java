// Este ejemplo: Muestra el hilo principal de un proceso.
// compilar: javac EjemploThread01.java
// ejecutar: java EjemploThread01

public class EjemploThread01 {

    public static void main(String args[]) {

	Thread t = Thread.currentThread();
	System.out.println("Thread " + t);
	t.setPriority(Thread.MAX_PRIORITY);
	System.out.println("Thread: " + t);
    }
}
