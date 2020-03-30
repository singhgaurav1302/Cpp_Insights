#include <iostream>
#include <string>
#include <memory>

struct Base {
    Base() : str{"empty"} { std::cout << "Base: " << this << std::endl; }
    Base(std::string s) : str{s} { std::cout << "Base string: " << str << std::endl; }
    ~Base() { std::cout << "~Base: " << this << " - " << str << std::endl; }
    std::string str;
};

struct CustomDeleter {
    void operator()(Base* p) { 
        std::cout << "CustomDeleter \n"; 
        delete p; 
    }
};

void FuncDeleter(Base* p) {
    std::cout << "FuncDeleter \n";
    delete p;
}

void FuncArrayDeleter(Base* p) {
    std::cout << "FuncArrayDeleter \n";
    delete[] p;
}

//Specialized for ptr14 
//template <> 
// struct std::default_delete<Base> {
//     void operator()(Base * ptr) { 
//         std::cout << "DefaultDelete specialized but invalid!!! for make_unique\n"; 
//         delete ptr;
//     }
// };


int main() {
    ////unique_ptr with C-style arrays
    //auto ptr1 = std::make_unique<Base[]>(3, "hello");
    //std::unique_ptr<Base[]> ptr2(new Base[2]{Base("hello"), Base("world")});
    //auto ptr3 = std::make_unique<Base[3]>(3);         //Error: Base[3] not allowed function deleted. Array of known bound not allowed

    //auto ptr4 = std::make_unique<Base>();
    ////Function Object Deleter does not add up to pointer memory
    std::unique_ptr<Base, CustomDeleter> ptr5(new Base);
    std::cout << "Size of unique_ptr with function object: " << sizeof(ptr5) << std::endl;
    
    ////Haveing C-Style function deleters increses unique_ptr size
    std::unique_ptr<Base, decltype(&FuncDeleter)> ptr6(new Base, &FuncDeleter);
    std::cout << "Size of unique_ptr with function: " << sizeof(ptr6) << std::endl;
    //std::unique_ptr<Base, decltype(FuncDeleter)*> ptr7(new Base, FuncDeleter);
    //std::unique_ptr<Base, void (*)(Base*)> ptr8(new Base, FuncDeleter);
    //std::unique_ptr<Base, void (*)(Base*)> ptr9(new Base, [](Base* p){ std::cout << "lamda \n"; delete p; });
    //std::unique_ptr<Base[], void (*)(Base*)> ptr10(new Base[2], [](Base* p){ std::cout << "lamda: " << p << "\n"; delete[] p; p = nullptr;});
    //std::unique_ptr<Base[], void (*)(Base*)> ptr11(new Base[2], FuncArrayDeleter);
    //std::cout << "Size of unique_ptr with function: " << sizeof(ptr11) << std::endl;
    
    //auto ptr12 = std::make_unique<Base>("First String");
    //ptr12.reset(new Base("second string"));
    
    ////make_unique does not support Custome deleters, as internally it uses new to allocate memory
    ///so it uses delete to dealloacte, so it does not provide any way to give custome DELETER
    //auto ptr14 = std::make_unique<Base>();
}
