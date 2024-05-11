// Save as "HelloJNI.c"
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "HelloJNI.h"   // Generated

// Implementation of the native method sayHello()
JNIEXPORT void JNICALL Java_HelloJNI_sayHello(JNIEnv *env, jobject thisObj) {
   printf("Hello World!\n");
   return;
}

/* gcc -I"%JAVA_JDK_HOME%\include -I"%JAVA_JDK_HOME%\include\win32" -I"%JAVA_HOME%\include\win32" -shared -o hello.dll HelloJNI.c  */
/*
 * Compilation sous Linux
 * gcc \
 * -Wall \
 * -fPIC \
 * -shared \
 * -o libHelloJNI.so \
 * -I"../java" \
 * -I"$JAVA_HOME/include" \
 * -I"$JAVA_HOME/include/linux" \ 
 * HelloJNI.c
 * 
 * gcc -Wall -fPIC -shared -o libHelloJNI.so -I"../java" -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" HelloJNI.c
 * 
 * -Wall : Active les avertissements du compilateur pour les problèmes potentiels dans le code.
 * -fPIC : Crée un code indépendant de la position (PIC), adapté au lien dynamique.
 * -shared : Crée une bibliothèque partagée .so
 * -o libHelloJNI.so : Nom de la bibliothèque partagée
 * -I"$JAVA_HOME/include" & -I"$JAVA_HOME/include/linux" : Emplacement des en-têtes
 * HelloJNI.c : fichier source à compiler
 * 
 * ldd: Utilisez la commande ldd suivie du chemin vers votre fichier .so pour afficher les bibliothèques partagées dont dépend votre fichier .so.
 * nm: Cette commande vous permet de lister les symboles exportés par votre fichier .so. Vous pouvez l'utiliser comme ceci : nm -D votre_fichier.so.
 * objdump: Avec la commande objdump, vous pouvez afficher les informations détaillées du fichier .so, y compris les sections, les symboles, etc. Par exemple, objdump -x votre_fichier.so.
 * 
*/
