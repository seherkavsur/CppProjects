#include <iostream>
class A{
    public: 
    //virtual fonksiyon
    virtual void foo()const{
        std::cout << "called A::FOO()"<< std::endl;
    }
    //common function
    void commonfoo()const{
        std::cout << "called common function"<< std::endl;
    }
};
class B : public A
{
    public:
    //override function
    void foo()const override{
        std::cout << "called B::FOO()"<< std::endl;
    }
};

void func(const A& a){
    a.foo();
    a.commonfoo();
}
int main(){
    B b;
    func(b);
}