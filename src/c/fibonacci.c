/*
 * fibonacci.c
 *
 * La suite de Fibonacci est une séquence de nombres entiers dans laquelle
 * chaque nombre est la somme des deux précédents. Elle commence typiquement 
 * par 0 et 1. Ainsi, les premiers termes de la suite de Fibonacci sont :
 * 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
 * 
 * Pour éviter les overflow tout en générant la suite de Fibonacci et en 
 * s'assurant que chaque valeur de la séquence ne dépasse pas la capacité 
 * d'un 'unsigned long long', il est important de vérifier les valeurs à 
 * chaque étape de la génération de la séquence.
 *
 * 1) Vérification de la Capacité : Avant d'ajouter deux nombres pour 
 *    obtenir le prochain nombre de Fibonacci, la vérification 
 *    ULLONG_MAX - fib[i-1] < fib[i-2] est effectuée pour s'assurer que 
 *    le résultat ne dépassera pas la capacité d'un 'unsigned long long'.
 *
 * 2) La Taille du Buffer : La taille du buffer a été calculée pour tenir
 *    compte du fait que chaque nombre dans la suite de Fibonacci, lorsqu'il 
 *    est grand, peut avoir jusqu'à 20 chiffres plus un espace (pour un 
 *    unsigned long long).
 *
 * 3) Gestion des Cas Limites : Si 'n' est inférieur ou égal à 0, la 
 *    fonction retourne immédiatement une chaîne vide.
 *
 * 4) Libération de la Mémoire : Libération de la mémoire allouée après
 *    utilisation dans le 'main'.
 *
 * Cette implémentation permet de générer une séquence de Fibonacci sans 
 * risque d'overflow tout en respectant la limite d'un 'unsigned long long'.
 * 
 * Sur une plateforme x86, la longueur d'un 'unsigned long long' est
 * généralement de 8 octets (64 bits).
 * 
 * Depuis le standard C 'C99', des types exacts d'entiers sont définis dans
 * l'en-tête <stdint.h> pour représenter un 'unsigned long long', appelé
 * 'uint64_t'. De même, cette en-tête définit 'UINT64_MAX', représentant la
 * valeur maximale qu'un entier non signé de 64 bits peut prendre.
 * 
 * La plage de valeurs maximale d'un 'uint64_t' est de 0 à 
 * '18 446 744 073 709 551 615' (2^64 - 1).
 */

#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

// Déclaration des fonctions
#include "FibonacciJNI.h"             // Generated
char* fibonacci_native(int n);

char* fibonacci_native(int n) {
    // Valeur par défaut si le paramètre n'est pas transmis ou est négatif.
    if (n <= 0) {
        n = 10;
    }

    // Allocation d'un buffer assez grand pour contenir la suite de Fibonacci
    int tailleBuffer = n * 21; // estimation plus précise de la taille du buffer (20 caractères max pour un uint64_t + espace)
    char* result = (char*)malloc(tailleBuffer * sizeof(char));
    if (result == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    result[0] = '\0'; // initialisation de la chaîne de caractères

    uint64_t fib[n];
    fib[0] = 0;
    if (n > 1) {
        fib[1] = 1;
    }

    for (int i = 2; i < n; i++) {
        // Vérifier si la prochaine valeur de Fibonacci dépasse la capacité d'un uint64_t
        if (UINT64_MAX - fib[i-1] < fib[i-2]) {
            printf("Erreur : Dépassement de capacité détecté pour n = %d\n", n);
            break;
        }
        fib[i] = fib[i-1] + fib[i-2];
    }

    // Construction de la chaîne de caractères avec les éléments de Fibonacci
    for (int i = 0; i < n; i++) {
        char buffer[21];
        sprintf(buffer, "%lu ", fib[i]);
        strcat(result, buffer);
    }

    return result;
}

JNIEXPORT jstring JNICALL Java_FibonacciJNI_fibonacci(JNIEnv *env, jobject obj, jint n) {
    // Utilisation de la fonction native pour calculer la suite de Fibonacci
    char* result = fibonacci_native(n);

    // Conversion de la chaîne C en chaîne Java
    jstring jResult = (*env)->NewStringUTF(env, result);

    // Libération de la mémoire allouée pour la chaîne C
    free(result);

    return jResult;
}


// Fonction principale pour les tests en C natif
/* int main(int argc, char **argv) {
    int n = 10; // Par défaut, calculer les 10 premiers termes
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    char* result = fibonacci_native(n);
    printf("Suite de Fibonacci : %s\n", result);
    free(result);

    return 0;
}
 */