
package pkg03serechil01;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class ManejadorDeConHilos implements Runnable{
    private Socket entrante;
    private int contador;
    public ManejadorDeConHilos(Socket i,int c){
        entrante = i; contador = c;                
    }
    public void run(){
        try {
            try {
                InputStream secuenciaDeEntrada = entrante.getInputStream();
                OutputStream secuenciaDeSalida = entrante.getOutputStream();

                Scanner in = new Scanner(secuenciaDeEntrada);
                PrintWriter out = new PrintWriter(secuenciaDeSalida,true);

                out.println("¡Hola! Escriba ADIOS para salir");

                boolean terminado = false;
                while(!terminado && in.hasNextLine()){
                    String linea = in.nextLine();
                    out.println("Eco"+linea);
                    System.out.println("Eco de:"+contador+" dice:"+linea);
                    if(linea.trim().equals("ADIOS")){
                        terminado = true;
                    }
                }                
            } finally {
                entrante.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
