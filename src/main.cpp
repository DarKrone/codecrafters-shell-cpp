#include <iostream>
#include "Headers/commands.hpp"

using namespace std;

int main() {
  // Flush after every std::cout / std:cerr
  cout << std::unitbuf;
  cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  cout << "$ ";

  CommandsHandler handler = CommandsHandler();

  string input;
  getline(cin, input);

  handler.handleCommand(input);
}
