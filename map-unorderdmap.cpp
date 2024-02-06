#include <iostream>
#include <map> 
#include <unordered_map>
int main(){
    //map
    std::map<char, int> map;
    map['b'] = 2;
    map['c'] = 1;
    map['a'] = 0;
    map['d'] = 4;

    for(std::map<char, int>::iterator iter = map.begin(); iter != map.end(); ++iter){
        std::cout << iter->first << "-" << iter->second << std::endl;
    }
    //output
    /*
    a-0
    b-2
    c-1
    d-4
    */

    //unordered map
    std::cout<< "---------\n";
    std::unordered_map<char, int> unmap;
    unmap['b'] = 2;
    unmap['c'] = 1;
    unmap['a'] = 0;
    unmap['d'] = 4;
    for(std::unordered_map<char, int>::iterator iter = unmap.begin(); iter != unmap.end(); ++iter){
        std::cout << iter->first << "-" << iter->second << std::endl;
    }
    //output
    /*
    d-4
    a-0
    c-1
    b-2
    */
    return 0;
}