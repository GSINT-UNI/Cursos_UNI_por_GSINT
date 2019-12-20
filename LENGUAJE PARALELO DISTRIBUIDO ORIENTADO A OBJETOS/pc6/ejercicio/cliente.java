package ejercicio;

import java.io.ObjectInputStream;
import java.util.Scanner;
import java.util.concurrent.*;
import java.io.ObjectOutputStream;
import java.net.Socket;
public class cliente {

	public static void main(String[] args) throws Exception{
		ObjectOutputStream salidaCliente = null;
		ObjectInputStream entradaCliente = null;
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
			new decimal(binario,salidaCliente);
			new octal(binario,salidaCliente);
			new hexadecimal(binario,salidaCliente);	
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
	static class decimal extends Thread{
		private String binario;
		private ObjectOutputStream salidaCliente = null;
		private ObjectInputStream entradaCliente = null;		
		private int res=0;
		private int cast=0;
		public decimal(String binario, ObjectOutputStream salidaCliente) {
			this.binario=binario;
			this.salidaCliente=salidaCliente;
		}
		public void run(){
			try{			
				//while(binario!=0) {
				//	res = (int)(res + (binario % 10) * Math.pow(2,cast));
				//	binario = binario/10;
				//	cast++;
				//}
				int decimal = Integer.parseInt(binario,2); 
				salidaCliente.writeObject(decimal);
			}
			catch(Exception e){			
				System.err.println("Error: " + e.getMessage());
			}
			finally{
				try{				
					if( entradaCliente != null ) entradaCliente.close();
					if( salidaCliente != null ) salidaCliente.close();					
				}catch(Exception e){				
					System.err.println("Error: " + e.getMessage());				
				}			
			}		
		}
	}
	static class octal extends Thread{
		private String binario;
		private ObjectOutputStream salidaCliente = null;
		private ObjectInputStream entradaCliente = null;		
		private int res=0;
		private int cast=0;
		public octal(String binario, ObjectOutputStream salidaCliente) {
			this.binario=binario;
			this.salidaCliente=salidaCliente;
		}
		public void run(){
			try{			
				int decimal = Integer.parseInt(binario,2);
				String octal = Integer.toOctalString(decimal);
				salidaCliente.writeObject(octal);
			}
			catch(Exception e){			
				System.err.println("Error: " + e.getMessage());
			}
			finally{
				try{				
					if( entradaCliente != null ) entradaCliente.close();
					if( salidaCliente != null ) salidaCliente.close();					
				}catch(Exception e){				
					System.err.println("Error: " + e.getMessage());				
				}			
			}		
		}
	}
	static class hexadecimal extends Thread{
		private String binario;
		private ObjectOutputStream salidaCliente = null;
		private ObjectInputStream entradaCliente = null;		
		private int res=0;
		private int cast=0;
		public hexadecimal(String binario, ObjectOutputStream salidaCliente) {
			this.binario=binario;
			this.salidaCliente=salidaCliente;
		}		
		public void run(){
			try{			
				int decimal = Integer.parseInt(binario,2);
				String hexadecimal = Integer.toHexString(decimal);
				salidaCliente.writeObject(hexadecimal);
			}
			catch(Exception e){			
				System.err.println("Error: " + e.getMessage());
			}
			finally{
				try{				
					if( entradaCliente != null ) entradaCliente.close();
					if( salidaCliente != null ) salidaCliente.close();					
				}catch(Exception e){				
					System.err.println("Error: " + e.getMessage());				
				}			
			}		
		}
	}
	
}