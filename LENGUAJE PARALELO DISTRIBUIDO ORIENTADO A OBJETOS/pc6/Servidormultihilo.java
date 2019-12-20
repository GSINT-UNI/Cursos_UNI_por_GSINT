
import java.net.*;
import java.util.Scanner;
import java.io.*;
import java.util.concurrent.*;
public class Servidormultihilo{	
	public static void main(String[] args) throws Exception{	
		Socket servicioCliente = null;
		ServerSocket servidor = new ServerSocket(5432);
		Semaphore sem = new Semaphore(2);
		int numerodehilos = 0;
		while( true ){
			try{			
				// ServerSocket me da el Socket
				servicioCliente = servidor.accept();
				// Instancio un Thread
				recurso.numero++;
				System.out.println("hay "+ recurso.numero+ "  clientes activos");
				if(recurso.numero < 3) {
					(new Tarea(servicioCliente,sem)).start();					
				}else {
					System.out.println("Ya hay 2 clientes actrivos, espere su turno.");
				}
			}catch(Exception e){			
				System.err.println("Error: " + e.getMessage());		
			}		
		}	
	}
	static class recurso{
		static int numero = 0;
	}
	static class Tarea extends Thread{	
		private Socket servicioCliente = null;
		private ObjectInputStream entradaServidor = null;;
		private ObjectOutputStream salidaServidor = null;
		Semaphore sem;
		public Tarea(Socket socket, Semaphore semaforo){		
			this.servicioCliente = socket;	
			sem = semaforo;
		}		
		public void run(){
			try{	
				sem.acquire();
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
				

				System.out.println("número enviado: "+ (String)entradaServidor.readObject() );
				System.out.println("número enviado: "+ (String)entradaServidor.readObject() );
				System.out.println("número enviado: "+ (String)entradaServidor.readObject() );
				//sc.close();
				
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
					sem.release();
					recurso.numero--;
				}catch(Exception e){				
					System.err.println("Error: " + e.getMessage());				
				}			
			}		
		}
	}
}