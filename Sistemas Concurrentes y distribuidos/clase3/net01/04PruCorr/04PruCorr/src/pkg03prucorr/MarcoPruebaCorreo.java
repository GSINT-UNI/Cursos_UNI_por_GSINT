/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg03prucorr;

import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class MarcoPruebaCorreo extends JFrame{
    private Scanner in;
    private PrintWriter out;
    private JTextField de;
    private JTextField para;
    private JTextField servidorSMPT;
    private JTextArea mensaje;
    private JTextArea comm;
    private JLabel L1;
    private JLabel L2;
    private JLabel L3;
    
    
    public static final int ANCHURA_PREDETERMINADA = 300;
    public static final int ALTURA_PREDETERMINADA = 300;

    public MarcoPruebaCorreo() {
        setSize(ANCHURA_PREDETERMINADA,ALTURA_PREDETERMINADA);
        setTitle("Prueba Correo");
        setLayout(null);
        
        L1 = new JLabel("De:");
        add(L1);
        L1.setBounds(20,20,40,25);
        de = new JTextField(20);
        add(de).setBounds(80, 20, 60, 25);
    
        
        L2 = new JLabel("Para:");
        add(L2);
        L2.setBounds(20,50,40,25);
        para = new JTextField(20);
        add(para).setBounds(80, 50, 60, 25);
        
        L3 = new JLabel("SMPT Servdor:");
        add(L3);
        L3.setBounds(20,80,100,25);
        servidorSMPT = new JTextField(20);
        add(servidorSMPT).setBounds(120, 80, 60, 25);
       
        mensaje =new JTextArea();
        add(new JScrollPane(mensaje)).setBounds(20,110,160,50); 

        comm =new JTextArea();
        add(new JScrollPane(comm)).setBounds(20,170,160,50); 
        
        JButton botonDeEnvio = new JButton("Enviar");
        add(botonDeEnvio).setBounds(20, 240, 70, 25);
        botonDeEnvio.addActionListener(
            new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    new Thread( 
                        new Runnable(){
                            public void run(){
                                comm.setText("");
                                sendMail();
                            }
                        }).start(); 
                }
            }
        );                        
    }
    public void sendMail(){
        try{
            Socket s = new Socket(servidorSMPT.getText(),25);
            
            InputStream secuenciaDeEntrada =s.getInputStream();
            OutputStream secuenciaDeSalida =s.getOutputStream();
            
            in = new Scanner(secuenciaDeEntrada);
            out = new PrintWriter(secuenciaDeSalida,true);
            
            String nombreComputadora = InetAddress.getLocalHost().getHostName();
            
            recibir();
            enviar("Helo"+nombreComputadora);
            recibir();
            
            enviar("MAIL FROM: <"+ de.getText() +">");
            recibir();
            
            enviar("RCPT TO: <"+ para.getText() +">");
            recibir();
            
            enviar("DATA");
            recibir();
            
            enviar(".");
            recibir();
            s.close();
            
        }catch(IOException e){
            comm.append("Error: "+e);
        }
    
    }
    public void enviar(String s){
        comm.append(s);
        comm.append("\n");
        out.print(s.replaceAll("\n","\r\n"));
        out.print("\r\r");
        out.flush();
    }
    
    public void recibir() throws IOException{
        String line = in.nextLine();
        comm.append(line);
        comm.append("\n");
    }
    
}
