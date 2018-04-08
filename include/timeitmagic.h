#pragma once

#include "timeit.h"

//needed for "magic"-functions
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>


namespace timeitmagic{


   //something similar to %timeit-magic
   struct TimeitResult{
     double time;
   };


   //default analysis just takes the minimal value
   struct DefaultAnalyzer{
     TimeitResult operator()(const std::vector<double> &times){
         TimeitResult result{ *std::min_element(times.begin(), times.end())};
         return result;
     }
   };

   //if repeat, number<=0, then choose them automatically
   template<typename Analyzer=DefaultAnalyzer, typename Fun1>
   TimeitResult timeit(Fun1&& stmt, int repeat=0, int number=0){
        //todo: better strategy:
        if(repeat<=0)
           repeat=3;
        if(number<=0)
           number=1;
        Analyzer an;
        return an(timeit::repeat(stmt, repeat, number));
   }
  

   //if repeat, number<=0, then choose them automatically
   template<typename Analyzer=DefaultAnalyzer, typename Fun1, typename Fun2>
   TimeitResult timeit(Fun1&& stmt, Fun2&& setup, int repeat=0, int number=0){
        //todo: better strategy:
        if(repeat<=0)
           repeat=3;
        if(number<=0)
           number=1;
        Analyzer an;
        return an(timeit::repeat(stmt, setup, repeat, number));
   }



   //convience functions
   struct DefaultFormatter{
        std::string operator()(const TimeitResult &result){
            std::stringstream ss;
            ss<<"Best time: "<<result.time<<"\n";
            return ss.str();
        }
   };
   
   
   template<typename Formatter=DefaultFormatter, typename Analyzer=DefaultAnalyzer, typename Fun1>
   TimeitResult print(Fun1&& stmt, int repeat=0, int number=0, std::ostream &stream=std::cout){
        TimeitResult result=timeitmagic::timeit<Analyzer>(stmt, repeat, number);
        Formatter form;
        stream<<form(result);
        return result;
   }


   template<typename Formatter=DefaultFormatter, typename Analyzer=DefaultAnalyzer, typename Fun1, typename Fun2>
   TimeitResult print(Fun1&& stmt, Fun2&& setup, int repeat=0, int number=0, std::ostream &stream=std::cout){
        TimeitResult result=timeitmagic::timeit<Analyzer>(stmt, setup, repeat, number);
        Formatter form;
        stream<<form(result);
        return result;
   }
}
