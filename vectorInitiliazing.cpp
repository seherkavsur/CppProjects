#include <iostream>
#include <vector>

int main(){
    //the first parameter is repeat count, the second parameter is value.
    std::vector<int> intVec1(20,3);
    std::cout << "vector1 : ";
    for (auto &&i : intVec1)
    {
        std::cout<< i;
    }

    std::cout << "\nvector2 : ";
    std::vector<int> intVec2(15);
    for (auto &&i : intVec2)
    {
        std::cout<< i;
    }

    std::cout << "\nvector3 : ";
    std::vector<int> intVec3(0);
    for (auto &&i : intVec3)
    {
        std::cout<< i;
    }
    return 0;
}