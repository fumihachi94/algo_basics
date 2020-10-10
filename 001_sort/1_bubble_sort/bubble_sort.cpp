#include "bubble_sort.h"

template<class T> 
int bubble_sort<T>::cal(){

    if(_v == nullptr){
        cerr << "Error: function bubble sort input is null." << endl;
        return 0;
    }

    T tmp;
    for(int i=0;i<_sz; i++){
        for(int j=0; j<_sz-i-1; j++){
            if(_v[j] < _v[j+1]) continue;
            tmp     = _v[j];
            _v[j]   = _v[j+1];
            _v[j+1] = tmp;
        }
    }

    return 1;
}

template int bubble_sort<short >::cal();
template int bubble_sort<int   >::cal();
template int bubble_sort<long  >::cal();
template int bubble_sort<float >::cal();
template int bubble_sort<double>::cal();
