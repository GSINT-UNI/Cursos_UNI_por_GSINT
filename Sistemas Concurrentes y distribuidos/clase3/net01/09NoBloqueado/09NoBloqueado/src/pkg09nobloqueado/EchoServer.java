/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg09nobloqueado;

import java.nio.*;
import java.nio.channels.*;
import java.net.*;
import java.util.*;
import java.io.IOException;

public class EchoServer {
  public static int DEFAULT_PORT = 7;
  
  public static void main(String[] args) {
  
    int port;
    try {
      port = Integer.parseInt(args[0]);
    }
    catch (Exception ex) {
      port = DEFAULT_PORT;   
    }
    System.out.println("Listening for connections on port " + port);

    
    ServerSocketChannel serverChannel;
    Selector selector;
    try {
      serverChannel = ServerSocketChannel.open();
      ServerSocket ss = serverChannel.socket();
      InetSocketAddress address = new InetSocketAddress(port);
      ss.bind(address);
      serverChannel.configureBlocking(false);
      selector = Selector.open();
      serverChannel.register(selector, SelectionKey.OP_ACCEPT);
    }
    catch (IOException ex) {
      ex.printStackTrace();
      return;   
    }
    
    while (true) {
      
      try {
        selector.select();
      }
      catch (IOException ex) {
        ex.printStackTrace();
        break;
      }
        
      Set readyKeys = selector.selectedKeys();
      Iterator iterator = readyKeys.iterator();
      while (iterator.hasNext()) {
        
        SelectionKey key = (SelectionKey) iterator.next();
        iterator.remove();
        try {
          if (key.isAcceptable()) {
            ServerSocketChannel server = (ServerSocketChannel ) key.channel();
            SocketChannel client = server.accept();
            System.out.println("Accepted connection from " + client);
            client.configureBlocking(false);
            SelectionKey clientKey = client.register(
              selector, SelectionKey.OP_WRITE | SelectionKey.OP_READ);
            ByteBuffer buffer = ByteBuffer.allocate(100);
            clientKey.attach(buffer);
          }
          if (key.isReadable()) {
            SocketChannel client = (SocketChannel) key.channel();
            ByteBuffer output = (ByteBuffer) key.attachment();
            client.read(output);
              System.out.println(" AA1:"+output.toString());
              System.out.println(" AA2:"+client.toString());
              System.out.println(" AA3:"+key.toString());
          }
          if (key.isWritable()) {
            SocketChannel client = (SocketChannel) key.channel();
            ByteBuffer output = (ByteBuffer) key.attachment();
            output.flip();
            client.write(output);
            output.compact();
              //System.out.println(" BB:"+output.toString());
          }
        }
        catch (IOException ex) {
          key.cancel();
          try {
            key.channel().close();
          }
          catch (IOException cex) {}
        }
        
      }

    }
  
  }

}