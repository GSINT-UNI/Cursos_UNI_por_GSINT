/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package javaapplication15;

/**
 *
 * @author PCS4
 */
//Un ejemplo de CountDownLatch

import java.util.concurrent.CountDownLatch;

class ejemplo3 {
   public static void main(String args[]) {
      CountDownLatch cdl = new CountDownLatch(5);
      System.out.println("Comenzando");
      new MiHilo(cdl);
      try {
         cdl.await();
      } catch (InterruptedException e) {
         System.out.println("Error: " + e.getMessage());
      }
   System.out.println("Hecho");
   }
}

class MiHilo implements Runnable {
   CountDownLatch latch;
   MiHilo(CountDownLatch c) {
      latch = c;
      new Thread(this).start();
   }
   public void run() {
      for(int i = 0 ; i<15; i++) {
         System.out.println (i);
         latch.countDown(); // decrementa el contador
         
      }
   }
}
