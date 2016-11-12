# Distributed-Service-using-GRPC
CS 6210: Distributed Service using grpc - Project 3

===== By: Ravi Prakash Giri (GTID: 903238554) ======

# To Run:
1) go to src folder and then make
2) run vendors from test directory by  `./run_vendors ../src/vendor_addresses.txt`
3) Run store from src by `./store 0.0.0.0:50056 <num_of_threads>`  // EX. ./store 0.0.0.0:50056 12

// here You are require to give the 3 arguments to see the number of threads working. Although, I am taking server_address as an argument, but I am using the hardcoded store listening address as it was not mentioned in the description clearly. The 3rd argument is to vary the number of threads.
 Default store listening address is "0.0.0.0:50056" written hard-coded inside the run() function of server_async.cc file.

4) Then from the test directory you can run ./run_tests 0.0.0.0:50056 <n>  here the 0.0.0.0:5056 is the address at which my store is listening.


# Output: 
This is a sample output:

Query id: 33, product: mobile4 is -->  (price: 0, vendor_id: VID: Vendor_localhost:50051 -- Vendor's Price: 69) (price: 0, vendor_id: VID: Vendor_localhost:50052 -- Vendor's Price: 78) (price: 0, vendor_id: VID: Vendor_localhost:50053 -- Vendor's Price: 76) (price: 0, vendor_id: VID: Vendor_localhost:50054 -- Vendor's Price: 84) (price: 0, vendor_id: VID: Vendor_localhost:50055 -- Vendor's Price: 33)

VID: Vendor_localhost:50051 -- Vendor's Price: 69 this a result from one of the 4 vendors.
