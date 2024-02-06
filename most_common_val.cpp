#include <iostream>
#include <vector>
#include <unordered_map>
int find_most_common(std::vector<int>& vec){
    std::unordered_map<int, int> freq;

    for (auto &&i : vec)
    {
        freq[i]++;
    }
    int value = 0;
    int repaitcount = 0;

    for (auto &&pair : freq)
    {
        if (pair.second > repaitcount)
        {
            value = pair.first;
            repaitcount  = pair.second;
        }
        
    }
    return value;    
}
int main(){
    std::vector<int> vec = {1, 2, 3, 4, 2, 2, 3, 5, 1, 2, 4, 4};

    auto result = find_most_common(vec);
    std::cout << "the most commond value is : " << result;
    return 0;
}