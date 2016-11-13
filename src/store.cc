#include "threadpool.h"
#include "server_async.cc"
#include <chrono>
#include <iostream>

class store1 { 

};

int main(int argc, char** argv) {
	//std::cout << "I 'm not ready yet!" << std::endl;
	//std::string random = "book1";
	//run_server();

  //using nbsdx::concurrent::ThreadPool;

  unsigned num_max_threads;
  std::string server_addr;
  if (argc == 3) {
    server_addr = std::string(argv[1]);
    num_max_threads = std::min( 20, std::max(0,atoi(argv[2])));
  }
  else if (argc == 2) {
    server_addr = std::string(argv[1]);
    num_max_threads = 4;
  }
  else {
    server_addr = "0.0.0.0:50056"; // no need
    num_max_threads = 4;
  }
  	//std::string serv_ad = server_addr;
    //constexpr unsigned n = num_max_threads;
    ThreadPool pool(num_max_threads); // Defaults to 10 threads.
   // int JOB_COUNT = 100;
    pool.AddJob( &run_server);

    pool.JoinAll();
    std::cout << "Expected runtime: 10 seconds." << std::endl;

	return EXIT_SUCCESS;
}


