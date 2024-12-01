#include "Headers/commands.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>

using namespace std;

void invalidCommand(string command);

void CommandsHandler::handleCommand(string command){
    regex word_regex("\\w+");

    auto firstWord = sregex_iterator(command.begin(), command.end(), word_regex);
    smatch match = *firstWord;
    string firstWordStr = match.str();

    if(firstWordStr == "echo"){
        CommandsHandler::echo();
    }
    else if(firstWordStr == "cd"){
        CommandsHandler::cd();
    }
    else if(firstWordStr == "exit"){
        CommandsHandler::exitApp();
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

void CommandsHandler::exitApp(){
    exit(0);
}

void invalidCommand(string command){
    cout << command << ": command not found" << endl;
}