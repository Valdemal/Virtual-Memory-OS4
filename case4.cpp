#include "HeapManager.h"

/*

Чанки должны быть отсортированы в списке в порядке неубывания
*/

int main() {
    HeapManager::allocate(1200);
    HeapManager::allocate(200);
    HeapManager::allocate(400);
    HeapManager::allocate(800);
    HeapManager::print_chunks_sizes();
}