#include <chrono>


namespace timeit{
    

    //returns time needed for one execution in seconds
    template<typename Fun1>
    double timeit(Fun1&& f, int number_of_executions=1)
    {  
       auto begin = std::chrono::high_resolution_clock::now();
       for(int i=0;i<number_of_executions;i++){
          f();
       }
       auto end = std::chrono::high_resolution_clock::now();
       return std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9/number_of_executions;
    }
}
