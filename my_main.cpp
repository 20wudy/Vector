#include <iostream>
#include "vector.hpp"
#include <utility>
#include <cassert> // added




using std::cout;
using std::endl;




void print_info(const my::vector& v, size_t N) {
    cout << "             size: " << v.size() << '\n';
    cout << "         capacity: " << v.capacity() << '\n';

    if (N < 10) { cout << ' '; }

    cout << "first " << N << " elements: ";

    for (size_t i = 0; i < N; ++i) {
        cout << *(v.data() + i) << ' ';
    }
    cout << '\n' << endl;
}


//int main() {
//    
//    // out of bounds
//    {
//        my::vector v;
//        v.push_back(1);
//        v.push_back(2);
//        int x = v[2]; // Out-of-bounds access
//    }
//    
//    return 0;
//}


int main() {
    cout << std::boolalpha;
    cout << "--------------------------------------------\n" << endl;




{
    cout << "CONSTRUCTORS\n" << endl;

    const my::vector default_constructed;
    cout <<       "siz == " <<  default_constructed.size()          << ' ';
    cout <<      " cap == " <<  default_constructed.capacity()      << ' ';
    cout <<      " ptr == " <<  default_constructed.data()          << ' ';
    cout << "  empty() == " <<  default_constructed.empty()         << endl;

    const my::vector size_t_constructed(18);
    cout <<       "siz == " <<  size_t_constructed.size()           << ' ';
    cout <<       "cap == " <<  size_t_constructed.capacity()       << ' ';
    cout <<    "ptr[8] == " <<  size_t_constructed[8]               << ' ';
    cout <<  " empty() == " <<  size_t_constructed.empty()          << endl;

    const my::vector size_t_w_val_constructed(38, 48);
    cout <<       "siz == " <<  size_t_w_val_constructed.size()     << ' ';
    cout <<       "cap == " <<  size_t_w_val_constructed.capacity() << ' ';
    cout <<   "ptr[28] == " <<  size_t_w_val_constructed[28]        << endl;

    const my::vector init_list_constructed {58, 68, 78, 88, 98, 108};
    cout <<       "siz == " <<  init_list_constructed.size()        << ' ';
    cout <<      " cap == " <<  init_list_constructed.capacity()    << ' ';
    cout <<   " ptr[3] == " <<  init_list_constructed[3]            << endl;
}


    cout << "\n--------------------------------------------\n\n";


{
    cout << "OPERATIONS NOT REQUIRING MEMORY REALLOCATION " << endl;
    cout << "pop_back, clear, reserve, push_back, resize\n" << endl;

    my::vector v {0, 1, 2, 3, 4, 5, 6, 7};
    print_info(v, 8);  // siz == 8, cap == 8

    int* ptr = &v[0];  // store copy of v.ptr

    v.pop_back();      // siz == 7, cap == 8, ptr unchanged
    v.pop_back();      // siz == 6, cap == 8, ptr unchanged
    v.pop_back();      // siz == 5, cap == 8, ptr unchanged
    v.pop_back();      // siz == 4, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements changed

    v.clear();         // siz == 0, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements changed

    v.resize(3);       // siz == 3, cap == 8, ptr unchanged
    print_info(v, 8);  // updated first 3 elements to 0

    v.resize(5, 88);   // siz == 5, cap == 8, ptr unchanged
    print_info(v, 8);  // updated next 2 elements to 88

    v.resize(2, 888);  // siz == 2, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements updated

    v.resize(0);       // siz == 0, cap == 8, ptr unchanged
    print_info(v, 8);  // no elements updated

    v.push_back(11);   // siz == 1, cap == 8, ptr unchanged
    v.push_back(22);   // siz == 2, cap == 8, ptr unchanged
    v.push_back(33);   // siz == 3, cap == 8, ptr unchanged
    print_info(v, 8);  // first 3 elements updated to 11, 22, 33, respectively

    v.reserve(4);      // nothing changes since cap == 8 >= 4
    print_info(v, 8);  // no elements updated

    v.resize(6);       // siz == 6, cap == 8, ptr unchanged
    print_info(v, 8);  // updated next 3 elements to 0

    if (ptr == &v[0]) {
        cout << "no memory reallocations so far" << endl;
    }
}


    cout << "\n--------------------------------------------\n\n";


{
    cout << "OPERATIONS REQUIRING MEMORY REALLOCATION" << endl;
    cout << "reserve, push_back, resize\n"             << endl;

    my::vector v;
    print_info(v, 0);


    int* ptr = v.data();  // store copy of v.ptr


    for (int i = 1; i <= 7; ++i) {
        v.push_back(i * 11);

        if (ptr != &v[0]) {
            cout << "there's been a memory reallocation" << endl;
            ptr = &v[0];
        }
        print_info(v, v.capacity());
    }


    v.reserve(10);     // ptr changed, capacity set to 10

    if (ptr != &v[0]) {
        cout << "there's been a memory reallocation" << endl;
        ptr = &v[0];
    }
    print_info(v, 10); // first 7 values are copied, last 3 values are uninitialized


    v.resize(16, 8);   // capacity doubled

    if (ptr != &v[0]) {
        cout << "there's been a memory reallocation" << endl;
        ptr = &v[0];
    }
    print_info(v, 20); // first 7 values copied, next 9 are 8s, last 4 are uninitialized


    v.resize(24);      // capacity doubled

    if (ptr != &v[0]) {
        cout << "there's been a memory reallocation" << endl;
        ptr = &v[0];
    }
    print_info(v, 0);  // first 16 values copied, next 8 are 0s, last 16 are uninitialized


    v.resize(81);      // capacity set to 81 (since 81 > 2 * 40)

    if (ptr != &v[0]) {
        cout << "there's been a memory reallocation" << endl;
        ptr = &v[0];
    }
    print_info(v, 0);  // first 24 values copied, next 57 are 0
}


    cout << "--------------------------------------------\n\n";


{
    cout << "SWAP, MOVE, COPY\n" << endl;

    my::vector v1 { 1,  2,  3,   };
    my::vector v2 {11, 22, 33, 44};

    v1.reserve(5);
    v2.reserve(6);

    cout << "v1 info..." << endl;
    print_info(v1, v1.capacity());
    int *p1 = &v1[0];

    cout << "v2 info..." << endl;
    print_info(v2, v2.capacity());
    int *p2 = &v2[0];




    v1.swap(v2);

    cout << "v1 info..." << endl;
    print_info(v1, v1.capacity());

    cout << "v2 info..." << endl;
    print_info(v2, v2.capacity());

    if ((&v1[0] == p2) && (&v2[0] == p1)) {
        cout << "v1 and v2's resources have been swapped" << endl;
    }

    v1.swap(v2);
    cout << "v1 and v2 have been swapped back\n" << endl;




    my::vector v3(std::move(v1));

    cout << "v1 info..." << endl;
    print_info(v1, v1.capacity()); // now the empty vector

    cout << "v3 info..." << endl;
    print_info(v3, v3.capacity());

    if ((v1.data() == nullptr) && (&v3[0] == p1)) {
        cout << "v3 stole v1's resources\n" << endl;
    }




    v1 = std::move(v3);

    cout << "v1 info..." << endl;
    print_info(v1, v1.capacity());

    if (&v1[0] == p1) {
        cout << "v1 stole v3's resources back\n" << endl;
    }




    my::vector v4(v1);

    cout << "v4 info..." << endl;
    print_info(v4, v4.capacity()); // v4.siz == v4.cap == v1.siz




    v4 = v2;

    cout << "v4 info..." << endl;
    print_info(v4, v4.capacity()); // v4.siz == v2.siz




    int* p4 = &v4[0];

    v4 = v4;
    if (p4 == &v4[0]) {
        cout << "self-assignment does not allocate memory" << endl;
    }
}


    return 0;
}





