package ejercicio;

import java.net.*;
import java.util.Scanner;
import java.io.*;
public class servidormultihilo{	
	public static void main(String[] args) throws Exception{	
		Socket servicioCliente = null;
		ServerSocket servidor = new ServerSocket(5432);
		while( true ){
			try{			
				// ServerSocket me da el Socket
				servicioCliente = servidor.accept();
				// Instancio un Thread
				(new Tarea(servicioCliente)).start();				
			}catch(Exception e){			
				System.err.println("Error: " + e.getMessage());		
			}		
		}	
	}
	static class Tarea extends Thread{	
		private Socket servicioCliente = null;
		private ObjectInputStream entradaServidor = null;;
		private ObjectOutputStream salidaServidor = null;
		public Tarea(Socket socket){		
			this.servicioCliente = socket;		
		}
		public void run(){
			try{			
				// Informacion del cliente
				System.out.println("Se conectaron desde la IP:"+servicioCliente.getInetAddress());
				
				// Entrada y salida
				entradaServidor = new
				ObjectInputStream(servicioCliente.getInputStream());				
				salidaServidor = new				
				ObjectOutputStream(servicioCliente.getOutputStream());				
				// envio el numero del 0 al 111111111111111111111111111111111111111111111111111111111111
				System.out.println("escribe un numero binario de 0 a 111111111111111111111111111111111111111111111111111111111111");
				Scanner sc = new Scanner(System.in);
				String binario = sc.nextLine();
				// Envio el digito al cliente
				salidaServidor.writeObject(binario);
				// Leo el resultado que envia el cliente
				String nom = (String)entradaServidor.readObject();
				System.out.println("número enviado: "+nom);			
			}
			catch(Exception e){			
				System.err.println("Error: " + e.getMessage());
			}
			finally{
				try{				
					if( salidaServidor !=null ) salidaServidor.close();
					if( entradaServidor !=null ) entradaServidor.close();
					if( servicioCliente != null ) servicioCliente.close();
					System.out.println("Conexion cerrada!");					
				}catch(Exception e){				
					System.err.println("Error: " + e.getMessage());				
				}			
			}		
		}
	}
}