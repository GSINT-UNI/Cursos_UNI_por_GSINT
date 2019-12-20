
import java.util.Scanner;
 
public class Final {

	public static void main(String[] args) {			
		System.out.println("Escriba un entero");
		Scanner scan = new Scanner(System.in);
	    int n = scan.nextInt();
	    new paralelsum(n);
	    	    
	    scan.close();
	}

}
class paralelsum implements Runnable{
	int n;
	Thread R;
	public paralelsum(int n) {
		this.n = n;
		R = new Thread(this);
		R.start();
	}
	public void run() {
		
		new suma2(n);
	    new suma3(n);
	    new suma4(n);	
	    //System.out.println("el valor final es :  "+SUMATOTAL.S);	    
	}
	
}
class SUMATOTAL{
	static int S=0;
}

class sumahilo implements Runnable{
	int n;
	int i;
	int h;
	Thread t;
	public sumahilo(int n, int i, int h) {
		this.n = n;
		this.i = i;
		this.h = h;
		t = new Thread(this);
		t.start();
	}
	public void run() {
		for(int k=h;k<=n;k=k+i){
			SUMATOTAL.S =(int) (SUMATOTAL.S + Math.pow(k,i));
			System.out.println("estoy en la suma "+ i +" y en su hilo "+ h+ ", k vale : "+k+" la suma hasta ahora es: "+ SUMATOTAL.S);
		}
	}
}

class suma2 implements Runnable{
	int n;	
	public suma2(int n) {
		this.n = n;
		new Thread(this).start();
	}
	public void run(){
		sumahilo s0 = new sumahilo(n,2,1);
		sumahilo s1 = new sumahilo(n,2,2);		
	}	
}
class suma3 {
	int n;
	public suma3(int n) {
		this.n = n;
		sumahilo s1 = new sumahilo(n,3,1);
		sumahilo s2 = new sumahilo(n,3,2);
		sumahilo s3 = new sumahilo(n,3,3);		
	}
}
class suma4 {
	int n;
	public suma4(int n) {
		this.n = n;	
		sumahilo s1 = new sumahilo(n,4,1);
		sumahilo s2 = new sumahilo(n,4,2);
		sumahilo s3 = new sumahilo(n,4,3);
		sumahilo s4 = new sumahilo(n,4,4);
		
	}
}
