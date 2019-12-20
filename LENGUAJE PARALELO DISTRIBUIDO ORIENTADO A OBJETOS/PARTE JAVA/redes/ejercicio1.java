package practica6;

import java.net.*;
class pc6 {
	public static void main (String args[]) {
		try {
			InetAddress direccion = InetAddress.getLocalHost();
			System.out.println("Nombre y dirección del servidor local:");
			System.out.println(direccion);
			direccion = InetAddress.getByName ("www.uni.edu.pe");
			System.out.println(direccion);
			InetAddress lista [] = InetAddress.getAllByName ("www.google.com");
			for (int i=0; i<lista.length; i++)
					System.out.println(lista[i]);
			} catch (Exception e) {
					System.err.println("Error: " + e.getMessage());
			}
	}
}