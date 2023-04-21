#pragma once
#include <chrono>
#include <functional>
#include <iostream>


// Pas dans la couverture de code, seulement pour moi pour m'amuser à tester la durée d'exécution.
void calculateDuration(std::function<void()> fonctionLambda) {
    auto start = std::chrono::high_resolution_clock::now();
    fonctionLambda();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Durée d'exécution : " << duration.count() << " microsecondes" << std::endl;
}