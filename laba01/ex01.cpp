#include <iostream>
#include <string>
#include <thread>


//========================1

// void    hello() {
//     std::cout << "Hello, parallel world!\n";
// }

// int main(void)
// {
//     std::thread th(hello);

//     th.join();
//     return 0;
// }

//========================2
// void    hello() {
//     std::cout << "Hello, parallel world!\n";
// }

// int main(void)
// {
//     std::thread th(hello);

//     return 0;
// }


//========================3
// void    hello(const std::string & first, const std::string & second) {
//     std::cout << first << " " << second << "\n";
// }

// int main(void)
// {
//     std::thread th(hello, "Hello,", "threads!");

//     th.join();
//     return 0;
// }

//========================4
std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread() {
  if ( main_thread_id == std::this_thread::get_id() )
    std::cout << "This is the main thread.\n";
  else
    std::cout << "This is not the main thread.\n";
}

// void    hello(const std::string & first, const std::string & second) {
//     is_main_thread();
//     std::cout << first << " " << second << "\n";
// }

// int main(void)
// {
//     std::thread th(hello, "Hello,", "threads!");

//     is_main_thread();
//     th.join();
//     return 0;
// }

//========================5
void    hello() {
    if (std::this_thread::get_id() == main_thread_id) {
        std::cout << "Hello, main threads!\n";
        return;
    } 
    std::cout << "Hello, " <<  std::this_thread::get_id() << " threads!\n";
}

int main(void)
{
    std::thread th1(hello);
    std::thread th2(hello);

    hello();
    th1.join();
    th2.join();
    return 0;
}
