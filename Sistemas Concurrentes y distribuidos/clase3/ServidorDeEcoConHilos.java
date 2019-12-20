/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package exam0301;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
public class ServidorDeEcoConHilos implements Runnable{
    private int nrocli = 5;
    private ManejadorDeConHilos[] cli = new ManejadorDeConHilos[nrocli];        
    private String[][] tablero = new String[5][8];
    
    public ServidorDeEcoConHilos() {                
        for(int i=0; i<5; i++){
            for(int j=0; j<8; j++){
                tablero[i][j]=".";
            }
        }
    }
    
    public void run(){
        try {
            int i = 1;
            ServerSocket s = new ServerSocket(8189);
            while (true) {                
                Socket entrante = s.accept();
                System.out.println("Engendrado " + i);
                //Runnable 
                cli[i] = new ManejadorDeConHilos(entrante , i,tablero);
                Thread t = new Thread(cli[i]);
                t.start();
                i++;                
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }
     
    //public class Servidor(){
    
    
    //}

    private void ManejadorDeConHilos(Socket entrante, int i) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
            
}
//telnet 127.0.0.1 8189