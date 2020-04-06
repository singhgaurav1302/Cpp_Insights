/* Stack
push_back
pop_back

5
4
3
2
1
vector list deque
*/

/*
//std::queue
#include <iostream>
#include <memory>
#include <exception>
#include <queue>
#include <list>

struct Base {
    Base(int x, int y) : x_{x}, y_{y} { std::cout << "Base Ctor x: " << x_ << "  " << y_ << std::endl; }
    ~Base() { std::cout << "Destroying x: " << x_ << "  " << y_ << std::endl; }
    Base(const Base& o) : x_{o.x_}, y_{o.y_} { std::cout << "Copy Ctor x: " << x_ << "  " << y_ << std::endl; }
    Base(Base&& o) : x_{std::exchange(o.x_, -1)}, y_{std::exchange(o.y_, -1)} { std::cout << "Move Ctor x: " << x_ << "  " << y_ << std::endl; }
  
    Base& operator=(const Base& o) { x_ = o.x_; y_ = o.y_; std::cout << "Copy Assignment Ctor x: " << x_ << "  " << y_ << std::endl; return *this; }
    Base& operator=(Base&& o)  { x_ = std::exchange(o.x_, -1); y_ = std::exchange(o.y_, -1); std::cout << "Move Assignment Ctor x: " << x_ << "  " << y_ << std::endl; return *this;}
    
    int x_, y_;
};

int main() 
{
    std::cout << "Changing underlying container to list for queue\n";
    std::queue<int, std::list<int>> qList;
    qList.push(1);
    qList.push(2);
    qList.push(3);    
    std::cout << "qList front: "<< qList.front() <<  ",\tqList back: " << qList.back() <<  ",\tqList size: " << qList.size() << std::endl;
    
    std::queue<int> q;    
    q.push(1);
    q.push(2);
    q.push(3);
    
    std::cout << "q front: " << q.front() << ",\tq back: " << q.back() <<  ",\tq size: " << q.size() << std::endl;
    
    q.pop();
    std::cout << "q front: " << q.front() <<  ",\tq back: " << q.back() <<  ",\tq size: " << q.size() << std::endl;
    std::cout << "q isempty: " << q.empty() << std::endl;
    
    std::queue<int> q2;
    q.swap(q2);
    std::cout << "q size swapped: " << q.size() << std::endl;
    std::cout << "q2 size swapped: " << q2.size() << std::endl;
    
    std::cout << "\n\nDifferent ways of Initializing queue" << std::endl;
    std::queue<int> q1(q);
    std::cout << "q1 size: " << q1.size() << std::endl;
    
    std::deque<int> deck{11, 12, 13, 14};
    std::queue<int> q4(deck);
    std::cout << "q4 front:" << q4.front() <<  ",\tq4 back: " << q4.back() <<  ",\tq4 size: " << q4.size() << std::endl;
    q4.push(99);
    std::cout << "q4 back: " << q4.back() << std::endl;
    
    std::list<int> li{11, 21, 31, 14};
    std::queue<int, std::list<int>> q5(li);
    std::cout << "q5 front:" << q5.front() <<  ",\tq5 back: " << q5.back() <<  ",\tq5 size: " << q5.size() << std::endl;
    q5.push(909);
    std::cout << "q5 back: " << q5.back() << std::endl;
    
    std::queue<int> q6(std::move(deck));
    std::cout << "q6 front:" << q6.front() <<  ",\tq6 back: " << q6.back() <<  ",\tq6 size: " << q6.size() << std::endl;
    std::cout << "sizeof deck: " << deck.size() << std::endl;
    
    std::queue<int, std::list<int>> q7({33, 32, 34, 35}); //list gets initailized with initailizer_list
    q7.push(8);
    q7.pop();
    std::cout << "q7 front:" << q7.front() <<  ",\tq7 back: " << q7.back() <<  ",\tq7 size: " << q7.size() << std::endl;
    
    std::queue<int, std::list<int>> q8(std::list<int>{7,8,9}); //list gets initailized with initailizer_list
    q8.push(89);
    q8.pop();
    std::cout << "q8 front:" << q8.front() << ",\tq8 back: " << q8.back() << ",\tq8 size: " << q8.size() << std::endl;
    
    std::cout << "\n\n-------------------------------------------------\n\n" << std::endl;
    
    std::queue<Base> qBase;
    {
        Base b1{1, 2};
        qBase.push(b1);
    }
    qBase.emplace(3, 4);
    qBase.push(*new Base(5,6)); //memory leak
    qBase.push(Base(7,8));      //Move Ctor
    
    std::cout << "qBase size: " << qBase.size() << std::endl;
}
*/


