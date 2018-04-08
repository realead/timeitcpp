#include <chrono>
#include <vector>


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
}
