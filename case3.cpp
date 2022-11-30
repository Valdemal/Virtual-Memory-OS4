#include "HeapManager.h"

/*
Еще одно тестирование переиспользования чанков
Сначала создается большой чанк
Потом создается маленький чанк
Затем удаляется большой.
Затем создается средний, он должен занять место 3-го
Затем удаляется маленький.
Снова создается большой.

Чанки должны быть отсортированы в списке в порядке неубывания
*/

int main() {
    size_t little_size = 400, medium_size = 800, big_size = 1200;

    auto p_big = HeapManager::allocate(sizeof(char) * big_size);
    auto p_little = HeapManager::allocate(sizeof(char) * little_size);

    HeapManager::free(p_big);

    auto p_medium = HeapManager::allocate(sizeof(char) * medium_size);

    HeapManager::free(p_little);

    p_big = HeapManager::allocate(sizeof(char) * big_size);

    p_little = HeapManager::allocate(sizeof(char) * little_size);

    HeapManager::print_chunks_sizes();
}