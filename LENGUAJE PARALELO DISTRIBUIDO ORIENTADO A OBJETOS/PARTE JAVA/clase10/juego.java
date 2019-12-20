/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package javaapplication16;

/**
 *
 * @author PCS4
 */
import java.util.concurrent.*;

class cajas{
   static int caja1 = 0;
   static int caja2 = 0;
}

class Equipo1 {
   Semaphore sem;
   Equipo1(Semaphore s){
       s = sem;
   }   
   JugadorA jugadorA = new JugadorA(100,sem);
   JugadorB jugadorB = new JugadorB(200,sem);
   
}

class Equipo2 {   
   Semaphore sem;
   Equipo2(Semaphore s){
       s = sem;
   }  
   JugadorC jugadorC = new JugadorC(1000,sem);
   JugadorD jugadorD = new JugadorD(500,sem);
}

class JugadorA implements Runnable {
   int retraso;  
   Semaphore sem;
   JugadorA(int retraso,Semaphore s){
      retraso = this.retraso; 
      s = sem;
      new Thread(this).start();
   }
   public void run(){
    try{
       while(cajas.caja2 < 1000 & cajas.caja1 < 1000){
         sem.acquire();
         cajas.caja1++;
         System.out.println("jugadorA : " + cajas.caja1);         
         Thread.sleep(10);
       }
    }
    catch(InterruptedException e){
       System.out.println("Error: " + e.getMessage());
    }
    sem.release();    
   }
}
class JugadorB implements Runnable {
   int retraso;
   Semaphore sem;
   JugadorB(int retraso,Semaphore s){
      retraso = this.retraso;
      s = sem;
      new Thread(this).start();     
   }
   public void run(){
    try{
       while(cajas.caja2 < 1000 & cajas.caja1 < 1000){
         sem.acquire();
         cajas.caja1++;
         System.out.println("jugadorB : " + cajas.caja1);         
         Thread.sleep(10);
       }
    }
    catch(InterruptedException e){
       System.out.println("Error: " + e.getMessage());
    }
    sem.release();    
   }
}
class JugadorC implements Runnable {
   int retraso; 
   Semaphore sem;
   JugadorC(int retraso,Semaphore s){
      retraso = this.retraso;
      s = sem;
      new Thread(this).start();
   }
   public void run(){
    try{
       while(cajas.caja2 < 1000 & cajas.caja1 < 1000){
         sem.acquire();
         cajas.caja1++;
         System.out.println("jugadorA : " + cajas.caja1);         
         Thread.sleep(10);
       }
    }
    catch(InterruptedException e){
       System.out.println("Error: " + e.getMessage());
    }
    sem.release();    
   }
}
class JugadorD implements Runnable {
   int retraso;
   Semaphore sem;
   JugadorD(int retraso,Semaphore s){
      retraso = this.retraso;
      s = sem;
      new Thread(this).start();
   }
   public void run(){
    try{
       while(cajas.caja2 < 1000 & cajas.caja1 < 1000){
         sem.acquire();
         cajas.caja1++;
         System.out.println("jugadorA : " + cajas.caja1);         
         Thread.sleep(10);
       }
    }
    catch(InterruptedException e){
       System.out.println("Error: " + e.getMessage());
    }
    sem.release();    
   }
}
public class juego {
    public static void main(String args[]) {
      Semaphore sem1 = new Semaphore(1);
      Semaphore sem2 = new Semaphore(1);
      new Equipo1(sem1);
      new Equipo2(sem2);
   }
}
