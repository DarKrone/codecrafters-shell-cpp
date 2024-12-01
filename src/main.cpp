#include <iostream>
#include <string>
#include "Headers/commands.hpp"

using namespace std;

int main() {
  // Flush after every std::cout / std:cerr
  cout << std::unitbuf;
  cerr << std::unitbuf;

  // Uncomment this block to pass the first stage

  CommandsHandler handler = CommandsHandler();

  string input;
  while(true){
    cout << "$ ";
    getline(cin, input);
    handler.handleCommand(input);
  }
}
