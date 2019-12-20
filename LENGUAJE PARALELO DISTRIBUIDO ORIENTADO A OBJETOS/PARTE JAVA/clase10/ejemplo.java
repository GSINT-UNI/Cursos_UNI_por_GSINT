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

import java.util.concurrent.*;
class ejemplo {
   public static void main(String args[]) {
      Semaphore sem = new Semaphore(1);
      new HiloIncrementa(sem, "A");
      new HiloDecrementa(sem, "B");
   }
}
//Un recurso compartido
class Compartido {
   static int contador = 0;
}

//Un hilo de ejecuciÃ³n que incrementa contador.
class HiloIncrementa implements Runnable {
   String name;
   Semaphore sem;
   HiloIncrementa(Semaphore s, String n) {
      sem = s;
      name = n;
      new Thread (this).start();
   }
   public void run() {
      System.out.println ("Comenzando " + name);
      try {
         // Primero, obtiene el permiso
         System.out.println(name + " estÃ¡ esperando por permiso.");
         sem.acquire();
         System.out.println(name + " obtiene permiso.");
         // Ahora, accede al recurso compartido
         for (int i=0; i < 5; i++) {
            Compartido.contador++;
            System.out.println(name + ": " + Compartido.contador);
             // Ahora, permite un cambio de contexto â€“ si es posible.
            Thread.sleep(50);
        }
      } catch (InterruptedException e) {
         System.out.println("Error: " + e.getMessage());
        }
      // Libera el permiso
      System.out.println (name + " libera el permiso.");
      sem.release();
   }
}

// Un hilo de ejecuciÃ³n que decrementa contador.
class HiloDecrementa implements Runnable {
   String name;
   Semaphore sem;
   HiloDecrementa (Semaphore s, String n) {
      sem = s;
      name = n;
      new Thread(this).start();
   }
   public void run () {
      System.out.println("Comenzando " + name);
      try {
         // Primero obtiene el permiso.
         System.out.println(name + " estÃ¡ esperando permiso.");
         sem.acquire ();
         System.out.println(name + " obtiene permiso.");
         // Ahora, accede al recurso compartido
         for (int i=0; i < 5; i++) {
            Compartido.contador--;
            System.out.println (name + ": " + Compartido.contador);
            //Ahora, permite un cambio de contexto â€“ si es posible
            Thread.sleep(50);
         }
      } catch (InterruptedException e) {
         System.out.println("Error: " + e.getMessage());
         }
      //Libera el permiso
      System.out.println(name + " libera el permiso.");
      sem.release();
   }
}