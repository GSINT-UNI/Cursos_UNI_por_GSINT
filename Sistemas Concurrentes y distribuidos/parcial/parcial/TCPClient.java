package parcial;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;

import redesOk.TCPServer50.OnMessageReceived;

public class TCPClient {
    private String msg;
    public String server_ip;
    public static final int SERVERPORT = 12345;
    private OnMessageReceived msgListener = null;
    private boolean running = false; //????
    protected PrintWriter out;
    protected BufferedReader in;
    
    public TCPClient(String ip, OnMessageReceived lstnr) {
        server_ip = ip;
        msgListener = lstnr;
    }

    public void sendImage(int img[][]) {
        
    }
    
    public void sendMessage(String msg) {
        if (out != null && !out.checkError()) {
            out.println(msg);
            out.flush();
        }
    }
    
    public void stopClient() {
        running = false;
    }
    
    @Override
    public void run(){
        running = true;
        
        try {
            InetAddress serverAddr = InetAddress.getByName(server_ip);
            System.out.println("Connecting to " + server_ip);
            Socket s = new Socket(serverAddr, SERVERPORT);
            
            try {
                out = new PrintWriter(
                    new BufferedWriter(new OutputStreamWriter(s.getOutputStream())),
                    true
                );
                System.out.println(("Done"));
                in = new BufferedReader(new InputStreamReader(s.getInputStream()));

                while (running) {
                    msg = in.readLine();
                    
                    if (msg != null && msgListener != null) {
                        msgListener.messageReceived(msg);
                    }
                    msg = null;
                }
            } catch (Exception e) {
                System.err.println("Error on TCPClient:");
                System.err.println(e);
            }
            finally {
                s.close();
            }
        } catch (Exception e) {
            System.err.println("Error on TCPClient:");
            System.err.println(e);
        }
    }

    public interface OnMessageReceived {
        public void messageReceived(String msg);
    }
}