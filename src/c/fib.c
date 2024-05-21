#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

// main
int main() {

    void *handle = dlopen("./libDemoJNI.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Erreur: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    //vider les erreurs existantes
    dlerror();

    // Déclarer un pointeur de fonction pour la fonction fibonacci
    char* (*fibonacci_native)(int);

    // obtenir l'adresse de la focntion "fibonacci_native"
    *(void **) (&fibonacci_native) = dlsym(handle, "fibonacci_native");

    // vérifier s'il y a eu une erreur lors de la récupération de l'adresse
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Erreur: %s\n", error);
        dlclose(handle);
        exit(EXIT_FAILURE);
    }

    // appeler la fonction fibonacci_native
    int n = 10;
    char *result = fibonacci_native(n);

    printf("le %dème nombre de Fibonacci est: %s\n", n, result);

    // fermer la bibliothèque partagée
    dlclose(handle);
    return 0;
}