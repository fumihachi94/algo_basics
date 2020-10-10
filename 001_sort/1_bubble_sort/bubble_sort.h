#include <iostream>

using namespace std;

template<class T>
class bubble_sort{
public:
    
    bubble_sort(T* v, size_t sz){
        _v = v;
        _sz = sz;
    };
    ~bubble_sort(){};

    int cal(); 

private:
    T* _v;
    size_t _sz;
};