/*
#include <iostream>
#include <memory>
#include <exception>
#include <array>

int main() 
{
    //int arr[0]; //Warning: Compiler dependent zero size array not allowed
    std::array<int, 0> za;
    std::cout << "zero size array: " << za.size() << std::endl;
    
    std::array<int, 3> a {1};
    std::cout << "uninitialized array size: " << a.size() << ",\t";
    for(auto& e : a)
        std::cout << e << ", ";
    std::cout << std::endl;
    
    std::array<int, 3> a1{1, 2};
    std::array<int, 3> a2 = {5, 6, 7};
    std::array<int, 4> a3({1, 2, 3, 4});
    
    int* ptr = a1.data();
    std::cout << "ptr: " << ptr << std::endl;
    std::cout << "element[0]: " << std::get<0>(a1) << std::endl;
    std::cout << "element[1]: " << a1[1] << std::endl;
    
    a1.fill(99);
    for(auto& e : a1)
        std::cout << e << " ";
    std::cout << std::endl;
    
    a1 = a2;
    for(auto& e : a1)
        std::cout << e << " ";
    std::cout << std::endl;
    
    //a1 = a3;  //not allowed size are different
    //a3 = a1;
    
    a1.at(1) = 88;
    std::cout << "a1.at(1): " << a1.at(1) << std::endl;
    try {
        a1.at(4) = 77;
    }
    catch(std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    a2.fill(77);
    a1 = std::move(a2);
    std::cout << "a2 array moved: ";
    for(auto& e : a2)
        std::cout << e << " ";
    std::cout << std::endl;
    
    //--------------------------------------------------------------------------------------
    
    std::array<std::unique_ptr<int>, 2> a4;
    a4[0] = std::make_unique<int>(4);
    std::cout << *a4[0] << std::endl;
    a4[1].reset(new int(88));
    std::cout << *a4[1] << std::endl;
    
    int x = 9;
    std::array<std::unique_ptr<int>, 2> a5{std::make_unique<int>(76), std::make_unique<int>(77)};
    std::cout << *a5[0] << " " << *a5[1] << std::endl;
    
    std::array<std::unique_ptr<int>, 2> a6{std::unique_ptr<int>(new int(55)), std::unique_ptr<int>(new int(54))};
    std::cout << *a6[0] << " " << *a6[1] << std::endl;
    a6[0] = a6[1];//std::unique_ptr<int>(new int(x));
    
    std::unique_ptr<int> p;
    p = std::unique_ptr<int>(new int(x)); //invokes rvalue assignment op
    //p1 = p2
    //a6[0] = a6[1];
    //p = p;
    //a3[0] = a2[0];
}
*/

/*
//Unique_ptr to vector
#include <iostream>
#include <vector>
#include <memory>

struct Base {
    Base() { std::cout << "Base" << std::endl; }
    ~Base() { std::cout << "~Base" << std::endl; }
};

int main() {
    std::unique_ptr<std::vector<int>> p{ new std::vector<int>(10, 99)};
    std::cout << (*p)[0] << std::endl;
    std::cout << (*p)[1] << std::endl;
    
    std::unique_ptr<std::vector<Base>> p1{ new std::vector<Base>(10, 99)};
    std::cout << (*p)[0] << std::endl;
    std::cout << (*p)[1] << std::endl;
}
*/

/*
//Copy Swap Idiom
#include <iostream>
struct Base {
    Base() { std::cout << "Base" << std::endl; }
    Base(const Base& o) { std::cout << "Copy Ctor" << std::endl; }
    Base(Base&& o) { std::cout << "Move Ctor" << std::endl; }
    //Base& operator=(Base o) { std::cout << "Copy Swap Assignment" << std::endl; return *this; }
    Base& operator=(const Base& o) { std::cout << "Copy Assignment" << std::endl;   return *this; }
    Base& operator=(Base&& o) { std::cout << "Move Assignment" << std::endl; return *this; }
    
    int* ptr;
};

Base foo(Base o) {
    return o;
}

int main()
{
    Base a;
    Base b;
    a = b;
    a = std::move(b);
    //a = foo(b); //copy move, move assign
    //a = foo(std::move(b)); //move move, move assign
    //a = b; //in this case one additional call
}
*/
