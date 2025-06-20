#include <iostream>
using namespace std;

class Singleton {
private:
    Singleton() {
        cout << "Constructor called" << endl;
    }

    // Deleted copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance() {
        static Singleton instance;
        cout << "Returning the Singleton instance at address: " << &instance << endl;
        return instance;
    }

    void sayHello() {
        cout << "Hello from Singleton at address: " << this << endl;
    }
};

int main() {
    Singleton& s1 = Singleton::getInstance();
    s1.sayHello();

    Singleton& s2 = Singleton::getInstance();
    s2.sayHello();

    if (&s1 == &s2) {
        cout << "Yes, s1 and s2 point to the SAME instance!" << endl;
    } else {
        cout << "Different instances! Something went wrong." << endl;
    }

    return 0;
}


// output

// Constructor called
// Returning the Singleton instance at address: 0x7ff635b640d0
// Hello from Singleton at address: 0x7ff635b640d0
// Returning the Singleton instance at address: 0x7ff635b640d0
// Hello from Singleton at address: 0x7ff635b640d0
// Yes, s1 and s2 point to the SAME instance!


// 🔷 What is a Singleton Class?
// A singleton class is a class that allows only one object (instance) of itself to be created during the entire program.

// 📦 How Singleton Works
// It:

// Hides the constructor (so no one can do new MyClass()).

// Provides a static method (e.g., getInstance()) to get the only instance.

// Prevents copying or assigning the object (so no duplicates can be created).

// In a singleton, the getInstance() function always returns a reference to the same static object.

// This line:

// cpp
// Copy
// Edit
// static Singleton instance;
// means that:

// The first time getInstance() is called, it creates instance.

// Every next time, it returns the same object, not a new one.

// It's because of the static keyword.
// inside a function, it means:

// "Create this variable only once, and reuse the same memory every time the function is called."
// Singleton(const Singleton&) = delete;
// Singleton& operator=(const Singleton&) = delete;
// These lines are C++11 features that disable copying of objects.

// Code	Meaning
// Singleton(const Singleton&) = delete;	Don't allow copying of the object
// Singleton& operator=(...) = delete;	Don't allow assigning the object