#include "Headers/commands.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>

using namespace std;

void invalidCommand(string commandLine);

void CommandsHandler::handleCommand(string commandLine){
    regex word_regex("\\w+");
    auto firstWord = sregex_iterator(commandLine.begin(), commandLine.end(), word_regex);
    smatch match = *firstWord;
    string command = match.str();
    
    if(command == "echo"){
        string text = commandLine.substr(5);
        CommandsHandler::echo(text);
    }
    else if(command == "cd"){
        CommandsHandler::cd();
    }
    else if(command == "exit"){
        CommandsHandler::exitApp();
    }
    else{
        invalidCommand(command);
    }
}

void CommandsHandler::echo(string text){
    cout << text << endl;
}

void CommandsHandler::cd(){
    return;
}

void CommandsHandler::exitApp(){
    exit(0);
}

void invalidCommand(string commandLine){
    cout << commandLine << ": command not found" << endl;
}