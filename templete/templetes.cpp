#include <iostream>
template<typename T>
void printval(T value){
    std::cout << value << std::endl;
}
int main(){
    printval(10);
    printval("templetes tests");
    printval(1.555);
    return 0;
}