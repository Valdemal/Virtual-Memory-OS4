#include "HeapManager.h"

/*
Тестирование выделения памяти при разных объемах данных.
Объем данных растет по экспоненте. (при 8 гб - все)
*/

int main(){
    size_t cases_count = 15;
    size_t memory_size_step = 4;

    void** memory = (void**)HeapManager::allocate(sizeof(void*) * cases_count);

    size_t current_size = memory_size_step;
    for (size_t i = 0; i < cases_count; i++){
        memory[i] = (void*)HeapManager::allocate(sizeof(void*) * current_size);
        current_size *= memory_size_step;
    }

    for (size_t i = 0; i < cases_count; i++){
        HeapManager::free(memory[i]);
    }

    HeapManager::free(memory);
}