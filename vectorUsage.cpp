#include <iostream>
#include <vector>
void showVector(std::vector<std::string> &vec){
    std::cout<< "vec1:";
    for (auto &&i : vec)
    {
        std::cout<< " ["<<i << "]  ";
    }
    std::cout<< std::endl;
}
int main(){
    std::vector<std::string> vec1;
    showVector(vec1);

    //push_back
    vec1.push_back("first vector member");
    vec1.push_back("second vector member");
    showVector(vec1);

    //pop_back
    vec1.pop_back();
    showVector(vec1);

    //empty
    if (!vec1.empty())
    {
        std::cout<<"vec1  is not empty!" << std::endl;
    }
    
    //insert
    vec1.insert(vec1.end(), "second vector member");
    vec1.insert(vec1.end(), "third vector member");
    vec1.insert(vec1.end(), "forth vector member");
    showVector(vec1);

    //erase
    vec1.erase(vec1.end());
    showVector(vec1);

    //resize & size & capacity &
    std::cout<<"vec1 size    :"<<vec1.size()<< std::endl;
    std::cout<<"vec1 capacity:"<<vec1.capacity()<< std::endl;
    vec1.shrink_to_fit();
    //fites capacity as own size shrink_to_fit 
    std::cout<<"vec1 size    :"<<vec1.size()<< std::endl;
    std::cout<<"vec1 capacity:"<<vec1.capacity()<< std::endl;
    vec1.resize(6);
    std::cout<<"vec1 size    :"<<vec1.size()  << std::endl;   
    std::cout<<"vec1 capacity:"<<vec1.capacity()  << std::endl;
    //returns maximum vector member count
    std::cout<<"vec1 max_size:"<<vec1.max_size() << std::endl;


    //assign
    vec1.assign(5,"A");
    showVector(vec1);

    //operator=
    std::vector<std::string> vec3(5,"B");
    vec1.operator=(vec3);
    showVector(vec1);

    //=
    std::vector<std::string> vec2;
    vec2.push_back("first");
    vec2.push_back("second");
    vec2.push_back("third");
    vec2.push_back("forth");

    vec1 = vec2;
    showVector(vec1);

    //operator[]
    std::cout<< "vec1 members: ";
    for (size_t i = 0; i < vec1.size(); i++)
    {
        std::cout<<vec1.operator[](i) << " , ";
    }
    std::cout << std::endl;
    //emplace
    vec1.emplace(vec1.begin() + 4, "fifth");
    vec1.emplace_back("sixth");
    showVector(vec1);   

    //begin, end
    std::cout<< "vec1 members         : ";
    for (auto i = vec1.begin(); i < vec1.end(); i++)
    {
        std::cout << *i<<" , ";
    }    
    std::cout << std::endl;

    //rbegin, rend
    std::cout<< "reversed vec1 members: ";
    for (auto i = vec1.rbegin(); i < vec1.rend(); i++)
    {
        std::cout << *i<<" , ";
    }    
    std::cout << std::endl;

    std::cout<<vec1.at(5)<<std::endl;
    
    return 0;
}