#include "bubble_sort.h"

using namespace std;

template<class T>
T bubble_sort<T>::cal(){
    T a;
    *a = 1;

    T tmp;

    unsigned int sz = sizeof(_v)/sizeof(*_v);

    // for(int i=0;i<sz; i++){
    //     for(int j=1; j<sz-i; j++){
    //         if(_v[i] < _v[j]) continue;
    //         tmp = _v[i];
    //         _v[i] = _v[j];
    //     }
    // }

    cout << "sizeof(_v)  : " << sizeof(_v)  << endl; 
    cout << "sizeof(*_v) : " << sizeof(*_v) << endl; 
    cout << "_v[2] : " << _v[2] << endl; 
    cout << "Input size : " << sz << endl; 

    return a;
}

template short*  bubble_sort<short* >::cal();
template int*    bubble_sort<int*   >::cal();
template long*   bubble_sort<long*  >::cal();
template float*  bubble_sort<float* >::cal();
template double* bubble_sort<double*>::cal();
