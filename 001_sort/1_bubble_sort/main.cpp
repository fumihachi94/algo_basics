#include <iostream>
#include "bubble_sort.h"

#define mytype int

using namespace std;

int main(void){
    mytype v[] = {10, 45, 23, 45, 65, 20, 4, 1};
    
    size_t sz = sizeof(v)/sizeof(*v);

    for(int i=0;i<sz; i++) cout << v[i] << ", ";
    cout << endl;

    // 実行
    bubble_sort<mytype> bubble(v, sz); 
    if(bubble.cal()){
        for(int i=0;i<sz; i++) cout << v[i] << ", ";
        cout << endl;
    }

    return 0;
}

/*
**参考サイト**
- [templateの実装をヘッダファイルに書かないでcppファイルに書く際の書き方まとめ - My Life as a Mock Quant](https://teramonagi.hatenablog.com/entry/20111229/1325167872)
*/