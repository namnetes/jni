/*
 * HelloJNI.h.
 * javac -h . HelloJNI.java
 * 
 * Pour exécuter le programme
 * java -Djava.library.path=. HelloJNI
 */

public class HelloJNI {  // Save as HelloJNI.java
   static {
      System.loadLibrary("DemoJNI");
   }

   // Declare an instance native method sayHello() which receives no parameter and returns void
   private native void sayHello();

   // Test Driver
   public static void main(String[] args) {      
      HelloJNI demo = new HelloJNI();
      demo.sayHello(); 
   }
}