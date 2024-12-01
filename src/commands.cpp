#include "Headers/commands.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>
#include <set>

using namespace std;

set<string> availableCommands = {"echo", "type", "exit"};

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
    else if(command == "type"){
        string text = commandLine.substr(5);
        CommandsHandler::type(text);
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

void CommandsHandler::type(string text){
    if(availableCommands.contains(text)){
        cout << text << " is a shell builtin" << endl;
    }
    else{
        cout << text << ": not found" << endl;
    }
}

void invalidCommand(string commandLine){
    cout << commandLine << ": command not found" << endl;
}