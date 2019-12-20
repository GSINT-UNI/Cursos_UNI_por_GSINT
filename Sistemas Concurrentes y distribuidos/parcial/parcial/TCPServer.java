import java.io.BufferedReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import parcial.TCPClient.OnMessageReceived;

public class TCPServer {
    private int count = 0;
    public static final int SERVERPORT = 12345;
    private OnMessageReceived msgListener = null;
    private boolean running = false;
    TCPServerThread[] client;
    PrintWriter out;
    BufferedReader in;
    ServerSocket ssocket;

    public TCPServer(OnMessageReceived msgltnr, int nclient) {
        msgListener = msgltnr;
        client = TCPServerThread[nclient];
    }

    public void broadcast(String msg) {
        for (int i = 0; i < count; i++) {
            client[i].sendMessage(msg);
        }
    }

    @Override
    public void run() {
        running = true;
        try {
            System.out.println("Connecting...");
            ssocket = new ServerSocket(SERVERPORT);

            while (running) {
                Socket clnt = ssocket.accept();
                client[count] = new TCPServerThread(clnt, this, count, client);
                count++;
                Thread t = new Thread(client[count]);
                t.start();
                System.out.println("Clients connected: " + count);

            }
        } catch (Exception e) {
            System.err.println("Error on TCPServer:");
            System.err.println(e);
        }
    }
    public OnMessageReceived getMessageListener() {
        return msgListener;
    }

}