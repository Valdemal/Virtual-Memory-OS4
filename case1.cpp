#include "HeapManager.h"
#include <iostream>

using namespace std;

void fill_arr(int* a, size_t len){
    for(size_t i = 0; i < len; i++){
        a[i] = rand();
    }
}

void print_arr(int *a, size_t len) {
    for(size_t i = 0; i < len; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
}


/*
Тестирование переиспользования чанков
В этом кейсе после удаления 2-го массива, при создании 3-го память должна повторно переиспользоваться
 */
int main() {
    int **arrs = (int**)HeapManager::allocate(sizeof(int*) * 3);

    arrs[0] = (int*)HeapManager::allocate(sizeof(int) * 5);
    fill_arr(arrs[0], 5);
    print_arr(arrs[0], 5);

    arrs[1] = (int*)HeapManager::allocate(sizeof(int) * 5);
    fill_arr(arrs[1], 5);
    print_arr(arrs[1], 5);
    HeapManager::free(arrs[1]);

    arrs[2] = (int*)HeapManager::allocate(sizeof(int) * 5);
    fill_arr(arrs[2], 5);
    print_arr(arrs[2], 5);

    HeapManager::free(arrs[0]);
    HeapManager::free(arrs[2]);
    HeapManager::free(arrs);
}