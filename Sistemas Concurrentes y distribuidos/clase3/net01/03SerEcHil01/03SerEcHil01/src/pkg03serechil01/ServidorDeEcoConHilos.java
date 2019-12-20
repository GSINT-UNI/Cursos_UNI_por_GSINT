
package pkg03serechil01;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServidorDeEcoConHilos {
    public static void main(String[] args) {
        try {
            int i = 1;
            ServerSocket s = new ServerSocket(8189);
            while (true) {                
                Socket entrante = s.accept();
                System.out.println("Engendrado " + i);
                Runnable r = new ManejadorDeConHilos(entrante , i);
                Thread t = new Thread(r);
                t.start();
                i++;                
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }
}
//telnet 127.0.0.1 8189