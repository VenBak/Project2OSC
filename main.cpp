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
#include <ostream>
#include <thread>
#include <vector>
#include <unistd.h>

// although it is good habit, you don't have to type 'std::' before many objects by including this line
using namespace std;

vector<int> buffer;
vector<string> logger;
int buffer_size = 0;
mutex printbuf_and_log;
mutex add_el, remove_el;

void print_buffer(vector<int>&  buffer) {
  cout << "The buffer_size is: " << buffer_size << endl;
  cout << "The buffer.size() is: " <<  int(buffer.size()) << endl;
  cout << "The buffer contains: " << endl;
  printbuf_and_log.lock();
  for (int i = 0; i < int(buffer.size()); i++) {
    cout << i << ": " << buffer.at(i) << endl;
    if (int(buffer.size()) == 0) {
      cout << "The buffer is empty" << endl;
    }
  }
  cout << "The logger contains: " << endl;
  for (int i = 0; i < int(logger.size()); i++) {
    cout << i << ": " << logger.at(i) << endl;
    if (int(logger.size()) == 0) {
      cout << "Nothing was logged" << endl;
    }
  }
  printbuf_and_log.unlock();

}


void log(string process_name, bool process) {
  string s = "";
  if (process) {
    s = process_name + "Succeeded";
    logger.push_back(s);
  } else {
    s = process_name + "Failed";
    logger.push_back(s);
  }
}

void unrestricted_addition(vector<int>& buffer, int& element) { 
  add_el.lock();
  int prev_size;
  prev_size = buffer.size();
  // Add element to buffer
  buffer.push_back(element);
  cout << "Entered: " << element << endl;
  ((prev_size + 1) != (int)buffer.size()) ? log("Addition: ", false) : log("Addition: ", true);
  add_el.unlock();
}

void restricted_addition(vector<int>& buffer, int& element) {
  add_el.lock();
  if (int(buffer.size()) < buffer_size) {
    // Add element to buffer
    buffer.push_back(element);
    cout << "Entered: " << element << endl;
    log("Addition:", true);
  } else {
    cout << "Out of bounds" << endl;
    log("Addition", false);
  }
  add_el.unlock();
}

void remove(vector<int>& buffer) {
  remove_el.lock();
  if (int(buffer.size()) != 0) {
    buffer.erase(buffer.begin());
  } else {
    cout << "The buffer is empty: " << endl;
  }
  (int(buffer.size()) != 0) ? log("Remove:", true) : log("Remove", false);
  remove_el.unlock();
}

void bounded_operation(vector<int>&  buffer, vector<string>&  logger) {
  int option = 0;

  cout << "Which operation do you which to perform: " << endl;
  cout << "1. Add" << endl;
  cout << "2. Remove" << endl;
  cout << "3. Exit" << endl;
  cin >> option;
  switch (option)
  {
    case 1:
      int element;
      cout << "What do you wish to add to the buffer:" << endl;
      cin >> element;
      restricted_addition(buffer, element);
      // Call for next prompt
      bounded_operation(buffer, logger);
      break;
    case 2:
      remove(buffer);
      bounded_operation(buffer, logger);
      break;
    case 3:
      print_buffer(buffer);
      break;
  }
}

void bounded() {
  cout << "How large should the buffer be?:" << endl;
  cin >> buffer_size;
  cout << "buffer size is:" << buffer_size << endl;
  bounded_operation(buffer,logger);
}

void unbounded_operation() {
  int option = 0;

  cout << "Which operation do you which to perform: " << endl;
  cout << "1. Add" << endl;
  cout << "2. Remove" << endl;
  cout << "3. Exit" << endl;
  cin >> option;
  switch (option)
  {
    case 1:
      int element;
      cout << "What do you wish to add to the buffer:" << endl;
      cin >> element;
      unrestricted_addition(buffer, element);
      // Call for next prompt
      unbounded_operation();
      break;
    case 2:
      remove(buffer);
      // Call for next prompt
      unbounded_operation();
      break;
    case 3:
      print_buffer(buffer);
      break;
  }
}

void default_functionality() {
  cout << "Do you want an unbounded or bounded buffer? :" << endl;
  int option = 0;
  cout << "Please choose a number: " << endl;
  cout << "1. Bounded" << endl;
  cout << "2. Unbouded" << endl;
  cin >> option;
  
  switch (option)
  {
    case 1:
      bounded();
      break;
    case 2:
      unbounded_operation();
      break;
  }
}

void thread_logging(string thread_name, string function_name){
  cout << thread_name << ": " << function_name << endl;
}

void first_thread(string tn) {
  thread_logging(tn, "Addition");
  int nr = 8;
  restricted_addition(buffer, nr);
  sleep(5);
  thread_logging(tn, "Addition");
  nr = 9;
  restricted_addition(buffer, nr);
  thread_logging(tn, "Addition");
  nr = 487548725;
  restricted_addition(buffer, nr);
}

void second_thread(string tn) {
  thread_logging(tn, "Addition");
  int nr = 7;
  restricted_addition(buffer, nr);
  thread_logging(tn, "Remove");
  remove(buffer);
  thread_logging(tn, "Remove");
  remove(buffer);
  thread_logging(tn, "Addition");
  nr = 76;
  restricted_addition(buffer, nr);
}

void test1(int test_size) {
  buffer_size = test_size;
  cout << "Test1: buffer size is:" << buffer_size << endl;
  cout << "Test1: thread 1 is called" << endl;
  thread t1(first_thread, "First_thread");
  cout << "Test1: thread 2 is called" << endl;
  thread t2(second_thread, "Second_thread");
  cout << "Test1: wait for threads to finish" << endl;
  t1.join();
  t2.join();
  cout << "Test1: threads are finished" << endl;
}

int main(int argc, char* argv[]) {
  test1(5);
  return 0;
}
