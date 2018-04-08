
#include <iostream>
#include <vector>
#include <string>

#include "timeit.h"


struct Callable{
  int i=0;
  int operator()(){
    i++;
    return i;
  }
};


void print_vector(const std::vector<double> &vec, const std::string &label){
   std::cout<<label<<":";
   for(const auto &v : vec){
      std::cout<<" "<<v;
   }
   std::cout<<"\n";
}

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
   std::cout<<"Callable time: "
            <<timeit::timeit(c, 24)
            <<"\n";


   //with setup:
   std::cout<<"Callable time with setup: "
            <<timeit::timeit(c, [](){std::cout<<"setup...\n";}, 10)
            <<"\n";

   std::cout<<"Rvalue time with setup: "
            <<timeit::timeit([](){return 1.0;}, [](){std::cout<<"setup...\n";}, 9)
            <<"\n";


   //repeat:
   print_vector(timeit::repeat(c,5,3), "repeat callable, no setup");
   print_vector(timeit::repeat([](){return 1.0;},c,5,3), "repeat temp lambda, callable setup");
   print_vector(timeit::repeat(f, [](){return 1.0;},5,3), "repeat lambda, temp lambda setup");


   //magic:
   std::cout<<"magic callable, no setup "<<timeit::magic(c).time<<"\n";
   std::cout<<"magic temp lambda, callable setup "<<timeit::magic([](){return 1.0;},c).time<<"\n";
   std::cout<<"magic lambda, temp lambda setup "<<timeit::magic(f, [](){return "";}).time<<"\n";


   //print magic:
   timeit::print_magic([](){return 1.0;});
   timeit::print_magic([](){return 1.0;},c);
   timeit::print_magic(f, [](){return "";});
}
