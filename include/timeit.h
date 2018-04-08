#include <chrono>
#include <vector>

//needed for "magic"-functions
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>


namespace timeit{
    

    //returns time needed for one execution in seconds:
    template<typename Fun1>
    double timeit(Fun1&& stmt, int number_of_executions=1)
    {  
       auto begin = std::chrono::high_resolution_clock::now();
       for(int i=0;i<number_of_executions;i++){
          stmt();
       }
       auto end = std::chrono::high_resolution_clock::now();
       return std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9/number_of_executions;
    }

    template<typename Fun1, typename Fun2>
    double timeit(Fun1&& stmt, Fun2&& setup, int number_of_executions=1)
    {  
       setup();
       return timeit(stmt,number_of_executions);
    }


    //make multiple runs:
    template<typename Fun1>
    std::vector<double> repeat(Fun1&& stmt, int repeat=3, int number=1){
       std::vector<double> res;
       for(int i=0;i<repeat;i++){
           res.push_back(timeit(stmt, number));
       }
       return res;
    }

    template<typename Fun1,  typename Fun2>
    std::vector<double> repeat(Fun1&& stmt, Fun2&& setup, int repeat=3, int number=1){
       std::vector<double> res;
       for(int i=0;i<repeat;i++){
           res.push_back(timeit(stmt, setup, number));
       }
       return res;
    }


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
   TimeitResult magic(Fun1&& stmt, int repeat=0, int number=0){
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
   TimeitResult magic(Fun1&& stmt, Fun2&& setup, int repeat=0, int number=0){
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
   TimeitResult print_magic(Fun1&& stmt, int repeat=0, int number=0, std::ostream &stream=std::cout){
        TimeitResult result=timeit::magic<Analyzer>(stmt, repeat, number);
        Formatter form;
        stream<<form(result);
        return result;
   }


   template<typename Formatter=DefaultFormatter, typename Analyzer=DefaultAnalyzer, typename Fun1, typename Fun2>
   TimeitResult print_magic(Fun1&& stmt, Fun2&& setup, int repeat=0, int number=0, std::ostream &stream=std::cout){
        TimeitResult result=timeit::magic<Analyzer>(stmt, setup, repeat, number);
        Formatter form;
        stream<<form(result);
        return result;
   }
}
