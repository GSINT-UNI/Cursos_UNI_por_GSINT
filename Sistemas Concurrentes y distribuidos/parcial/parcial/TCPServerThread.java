import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

import parcial.TCPClient.OnMessageReceived;

public class TCPServerThread extends Thread {
    private Socket client;
    private int clientID;
    private TCPServer server;
    private PrintWriter out;
    private BufferedReader in;
    private OnMessageReceived msgListener;
    private String msg;
    TCPServerThread[] friend;
    private boolean running = false;

    public TCPServerThread(Socket clnt, TCPServer srvr, int id, TCPServerThread[] frnd) {
        client = clnt;
        server = srvr;
        clientID = id;
        friend = frnd;
    }

    @Override
    public void run() {
        running = true;

        try {
            try {
                out = new PrintWriter(
                    new BufferedWriter(
                        new OutputStreamWriter(client.getOutputStream())
                    ),
                    true
                );
                msgListener = server.getMessageListener();
                in = new BufferedReader(
                    new InputStreamReader(client.getInputStream())
                );

                while (running) {
                    msg = in.readLine();
                    
                    if (msg != null && msgListener != null) {
                        msgListener.messageReceived(msg);
                    }

                    msg = null;
                }

                
            } catch (Exception e) {
                System.err.println("Error on TCPServerThread:");
                System.err.println(e);
            } finally {
                client.close();
            }
        } catch (Exception e) {
            System.err.println("Error on TCPServerThread:");
            System.err.println(e);
        }
    }

    public void sendMessage(String msg) {
        if (out != null && !out.checkError()) {
            out.println(msg);
            out.flush();
        }
    }

    public void stopServer() {
        running = false;
    }

}