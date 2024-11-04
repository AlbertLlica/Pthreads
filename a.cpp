#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

long long totalTosses;
long long circleCount = 0;
int numThreads;
pthread_mutex_t mutex;

void* monteCarlo(void* args) {
    long long localCount = 0;
    unsigned int seed = time(nullptr);

    for (long long i = 0; i < totalTosses / numThreads; ++i) {
        double x = (double(rand_r(&seed)) / RAND_MAX) * 2.0 - 1.0;
        double y = (double(rand_r(&seed)) / RAND_MAX) * 2.0 - 1.0;
        if (x * x + y * y <= 1) localCount++;
    }

    pthread_mutex_lock(&mutex);
    circleCount += localCount;
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main() {
    std::cout << "Ingresa el numero Total de Lanzamientos: ";
    std::cin >> totalTosses;

    std::cout << "Ingresa el numero de Hilos: ";
    std::cin >> numThreads;

    pthread_t threads[numThreads];
    pthread_mutex_init(&mutex, nullptr);

    for (int i = 0; i < numThreads; ++i) {
        pthread_create(&threads[i], nullptr, monteCarlo, nullptr);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);

    double piEstimate = 4 * double(circleCount) / double(totalTosses);
    std::cout << "Estimated Pi = " << piEstimate << std::endl;

    return 0;
}
