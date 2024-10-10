/**
  * Assignment: synchronization
  * Operating Systems
  */

/**
  Hint: F2 (or Control-klik) on a functionname to jump to the definition
  Hint: Ctrl-space to auto complete a functionname/variable.
  */

// function/class definitions you are going to use
#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// although it is good habit, you don't have to type 'std::' before many objects by including this line
using namespace std;

//should the buf and log be global?
vector<int> buf;
vector<string> log;
int SIZE;
bool unbounded_buffer = false;
int buf_index = 0;
int log_index = 0;

void createBoundedBuffer(int size){
  SIZE=size;
  write_log("Create-bounded buffer-op: successful");
}

void createUnboundedBuferr(){
  unbounded_buffer = true;
  write_log("Create-unbounded buffer-op: successful");
}

void addElement(int i){
  if(unbounded_buffer || buf_index < SIZE){
    buf.push_back(i);
    write_log("Add-op: successful");
    buf_index++;
  } else {
    write_log("Add-op: failure");
  }
}

void removeElement(){
  if(buf.size() > 0){
    buf_index--;
    buf.erase(buf.begin());
    write_log("Remove-op: successful");
  } else {
    write_log("Remove-op: failure");
  }
}

void write_log(string s){
  log.push_back(s);
  log_index++;
}

string read_log(int index){
  if(index >= 0 && index < log.size()){
    write_log("Read_log-op: succesful");
    return log[index];
  } else {
    write_log("Read_log-op: failure");
    return;
  }
}

int main(int argc, char* argv[]) {
	return 0;
}
