#include <iostream>
#include <list>
int main(){
    std::list<int> mylist = {1,2,3};

    for (auto &&i : mylist)
    {
        std::cout<<i;
    }

    mylist.pop_front();
    std::cout<< "\npop_front result : ";
    for (auto &&i : mylist)
    {
        std::cout<<i;
    }
    
    mylist.push_front(1);
    std::cout<< "\npush front result: ";
    for (auto &&i : mylist)
    {
        std::cout<< i;
    }

    mylist.merge(std::list<int>{6,5,6});
    std::cout<< "\nmerge result    :";
    for (auto &&i : mylist)
    {
        std::cout<< i;
    }

    int a = 6;
    mylist.assign(5,a);
    std::cout<< "\nssign result    :";
    for (auto &&i : mylist)
    {
        std::cout<< i;
    }

    mylist.assign(std::initializer_list<int>{9,8,7,6});
    std::cout<< "\nintializer list result:" ;
    for (auto &&i : mylist)
    {
        std::cout<< i;
    }
    return 0;
}