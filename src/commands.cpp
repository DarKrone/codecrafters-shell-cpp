#include "Headers/commands.hpp"
#include <string>
#include <iostream>

using namespace std;

void invalidCommand(string command);

void CommandsHandler::handleCommand(string command){
    if(command == "echo"){
        CommandsHandler::echo();
    }
    else if(command == "cd"){
        CommandsHandler::cd();
    }
    else{
        invalidCommand(command);
    }
}

void CommandsHandler::echo(){
    return;
}

void CommandsHandler::cd(){
    return;
}

void invalidCommand(string command){
    cout << command << ": command not found";
}