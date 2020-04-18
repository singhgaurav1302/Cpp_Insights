#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>

int foo(int x, int y, const std::function<int(int, int)>& maxi) { 
    return maxi(x, y);
}

//Below works with c++20 -fconcepts
// int foo(int x, int y, const auto& maxi) { 
//     return maxi(x, y);
// }

int main()
{
    //[captures](parameters) -> return type {body};
    [](){};
    
    auto lamb1 = [](int x, int y) { return x > y; };
    std::cout << "Is 2 greater than 4: " << lamb1(2, 4) << std::endl;
    
    auto lamb2 {
        [](int x, int y) { return x < y; }
    };
    std::cout << "Is 2 less than 4: " << lamb2(2, 4) << std::endl;
    
    std::function add {
        [] (int x, int y) -> int { return x + y; }
    };
    std::cout << "add(4, 7): " << add(4, 7) << std::endl;

    std::function sub = [] (int x, int y) -> int { return x - y; };
    std::cout << "sub(4, 7): " << sub(4, 7) << std::endl;
    
    std::cout << "Maximum of 5, 9: " << foo(5, 9, [](int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }) << std::endl;
    
    std::array<int, 8> arr {1, 2, 3, 4, 5, 6, 7, 8};
    auto found = std::find_if(std::begin(arr), std::end(arr), [](const auto& val){ return (val / 2) == std::sqrt(val); });
    std::cout << "Value is: " << *found << std::endl; 
    
    auto isMatching = [](const auto& val){ return (val / 2) == std::sqrt(val); };
    found = std::find_if(std::begin(arr), std::end(arr), isMatching);
    std::cout << "Value is: " << *found << std::endl;
    
    //generic lambda
    auto print = [] (const auto& val) { 
        static int count = 0;
        std::cout << "printing count: " << count++ << " val: " << val << std::endl;
    };
    
    print(1);
    print(2);
    print("hello");
    print("world");
    
    
    //lambda captures
    int temp = 8;
    std::string str = "hello";
    std::string value;
    
    auto capByValue = [temp]() { //temp++; 
        std::cout << "Lambda [temp] - capture by value - member data - () const" << std::endl;};
    capByValue();
    
    auto capByRef = [&temp]() { temp++; std::cout << "Lambda [&temp] - capture by reference = member reference - () const" << std::endl;};
    capByRef();
    std::cout << "temp: " << temp << std::endl;
    
    auto capByValMut = [temp]() mutable { temp++; std::cout << "Lambda [temp] mutable - capture by value - () non const" << std::endl;};
    capByValMut();
    std::cout << "temp: " << temp << std::endl;

    auto capAllByVal = [=]() { //temp++; 
        std::cout << "Lambda [=] - capture by value - () const" << std::endl;};
    capAllByVal();
    std::cout << "temp: " << temp << std::endl;
    
    auto capAllByRef = [&]() { 
        temp++; 
        value = str;
        std::cout << "Lambda [=] - capture by value - () const" << std::endl;};
    capAllByRef();
    std::cout << "temp: " << temp << " " << value << std::endl;
    
    //[&, &temp](){}; //invalid already temp is captured bu ref
    //[temp, &](){}; //invalid default should be first
    //[&, temp, &temp]() {} //invalid repeated twice
    [&, temp] () {};
    [=, &temp] () {};
    
    {
        int width = 2;
        int height = 4;
        auto compareArea = [userArea = width * height](int knownArea) { return userArea == knownArea; };
        std::cout << "Is Area same: " << compareArea(9) << std::endl;
    }
    
    {
        //lambda are object, so when copied internal states are copied.
        int x = 9; 
        auto object = [x]() mutable { std::cout << ++x << std::endl; };
        object();
        object();
        auto l1 = object;
        auto l2 = object;
        l1();
        l2();
        std::cout << "x: " << x << std::endl;        
    }
    {
        //lambda are object, so when copied internal states are copied.
        int x = 1; 
        auto object = [x]() mutable { std::cout << ++x << std::endl; };
        object();
        object();
        auto l1 = std::ref(object);
        auto l2 = std::ref(object);
        l1();
        l2();
        std::cout << "x: " << x << std::endl;        
    }
    
}

/*
#define NDEBUG
#include <cassert>

static_assert(sizeof(int) == 7, "Size of int is not 7");

int main() {
    assert(true == false && "Runtime assert");
}
*/

/*
#include <iostream>
#include <algorithm>

int x = 9;

int max(int x, int y) { std::cout << "my max returns 22 - "; return 22; }

int main() {
    int x = 5;
    std::cout << x << std::endl;
    std::cout << ::x << std::endl;
    
    using namespace std;
    int y = 2;
    std::cout << "max of 2, 5: " << max(y, x) << std::endl;
    std::cout << "max of 2, 5: " << ::max(y, x) << std::endl;
    
    std::vector<int> v1 { 1, 2, 3};
    std::vector<int> v2 { 6, 7, 8};
    std::swap(v1, v2);
    
}
*/
/*
//Initializer list - a proxy object over array
#include <iostream>
#include <utility>

struct Base {
    int x;
    int y;
    Base() { std::cout << "Base x:\t" << x << " y: " << y << " &x: " << &x << " &y: " << &y << std::endl; }
    //explicit
    Base(int a, int b) : x(a), y(b) { std::cout << "Param Base x:\t" << x << " y: " << y << " &x: " << &x << " &y: " << &y << std::endl; }
    Base(const Base& o) : x(o.x), y(o.y) { std::cout << "Copy Base x:\t" << x << " y: " << y << " &x: " << &x << " &y: " << &y << std::endl; }
    Base(Base&& o) noexcept { std::cout << "Move Base&& x:\t" << x << " y: " << y << " &x: " << &x << " &y: " << &y << std::endl; }
    Base& operator=(const Base& o) { x = o.x; y = o.y; std::cout << "Copy Assign x:\t" << x << " y: " << y << " &x: " << &x << " &y: " << &y << std::endl; return *this; }
    Base& operator=(Base&& o) noexcept { 
        x = std::exchange(o.x, -1); y = std::exchange(o.y, -1); 
        std::cout << "Copy Assign x:\t" << x << " y: " << y << " &x: " << &x << " &y: " << &y << std::endl; return *this; }
    
    ~Base() { std::cout << "Dtor x:\t" << x << " y: " << y << std::endl; }
    void print() const { std::cout << "print x:\t" << x << " y: " << y << " &x: " << &x << " &y: " << &y << std::endl; }
};

int main()
{
    Base b(8, 9);
    b.print();
    std::initializer_list<Base> li1 = {{1, 2}, {4, 5}, b};
    std::cout << "size: " << li1.size() << std::endl;
    auto li2 = li1;
    for (const auto& e : li2)
        e.print();
}
*/
