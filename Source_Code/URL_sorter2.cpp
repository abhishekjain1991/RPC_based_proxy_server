    // This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <curl/curl.h>
#include <random>



using namespace std;




int main(int argc, char **argv) {

  default_random_engine generator;
  binomial_distribution<int> distribution_bi(124,0.5);
  binomial_distribution<int> distribution_bi2(124,0.9);
  ifstream myReadFile;
  myReadFile.open("url.txt");
  string data;
  int all_data_length=0;
  char output[100];
  vector<string> URL_list;
  multimap<int,string> finaldata;
  int i = 0;

  if (myReadFile.is_open()) {
	while (!myReadFile.eof()) 
		{
			myReadFile >> output;
			cout<<"inserting "<<i++<<endl;
			URL_list.push_back(string(output));
		}
	}
  myReadFile.close();
  ofstream myfile;
  myfile.open ("Payload2.txt");


for(int i=0;i<100;i++)
{
	int j=0;
//	if(i%2)
//	{
	for(j=0;j<3;j++)
		myfile<<URL_list[distribution_bi(generator)]<<endl;
	for(j=2;j<5;j++)
		myfile<<URL_list[distribution_bi2(generator)]<<endl;
//	}
//	else
//	{
//	for(j=0;j<3;j++)
//		myfile<<URL_list[distribution_bi(generator)]<<endl;
//	for(j=3;j<5;j++)
//		myfile<<URL_list[distribution_bi(generator)]<<endl;
//	}
}

myfile.close();





  return 0;
}
