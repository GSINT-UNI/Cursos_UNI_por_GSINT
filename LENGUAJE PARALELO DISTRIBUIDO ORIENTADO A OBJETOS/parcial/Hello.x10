/**
 * The canonical "Hello, World" demo class expressed in X10
 */
import x10.lang.System;
public class Hello {

    /**
     * The main method for the Hello class
     */
    public static def main(Rail[String]) {   
    	val n:Rail[Long] = [1,0,0];  
    	
    	
    	while( n(1)<=20 ){
    		 finish{
    			async{    				
    				if(n(2) == 0 ){
    					n(1)++;
    					Console.OUT.println("Produce: "+n(1));
    					n(2) = 1;
    					System.sleep(600);
    				}
    			}
    			
    			async{
    				if(n(2) == 1){
    					Console.OUT.println("Consume: "+n(1));
    					n(2) = 0;
    					System.sleep(600);
    				}
    			}
    		}
    	}
        
    }

}
