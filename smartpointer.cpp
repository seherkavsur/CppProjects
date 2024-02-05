#include <iostream>
#include <memory>
void throwException(){
    throw std::runtime_error("\nit's a exception");
}
class cls{
    public:
    cls(){
        std::cout << "called ctor of the cls class" << std::endl;
    }
    ~cls(){
        std::cout << "called dtor of the cls class" << std::endl;
    }
};
void usePointer(){
    cls *clsPtr = new cls();

    try
    {
        throwException();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    //clsPtr delete edilmeden throw eder. 
    delete clsPtr;
}
void useSmartPointer(){
    std::unique_ptr<cls> uptr = std::make_unique<cls>();
}
int main(){
    //if you use the pointer, you must call the dtor.
    usePointer(); 
    //if you use the smart pointer, it can called the dtor automaticly.
    useSmartPointer();
    return 0;
}