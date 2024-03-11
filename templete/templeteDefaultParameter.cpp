#include <iostream>
template<typename T, typename U = int>
class even{
    T first;
    U second;
    public:
    even(T firstParameter,U secondParameter){
        first = firstParameter;
        second =secondParameter;
    }
    T firstValue(){
        return first;
    }
    U secondValue(){
        return second;
    }
};
int main(){
    even<std::string, int> obj1 = even<std::string, int>{"jhon", 5};
    even<float, std::string> obj2 = even<float, std::string>{15.1, "max"};

    std::cout<< obj1.firstValue() << std::endl;
    std::cout<< obj1.secondValue() << std::endl;
    std::cout<< obj2.firstValue() << std::endl;
    std::cout<< obj2.secondValue() << std::endl;
    return 0;
}