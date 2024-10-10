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

vector<int> buffer;
int buffer_size = 0;

void print_buffer(vector<int>&  buffer) {
  cout << "The buffer_size is: " << buffer_size << endl;
  cout << "The buffer.size() is: " <<  int(buffer.size()) << endl;
  cout << "The buffer contains: " << endl;
  for (int i = 0; i < int(buffer.size()); i++) {
    cout << buffer.at(i) << "\n";
  }
}


string logged(bool process) {
  if (process) {
    return "Succeded";
  } else {
    return "Failed";
  }
}

// string bounded_prompt () {

// }


void remove(vector<int>&  buffer) {

  if (int(buffer.size()) != 0) {
    buffer.erase(buffer.begin());
    for (int i = 0; i < int(buffer.size()); i++) {
      buffer[i] = buffer[i+1];
    }
    logged(true);
  } else {
    logged(false);
  }
}

void add(vector<int>&  buffer) {
  int element;
  cout << "What do you wish to add to the buffer:" << endl;
  cin >> element;
  if (int(buffer.size()) < buffer_size) {
    buffer.push_back(element);
    buffer_size++;
    logged(true);
  } else {
    // return logged(false);
    print_buffer(buffer);
  }
}

void bounded_operation(vector<int>&  buffer) {
  int option = 0;

  cout << "1. Add" << endl;
  cout << "2. Remove" << endl;
  cout << "3. Exit" << endl;
  cout << "Please choose a number: ";
  cin >> option;

  while(option != 3) {
    switch (option)
    {
      case 1:
        add(buffer);
        break;
      case 2:
        remove(buffer);
        break;
    }
  }
  print_buffer(buffer);
}

void bounded() {
  int buffer_size;
  cout << "How large should the buffer be?:" << endl;
  cin >> buffer_size;
  bounded_operation(buffer);
}

void unbounded() {
  
}

int main(int argc, char* argv[]) {
  cout << "Do you want an unbounded or bounded buffer? :" << endl;
  int option = 0;

  cout << "1. Bounded" << endl;
  cout << "2. Unbouded" << endl;
  cout << "Please choose a number: ";
  cin >> option;
  
  switch (option)
  {
    case 1:
      bounded();
      break;
    case 2:
      unbounded();
      break;
  }
  return 0;
}
