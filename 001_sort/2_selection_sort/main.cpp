/************************************
  2. Selection Sort
  @fumihachi
  email: fumiya.sato.rop@gmail.com 
************************************/

#include <iostream>

using namespace std;

template<typename T> 
void selectionSort(T v[], size_t size){
    for (int i=0; i<size-1; i++){
        T tmp = v[i];
        int    n   = i;
        for (int j=i; j<size; j++) if (v[j] < v[n]) n = j;
        v[i] = v[n];
        v[n] = tmp;
    }
}

template<typename T> 
void printArray(T v[], int size, string msg = ""){
    cout << msg;
    for(int i=0;i<size; i++) cout << v[i] << ", ";
    cout << endl;
}

int main(void){
    cout << "== Selection Sort Algorithm ==" << endl;
    int v[] = {10, 45, 23, 45, 65, 20, 4, 1};
    size_t sz = sizeof(v)/sizeof(*v);
    printArray(v, sz, "Input data: ");
    // Execution of selection sort
    selectionSort(v, sz);
    printArray(v, sz, "Sorted data: ");
    return 0;
}
