#ifndef vector_hpp
#define vector_hpp


#include <iostream>
#include <initializer_list>
#include <utility>


namespace my {


class vector {
public:
    vector();
    ~vector();


    size_t size()     const;
    size_t capacity() const;

    bool empty() const;

    const int& operator[](size_t) const;
          int& operator[](size_t);


    explicit vector(size_t);
    vector(size_t, int);
    vector(std::initializer_list<int>);


    void pop_back();
    void clear();


    void reserve(size_t);
    void push_back(int);
    void resize(size_t, int = 0);


    void swap(vector&);

    vector(vector&&);
    vector& operator=(vector&&);

    vector(const vector&);
    vector& operator=(const vector&);


    const int* data() const;
          int* data();


private:
    size_t siz;
    size_t cap;
    int*   ptr;


    void new_capacity(size_t);
};


void swap(vector&, vector&);


}


#endif /* vector_hpp */
