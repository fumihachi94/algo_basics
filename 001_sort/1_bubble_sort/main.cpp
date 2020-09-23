#include <iostream>
#include "bubble_sort.h"

#define mytype int

using namespace std;

template <class T>
int bubble(T* _v, unsigned int sz){

    if(_v == nullptr){
        cout << "null: function bubble sort input is null." << endl;
        return 0;
    }

    int tmp;
    for(int i=0;i<sz; i++){
        for(int j=0; j<sz-i-1; j++){
            if(_v[j] < _v[j+1]) continue;
            tmp     = _v[j];
            _v[j]   = _v[j+1];
            _v[j+1] = tmp;
        }
    }

    return 1;
}

int main(void){
    mytype v[] = {10, 45, 23, 45, 65, 20, 4};

    int sz = sizeof(v)/sizeof(*v);
    bubble(v, sz);

    for(int i=0;i<sz; i++){
        cout << v[i] << ", ";
    }
    cout << endl;

    //bubble_sort<mytype> sort(v); 
    //sort.cal();

    return 0;
}

/*
**参考サイト**
- [templateの実装をヘッダファイルに書かないでcppファイルに書く際の書き方まとめ - My Life as a Mock Quant](https://teramonagi.hatenablog.com/entry/20111229/1325167872)
*/