
package pkg03prusoc;

import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

public class PruebaSocket {    
    public static void main(String[] args) {
        try {
            //Socket s = new Socket("time-A.timefreq.bldrdoc.gov",13);
            Socket s = new Socket("127.0.0.1",8189);
            try {
                InputStream secuenciaDeEntrada = s.getInputStream();
                Scanner in = new Scanner(secuenciaDeEntrada);
                while (in.hasNextLine()) {
                    String line = in.nextLine();
                    System.out.println(line);                    
                }
            } finally{
                s.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }        
    }
}
