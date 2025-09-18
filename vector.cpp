#include "vector.hpp"


// #1                                                                                                   
my::vector::vector() : siz(0), cap(0), ptr(new int[0]) {}
my::vector::~vector() {
    delete[] ptr;
}



// #2: define operator[]                                                                                
const int& my::vector::operator[](size_t i) const {
    return *(ptr + i);                                                          
}
int& my::vector::operator[](size_t i) {
    return *(ptr + i);
}

size_t my::vector::size()     const { return siz; }
size_t my::vector::capacity() const { return cap; }

bool my::vector::empty() const { return siz == 0; }




// #3: Constructors for vector(size_t), vector(size_t, int), vector(std::initializer_list<int>)         
my::vector::vector(size_t i) : siz(i), cap(i), ptr(new int[i]()) {}
my::vector::vector(size_t a, int b) : siz(a), cap(a), ptr(new int[a]) {
    int* p = ptr;
    for (size_t i = 0; i < a; i++) {
        p[i] = b;
        // *p = i;
        // ++p;
    }                                                                
}

my::vector::vector(std::initializer_list<int> il) : siz(il.size()),  
cap(il.size()),
ptr(new int[il.size()]) {
    int* p = ptr;

    for (int i : il) {
        *p = i;
        ++p;
    }
}


// #4: define the member function void clear()                                                          
void my::vector::clear() { siz = 0; }                                
void my::vector::pop_back() { siz -= 1; }

void my::vector::new_capacity(size_t n) {
    if (n < cap) {
        n = cap;
    }
    cap = n;
    int* new_ptr = new int[cap];

    for (size_t i = 0; i < siz; ++i) {
        new_ptr[i] = ptr[i];
    }
    delete[] ptr;

    ptr = new_ptr;
}




// #5: define void reserve(size_t), void push_back(int), void resize(size_t n, int i)                   
void my::vector::reserve(size_t i) { // TEST
    if (i < cap) return;
    else {
        new_capacity(i);
        return;
    }
}
void my::vector::push_back(int i) { // TEST
    if (cap == 0) {
        new_capacity(1);
        ptr[0] = i;
        siz = 1;
    }
    else if (cap == siz) {
        new_capacity(cap * 2);
        ptr[siz++] = i;
    }
    else {
        ptr[siz++] = i;
    }
}
void my::vector::resize(size_t n, int i) {
    if (n >= cap * 2) { // Do I want it to be at n*2 or greater than n*2?
        new_capacity(n);
    }
    else if (n > cap) {
        new_capacity(cap * 2);
    }
    for (size_t j = siz; j < n; j++) {
        push_back(i);
    }
    siz = n;
}

const int* my::vector::data() const { return ptr; }
int* my::vector::data() { return ptr; }




// #6: member function void swap(vector&), move constructor vector(vector&&),                           
// move assignment operator vector& operator=(vector&&), 
// copy constructor vector(const vector&), 
// copy assignment operator vector& operator=(const vector&)

// member function
void my::vector::swap(vector& other) {
    std::swap(siz, other.siz);
    std::swap(cap, other.cap);
    std::swap(ptr, other.ptr);
}
// move constructor
my::vector::vector(vector&& other) : vector() {
    swap(other);
}
// move assignment operator 
my::vector& my::vector::operator=(vector&& other) {
    swap(other);
    return *this;
}
// copy constructor
my::vector::vector(const vector& other) : siz(other.siz), cap(other.siz), ptr(new int[other.siz + 1]) {
    for (size_t i = 0; i <= siz; ++i) {
        ptr[i] = other.ptr[i];
    }
}
// copy assignment operator
my::vector& my::vector::operator=(const vector& other) {
    if (this == &other) {
        return *this;
    }
    vector copy(other);
    swap(copy);
    return *this;
}

void my::swap(vector& v1, vector& v2) {
    v1.swap(v2);
}