/*
DESIRED OUTPUT...
 --------------------------------------------

 CONSTRUCTORS

 siz == 0  cap == 0  ptr == 0x0   empty() == true
 siz == 18 cap == 18 ptr[8] == 0  empty() == false
 siz == 38 cap == 38 ptr[28] == 48
 siz == 6  cap == 6  ptr[3] == 88

 --------------------------------------------

 OPERATIONS NOT REQUIRING MEMORY REALLOCATION
 pop_back, clear, reserve, push_back, resize

              size: 8
          capacity: 8
  first 8 elements: 0 1 2 3 4 5 6 7

              size: 4
          capacity: 8
  first 8 elements: 0 1 2 3 4 5 6 7

              size: 0
          capacity: 8
  first 8 elements: 0 1 2 3 4 5 6 7

              size: 3
          capacity: 8
  first 8 elements: 0 0 0 3 4 5 6 7

              size: 5
          capacity: 8
  first 8 elements: 0 0 0 88 88 5 6 7

              size: 2
          capacity: 8
  first 8 elements: 0 0 0 88 88 5 6 7

              size: 0
          capacity: 8
  first 8 elements: 0 0 0 88 88 5 6 7

              size: 3
          capacity: 8
  first 8 elements: 11 22 33 88 88 5 6 7

              size: 3
          capacity: 8
  first 8 elements: 11 22 33 88 88 5 6 7

              size: 6
          capacity: 8
  first 8 elements: 11 22 33 0 0 0 6 7

 no memory reallocations so far

 --------------------------------------------

 OPERATIONS REQUIRING MEMORY REALLOCATION
 reserve, push_back, resize

              size: 0
          capacity: 0
  first 0 elements:

 there's been a memory reallocation
              size: 1
          capacity: 1
  first 1 elements: 11

 there's been a memory reallocation
              size: 2
          capacity: 2
  first 2 elements: 11 22

 there's been a memory reallocation
              size: 3
          capacity: 4
  first 4 elements: 11 22 33 ???

              size: 4
          capacity: 4
  first 4 elements: 11 22 33 44

 there's been a memory reallocation
              size: 5
          capacity: 8
  first 8 elements: 11 22 33 44 55 ??? ??? ???

              size: 6
          capacity: 8
  first 8 elements: 11 22 33 44 55 66 ??? ???

              size: 7
          capacity: 8
  first 8 elements: 11 22 33 44 55 66 77 ???

 there's been a memory reallocation
              size: 7
          capacity: 10
 first 10 elements: 11 22 33 44 55 66 77 ??? ??? ???

 there's been a memory reallocation
              size: 16
          capacity: 20
 first 20 elements: 11 22 33 44 55 66 77 8 8 8 8 8 8 8 8 8 ??? ??? ??? ???

 there's been a memory reallocation
              size: 24
          capacity: 40
  first 0 elements:

 there's been a memory reallocation
              size: 81
          capacity: 81
  first 0 elements:

 --------------------------------------------

 SWAP, MOVE, COPY

 v1 info...
              size: 3
          capacity: 5
  first 5 elements: 1 2 3 ??? ???

 v2 info...
              size: 4
          capacity: 6
  first 6 elements: 11 22 33 44 ??? ???

 v1 info...
              size: 4
          capacity: 6
  first 6 elements: 11 22 33 44 ??? ???

 v2 info...
              size: 3
          capacity: 5
  first 5 elements: 1 2 3 ??? ???

 v1 and v2's resources have been swapped
 v1 and v2 have been swapped back

 v1 info...
              size: 0
          capacity: 0
  first 0 elements:

 v3 info...
              size: 3
          capacity: 5
  first 5 elements: 1 2 3 ??? ???

 v3 stole v1's resources

 v1 info...
              size: 3
          capacity: 5
  first 5 elements: 1 2 3 ??? ???

 v1 stole v3's resources back

 v4 info...
              size: 3
          capacity: 3
  first 3 elements: 1 2 3

 v4 info...
              size: 4
          capacity: 4
  first 4 elements: 11 22 33 44

 self-assignment does not allocate memory
...END OF OUPUT
*/
