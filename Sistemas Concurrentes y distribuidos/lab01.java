/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pc1;
import java.util.Random;
import static java.lang.Thread.sleep;

/**
 *
 * @author PCS4
 */
public class tarea01 {
	int nnn=1000;
    trabajo[] ht = new trabajo[nnn];
    Thread[] t = new Thread[nnn];
    boolean flag = false;
    public void inicio(){
        int nh = 3;
        for (int i=0; i< ht.length; i++){
            ht[i] = new trabajo();
            t[i] = new Thread(ht[i]);
            t[i].start();
        }           
        
    }
    public class trabajo extends Thread{
        int a = 30;
        int num = 1;
		public void run(){
            try{                
                while(num!=666 && flag==false){
                    sleep(20);
                    int num = (int) (Math.random() * 1000) + 1;
                    if(num==666 && flag == false) {                       
                       System.out.println(this.getName()+ " GANADOR "); 
                       flag = true;
                       for(Thread j : t) {
                    	   j.stop();
                   	   }
                    }
                    
                }                          
                
            } catch(InterruptedException ex) { System.out.println(":"+ex);}
        }
    }
    public static void main(String[] args){
        new tarea01().inicio();
    }
}

