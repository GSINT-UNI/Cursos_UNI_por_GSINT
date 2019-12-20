package javaapplication15;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author PCS4
 */
import java.util.concurrent.Semaphore;
class Monitor {
   int n;
   //Comienza con el semáforo no disponible para el consumidor
   static Semaphore semCon = new Semaphore(0);
   static Semaphore semProd = new Semaphore(1);
   void recoger() {
      try {
         semCon.acquire();
      } catch (InterruptedException e) {
         System.out.println("Error: " + e.getMessage());
      }
      System.out.println("Obtiene : " + n);
      semProd. release ();
   }
   void poner(int n) {
      try {
         semProd.acquire();
      } catch( InterruptedException e) {
         System.out.println("Error: " + e.getMessage()); 
      }
      this.n = n;
      System.out.println("Pone : " + n);
      semCon.release ();
   }
}
class Productor implements Runnable {
   Monitor q;
   Productor(Monitor q) {
      this.q = q;
      new Thread(this,"Productor").start();
   }
   public void run() {
      for(int i=0; i < 20; i++) q.poner(i);
   }
}

class Consumidor implements Runnable {
   Monitor q;
   Consumidor(Monitor q) {
      this.q = q;
   new Thread(this, "Consumidor").start();
   }   
   public void run(){
      for(int i=0; i < 20; i++) q.recoger();
   }
}

class ejemplo2 {
   public static void main(String args[]) {
      Monitor q = new Monitor();
      new Consumidor(q);
      new Productor(q);
   }
}

