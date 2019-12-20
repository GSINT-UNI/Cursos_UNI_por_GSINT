/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package newpackage;

/**
 *
 * @author PCS4
 */
//Ejemplo de CyclicBarrier .
import java.util.concurrent.*;
class ejemplo4 {
   public static void main(String args[]) {
      CyclicBarrier cb = new CyclicBarrier(3, new BarAccion());
      System.out.println("Comenzando");
      new MiHilo(cb, "A");
      new MiHilo(cb, "B");
      new MiHilo(cb, "C");
   }
}

//Un hilo de ejecución que utiliza un CyclicBarrier
class MiHilo implements Runnable {
   CyclicBarrier cbar;
   String nombre;
   MiHilo (CyclicBarrier c, String n) {
      cbar = c;
      nombre = n;
      new Thread(this).start();
   }
   public void run() {
      System.out.println(nombre);
      try {
         cbar .await();
      } catch (BrokenBarrierException e) {
         System.out.println("Error: " + e.getMessage());
      } catch (InterruptedException e) {
         System.out.println("Error: " + e.getMessage());
      }
   }
}
// Un objeto de esta clase es llamada cuando el CyclicBarrier termina.
class BarAccion implements Runnable {
   public void run() {
      System.out.println("Límite Alcanzado.");
   }
}