// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "RPCproxy.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
#include "cache.h"
#include "doc_fetch.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using namespace std;
using namespace  ::Test;





static int miss_count_ind=0;
static int miss_count_byte=0;
class RPCproxyHandler : virtual public RPCproxyIf {
 public:
  RPCproxyHandler() {
    // Your initialization goes here
  }
  typedef string (*fetch)(string);
  fetch fetch_array[8]={fetch_data_GD1,fetch_data_GDF,fetch_data_MAXS,fetch_data_fifo,fetch_data_lfu,fetch_data_lru,fetch_data_lru_min,fetch_data_random};

  typedef void (*update)(string,string,int);
  update update_array[8]={update_cache_GD1,update_cache_GDF,update_cache_MAXS,update_cache_fifo,update_cache_lfu,update_cache_lru,update_cache_lru_min,update_cache_random};

  int *mc_array[8]={&mc_GD1,&mc_GDF,&mc_MAXS,&mc_fifo,&mc_lfu,&mc_lru,&mc_lru_min,&mc_random};
  int *mcb_array[8]={&mcb_GD1,&mcb_GDF,&mcb_MAXS,&mcb_fifo,&mcb_lfu,&mcb_lru,&mcb_lru_min,&mcb_random};

  void ping(std::string& _return, const std::string& URL) {
    // Your implementation goes here
    // Your implementation goes here

  time_stamp++;
  string f_return;

  //function pointers for fetch and update functions of all cache types
  
  

  int miss_indicator_array[8]={0};
  int found_in_one=0;
  string temp_result;
  //check for misses in all cache types
  for(int i=0;i<8;i++)
  {
	temp_result=fetch_array[i](URL);
	if(temp_result=="empty")
	{
		*(mc_array[i])=*(mc_array[i])+1;
		miss_indicator_array[i]=1;
	}
	else
	{
		*(mcb_array[i])=*(mcb_array[i])+temp_result.length();
		if(!found_in_one)
		{
			found_in_one=1;
			f_return=temp_result;
		}
	}
  }
  //if not present in any cache type, use curl to fetch the data
  if(!found_in_one)
  {
	f_return = fetch_doc(URL);
	//cout<<"data not found in any cache "<<endl;
  }
  else
  {
	//cout<<"data found in atleast one cache "<<endl;
  }
  // update all caches where data is not found
  for(int i=0;i<8;i++)
  {
	if(miss_indicator_array[i])
		{
			
			//cout<<"updating "<<i<<endl;
			update_array[i](URL, f_return, f_return.length());
		}
  }
  _return = f_return;

}

  


  int32_t miss_count() {
    // Your implementation goes here
    
    
    if(miss_count_ind==7)
	{
		int temp=*(mc_array[miss_count_ind]);
		miss_count_ind=0;
		clear_everything();
		return (temp);
	}
    else
    	return *(mc_array[miss_count_ind++]);
  }


    int32_t byte_count() {
    // Your implementation goes here
    if(miss_count_byte==7)
	{
		int temp=*(mcb_array[miss_count_byte]);
		miss_count_byte=0;
		return (temp);
	}
    else
    	return *(mcb_array[miss_count_byte++]);
  }

    void kill_server() {
    // Your implementation goes here
    exit(0);
  }




};

int main(int argc, char **argv) {
  int port = 9090;
    if(argc==2)
	{	
		C_SIZE=atoi(argv[1])*1024;
	}
  else
	{
		C_SIZE=1024*1024;
	}
  boost::shared_ptr<RPCproxyHandler> handler(new RPCproxyHandler());
  boost::shared_ptr<TProcessor> processor(new RPCproxyProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

