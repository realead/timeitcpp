
#include <iostream>
#include <vector>
#include "timeit.h"


struct Callable{
  int i=0;
  int operator()(){
    i++;
    return i;
  }
};


int main(){
   std::vector<double> vec(2000, 1.1);
   auto f=[&vec](){
                     for(auto &v : vec)
                         v*=v;
                   };

   //can be used without const:
   std::cout<<"Time: "
            << timeit::timeit(f,2)
            <<"\n";
   std::cout<<"Time 10: "
            << timeit::timeit(f,10)
            <<"\n";


   //must use const, because it is a rvalue.
   std::cout<<"Time2: "
            << timeit::timeit([](){ return; },3)
            <<"\n";

   
   Callable c;
   std::cout<<"Callable time:"
            <<timeit::timeit(c, 24)
            <<"\n";

}
