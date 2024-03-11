#include <iostream>
template<typename T>
class warehouse
{
private:
   T data;
public:
    void addData(T newdata){
        data = newdata;
    }
    T getData(){
        return data;
    }
};
int main(){
    warehouse<int> intWh;
    intWh.addData(15);
    std::cout << intWh.getData()<< std::endl;

    warehouse<std::string> strWh;
    strWh.addData("templete class");
    std::cout << strWh.getData()<<std::endl;;
    return 0;
}