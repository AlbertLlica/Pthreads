#include <iostream>
#include <pthread.h>
#include <chrono>

void* emptyThread(void* args) {
    return nullptr;
}

int main() {
    int numThreads;
    std::cout << "Ingrese el numero de Hilos: ";
    std::cin >> numThreads;

    pthread_t threads[numThreads];
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        pthread_create(&threads[i], nullptr, emptyThread, nullptr);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }
//CORREGIR TIEMPO PROMEDIO: OBTENER EL TIEMPO DE TODOS Y RECIEN DIVI
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double averageTime = duration.count() / numThreads;

    std::cout << "Tiempo promedio para crear y terminar un hilo: " << averageTime << " segundos\n";

    return 0;
}
