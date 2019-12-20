package ejercicio;

import java.net.ServerSocket;
import java.net.Socket;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
public class servidor{

	public static void main(String[] args) throws Exception{
		ObjectInputStream entradaServidor = null;
		ObjectOutputStream salidaServidor = null;
		Socket servicioCliente = null;
		ServerSocket servidor = new ServerSocket(5432);
		while( true ){
			try{
				// El ServerSocket me da el Socket
				servicioCliente = servidor.accept();
				// Informacion del cliente
				System.out.println("Se conectaron desde la IP: "
				+servicioCliente.getInetAddress());
				// Entrada y salida
				entradaServidor = new ObjectInputStream( servicioCliente.getInputStream() );
				salidaServidor = new ObjectOutputStream( servicioCliente.getOutputStream() );
				// Leo el nombre que envia el cliente
				String nom = (String)entradaServidor.readObject();
				// Armo el saludo personalizado que le quiero enviar
				String saludo = "HolaAAAAAAAAAAAA "+nom+", saludos desde el Servidor.";
				// Envio el saludo al cliente
				salidaServidor.writeObject(saludo);
				System.out.println("Saludo enviado...");
			}
			catch(Exception e){		
				System.err.println("Error: " + e.getMessage());
			}
			finally{		
				if( salidaServidor !=null ) salidaServidor.close();
				if( entradaServidor !=null ) entradaServidor.close();
				if( servicioCliente != null ) servicioCliente.close();
				servidor.close();
				System.out.println("Conexion cerrada!");
				System.exit(0);
			}
			
		}
	}
}