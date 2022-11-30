#include "HeapManager.h"
#include <iostream>


/*
Реализовать менеджер кучи по приведенному в теоретической части
описанию. Обеспечить к нему интерфейс в виде двух функции̮
аналогичных malloc и free. Проверить работоспособность работы
менеджера кучи последовательно выделяя участки памяти
различного размера от нескольких десятков баи̮т до нескольких
гигабайт.
*/

void test(){
    int *arr = (int*)HeapManager::allocate(sizeof(int) * 5);

    for (size_t i = 0; i < 5; i++){
        arr[i] = rand();
    }

    for (size_t i = 0; i < 5; i++){
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int main() {
    int *arr1 = (int*)HeapManager::allocate(sizeof(int) * 5);

    for (size_t i = 0; i < 5; i++){
        arr1[i] = rand();
    }

    for (size_t i = 0; i < 5; i++){
        std::cout << arr1[i] << ' ';
    }
    std::cout << std::endl;

    int *arr2 = (int*)HeapManager::allocate(sizeof(int) * 5);

    for (size_t i = 0; i < 5; i++){
        arr2[i] = rand();
    }

    for (size_t i = 0; i < 5; i++){
        std::cout << arr2[i] << ' ';
    }

    HeapManager::free(arr2);

    int *arr3 = (int*)HeapManager::allocate(sizeof(int) * 5);

    for (size_t i = 0; i < 5; i++){
        arr3[i] = rand();
    }

    for (size_t i = 0; i < 5; i++){
        std::cout << arr3[i] << ' ';
    }
}
