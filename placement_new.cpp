#include <new>
#include <iostream>

// overloading global operator new
void* operator new(size_t size) {
    std::cout << "My operator new size: " << size << std::endl;
    return malloc(size);
}

struct Base {
    int x;
    Base() { x = 11; std::cout << "Base" << std::endl; }
    ~Base() { std::cout << "~Base" << std::endl; }
    void print() { std::cout << "value is: " << x << std::endl; }
    
    // overloading class specific operator new
    static void* operator new(size_t size) {
        std::cout << "Base operator new size: " << size << std::endl;
        return ::operator new(size);
    }
    
    static void* operator new(size_t size, void* p) {
        std::cout << "Base operator placement new size: " << size << std::endl;
        return ::operator new(size, p);
    }
};

int main() {
    {
        //new operator
        // Base* b1 = ::new Base;
        // b1->print();
        
        Base* b2 = new Base;
        b2->print();
        
        // int* pool = new int[100];
        // Base* b3 = new (pool) Base;
        // b3->print();
    }
    
    //operator new
    // Base* b2 = (Base*) operator new(sizeof(Base));
    // b2->print();
    
    // Base* b3 = (Base*) operator new(sizeof(Base), std::nothrow);
    // b3->print();
    
    // int* pool = new int[100];
    // Base* b4 = (Base*) operator new(sizeof(Base), pool);
    // b4->print();
    // std::cout << "pool: " << pool << " b4: " << b4 << std::endl;
}
