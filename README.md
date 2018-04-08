# timeitcpp

c++11, header-only implemenation of python's timeit-functionality


## timeit.h

Functionality of the standard `timeit`-module.

#### timeit-usage:

It is possible to measure time for anything "callable" for example a lambda or an struct with `operator()`, the argument can be either lvalue or rvalue. For example:

    #include <timeit.h>

    //temp lambda:
    std::cout << timeit::timeit([](){ return; }) << "\n";

    //lambda:
    auto f=[](){return 0.0;}
    std::cout << timeit::timeit([](){ return; }) << "\n";

    //temp "callable" struct-object:
    std::cout<< timeit::timeit(Callable()) <<"\n";

 
Parameter `number`, gives how many times the "callable" will be called. The resulting time is the average time for one call. For example

    #include <timeit.h>
    timeit::timeit([](){ std::cout<<"Do\n"; }, 5);

would print 5 times "Do", because `number=5`.


It is also possible to pass a `setup`-function which is called prior to the measured function, but its execution time isn't taken into the account. For example:

    #include <timeit.h>

    auto stmt = [](){std::cout<<"stmt\n";};
    auto setup = [](){std::cout<<"setup\n";};
    int number=5; //default 1
    double time=timeit::timeit(stmt, setup, number);

would output at first "setup" and then 5 times "stmt";

#### repeat-usage:

Similar to `timeit`, however multiple runs are executed and the measured times are returned in a `std::vector<double>` so they can be analyzed later on. For example:

    #include <timeit.h>

    auto stmt = [](){std::cout<<"stmt\n";};
    auto setup = [](){std::cout<<"setup\n";};
    int repeat=2;//default 3
    int number=5;//default 1
    std::vector<double> times=timeit::timeit(stmt, setup, repeat, number);


## timeitmagic.h

Functionality similar to ipython's `%timeit`-magic.

#### timeit-usage

It chooses automatically the value for `repeat` and `number` of the `timeit::repeat`-function and analyses times (choosing the minimal), returning the result of this analysis a `timeitmagic::TimeitResult`-object. For example:


    #include <timeitmagic.h>

    auto stmt = [](){std::cout<<"stmt\n";};
    auto setup = [](){std::cout<<"setup\n";};

    //choose repeat and number automatically:
    double time=timeitmagic::timeit(stmt, setup).time;

#### print-usage

Uses `timeitmagic::timeit`, formats its result and prints to `std::cout` (per default) or other stream. For example:


    #include <timeitmagic.h>

    auto stmt = [](){std::cout<<"stmt\n";};
    auto setup = [](){std::cout<<"setup\n";};

    //choose repeat and number automatically:
    timeitmagic::print(stmt, setup);

would print "Best time: 1.697e-06\n" to standard out.

## Tests

Run `test.sh` for tests (only tests that it compiles, not the results).
