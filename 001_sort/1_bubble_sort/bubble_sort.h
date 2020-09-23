#include <iostream>

template<class T>
class bubble_sort{
public:
    
    bubble_sort(T& v){_v = v; std::cout << _v <<std::endl; std::cout << v <<std::endl;};
    ~bubble_sort(){};

    T cal(); 

private:
    T* _v;
};
