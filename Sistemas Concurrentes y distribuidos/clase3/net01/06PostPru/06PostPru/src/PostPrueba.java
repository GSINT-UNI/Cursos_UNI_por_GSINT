 import java.awt.*;
 import java.awt.event.*;
 import java.io.*;
 import java.net.*;
 import java.util.*;
 import javax.swing.*;
 
 public class PostPrueba{
    public static void main(String[] args){
        EventQueue.invokeLater(new Runnable(){
            public void run(){
                JFrame frame = new PostTestFrame();
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
            }
        });
    }
 }