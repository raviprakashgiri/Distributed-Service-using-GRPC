/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "vendor.grpc.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using vendor::BidQuery;
using vendor::BidReply;
using vendor::Vendor;

class VendorClient {
 public:
  explicit VendorClient(std::shared_ptr<Channel> channel): stub_(Vendor::NewStub(channel)) {}

  std::string get_details(const std::string& user) {
    // Data we are sending to the server.
    BidQuery request;
    request.set_product_name(user);
    BidReply reply;

    ClientContext context;

    CompletionQueue cq;

    Status status;

    std::unique_ptr<ClientAsyncResponseReader<BidReply> > rpc(
        stub_->AsyncgetProductBid(&context, request, &cq));

    rpc->Finish(&reply, &status, (void*)1);
    void* got_tag;
    bool ok = false;
   
    GPR_ASSERT(cq.Next(&got_tag, &ok));

    GPR_ASSERT(got_tag == (void*)1);
  
    GPR_ASSERT(ok);

    // Act upon the status of the actual RPC.
    if (status.ok()) 
    {
      std::ostringstream price_str;
      price_str << reply.price();
      return "VID: "+reply.vendor_id()+" -- "+"Vendor's Price: "+price_str.str();
    } else {
      return "RPC failed";
    }
  }

 private:
  
  std::unique_ptr<Vendor::Stub> stub_;
};

std::string run_client(std::string user, std::string ip_addresses) {
  
  VendorClient vendor_(grpc::CreateChannel(
      ip_addresses, grpc::InsecureChannelCredentials()));
  
  std::string reply = vendor_.get_details(user);  // The actual RPC call!
  std::cout << "Reply received: " << reply << std::endl;

 return reply;
}
