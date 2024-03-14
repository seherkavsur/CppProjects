#include <iostream>
#include <tuple>

int main()
{
    std::tuple<int, std::string, double> myTuple(10,"hello",3.14);

// Access elements using std::get or ind
    int first =  std::get(myTuple);
    std::cout << "first element: " << std::get(myTuple) << std::endl;
    std::cout << "second element: " << std::get(myTuple) << std::endl;
    std::cout << "third element: " << myTuple << std::endl;

//   std::cout << "First element (index): " << std::tuple_element_t<0, decltype(myTuple)>::type(myTuple) << std::endl;

    return 0;
}