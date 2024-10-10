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

// although it is good habit, you don't have to type 'std::' before many objects by including this line
using namespace std;

vector<int> buffer;
vector<string> logger;
int buffer_size = 0;

void print_buffer(vector<int>&  buffer) {
  cout << "The buffer_size is: " << buffer_size << endl;
  cout << "The buffer.size() is: " <<  int(buffer.size()) << endl;
  cout << "The buffer contains: " << endl;
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


// void remove(vector<int>&  buffer) {

//   if (int(buffer.size()) != 0) {
//     buffer.erase(buffer.begin());
//     for (int i = 0; i < int(buffer.size()); i++) {
//       buffer[i] = buffer[i+1];
//     }
//     logged(true);
//   } else {
//     logged(false);
//   }
// }

// void add(vector<int>&  buffer) {
//   int element;
//   cout << "What do you wish to add to the buffer:" << endl;
//   cin >> element;
//   if (int(buffer.size()) < buffer_size) {
//     buffer.push_back(element);
//     // print_buffer(buffer);
//     cout << "Entered: " << element << endl;
//     print_buffer(buffer);
//   } else {
//     // return logged(false);
//     cout << "Out of bounds" << endl;
//     print_buffer(buffer);
//   }
// }

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
      if (int(buffer.size()) < buffer_size) {
        // Add element to buffer
        buffer.push_back(element);
        cout << "Entered: " << element << endl;
        // Add operation to loggere
        logger.push_back("Success");
        // Call for next prompt
        bounded_operation(buffer,logger);
      } else {
        cout << "Out of bounds" << endl;
        logger.push_back("Failure");
        bounded_operation(buffer,logger);
      }
      break;
    case 2:
      if (int(buffer.size()) != 0) {
        buffer.erase(buffer.begin());
        logger.push_back("Success");
        bounded_operation(buffer, logger);
      } else {
        cout << "The buffer is empty: " << endl;
        logger.push_back("Failure");
        bounded_operation(buffer, logger);
      }
      break;
    case 3:
      print_buffer(buffer);
      break;
  }
  // while(option != 3) {
  //   prompt_operation(buffer);
  // }
}

void bounded() {
  cout << "How large should the buffer be?:" << endl;
  cin >> buffer_size;
  bounded_operation(buffer,logger);
}

void unbounded() {
  
}

int main(int argc, char* argv[]) {
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
      unbounded();
      break;
  }
  return 0;
}
