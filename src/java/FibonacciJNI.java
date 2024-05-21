/*
 * FibonacciJNI.h.
 * javac -h . FibonacciJNI.java
 * 
 * Pour exécuter le programme
 * java -Djava.library.path=. FibonacciJNI
 */

 public class FibonacciJNI {  // Save as HelloJNI.java
    static {
       System.loadLibrary("DemoJNI");
    }
 
    // Declare an instance native method fibonacci() which receives one parameter and returns a string
    private native String fibonacci(int n);
 
    // Test Driver
    public static void main(String[] args) {
      int n = -1;

      if (args.length > 0) {
         n = Integer.parseInt(args[0]);
      } 

      FibonacciJNI demo = new FibonacciJNI();
      String result = demo.fibonacci(n);
      System.out.println("Suite de Fibonacci jusqu'à n = " + n + " : " + result);
    }
 }