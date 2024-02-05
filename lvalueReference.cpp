#include <iostream>
void func(int t){
    ++t;
    
}
void funcref(int &k){
    ++k;
}
int main(){
    int value = 10;
    func(value);
    std::cout  <<"the value of x after the func() is called   :" << value<< std::endl;
    funcref(value);
    std::cout << "the value of x after the funcref() is called:"<<value<< std::endl;
     
    //l value expresion
    int x = 100;
    int &y = x;
    std::cout << std::endl << "y  :" << y  << "  x: "<<x << std::endl;
    
    return 0;
}