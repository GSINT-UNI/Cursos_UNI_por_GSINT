import java.io.ObjectInputStream;
import java.util.concurrent.*;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class Cliente2 {

	public static void main(String[] args) throws Exception{
		
		ObjectInputStream entradaCliente = null;
		ObjectOutputStream salidaCliente = null;
		Socket cliente = null;
		try{
			
			// Instancio el socket con la IP del Servidor y el PORT
			// del servidor. Con ipconfig averigua la dirección IP
			// y nombtre de tu PC o si no usa 127.0.0.1 que
			//representa la IP del equipo local (localhost)
			cliente = new Socket("localhost",5432);
			//Entrada y salida			
			salidaCliente = new ObjectOutputStream(cliente.getOutputStream());
			entradaCliente = new ObjectInputStream(cliente.getInputStream());
			//Recibo el binario 			
			String binario = (String) entradaCliente.readObject();
			//cambios en paralelo
			System.out.println(cliente);				
			System.out.println(salidaCliente);
			Semaphore sem = new Semaphore(1);
			hilo h1 = new hilo("decimal",cliente,salidaCliente,binario,10,sem);
			hilo h2 = new hilo("octal",cliente,salidaCliente,binario,8,sem);
			hilo h3 = new hilo("hexadecimal",cliente,salidaCliente,binario,16,sem);
			h1.h.join();
			h2.h.join();
			h3.h.join();			
		}
		catch(Exception e) {
			System.err.println("Error: " + e.getMessage());	
		}
		finally{	
			if( entradaCliente != null ) entradaCliente.close();
			if( salidaCliente != null ) salidaCliente.close();
			if( cliente != null ) cliente.close();	
		}
			
	}
	
	static class hilo implements Runnable{
		
		Socket cliente = null;
		String binario;
		int n;
		Semaphore sem;
		ObjectOutputStream salidaCliente;
		String nom;
		Thread h;
		public hilo(String nomhilo,Socket cliente,ObjectOutputStream salida, String binario,int n, Semaphore sem){		
			this.binario = binario;	
			this.n = n;			
			this.cliente = cliente;
			this.sem = sem;
			salidaCliente = salida;
			nom = nomhilo;
			h = new Thread(this,nom);
			h.start();
		}
		public void run() {	
			if(this.n == 10) {
				try{	
					System.out.println(cliente);
					int decimal = Integer.parseInt(binario,2);					
					System.out.println(salidaCliente);
					sem.acquire();
					salidaCliente.writeObject(Integer.toString(decimal));
					sem.release();
				}
				catch(Exception e){			
					System.err.println("Error: " + e.getMessage());
				}
				
			}
			if(this.n == 8) {				
				try{	
					int decimal = Integer.parseInt(binario,2);
					String octal = Integer.toOctalString(decimal);
					sem.acquire();
					salidaCliente.writeObject(octal);
					sem.release();
				}
				catch(Exception e){			
					System.err.println("Error: " + e.getMessage());
				}
				
			}
			if(this.n == 16) {
				try{		
					int decimal = Integer.parseInt(binario,2);
					String hexadecimal = Integer.toHexString(decimal);
					sem.acquire();
					salidaCliente.writeObject(hexadecimal);
					sem.release();
				}
				catch(Exception e){			
					System.err.println("Error: " + e.getMessage());
				}
				
			}
						
		}
	}	
}