#include "Headers/commands.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>
#include <set>
#include <sstream>
#include <filesystem>
#include <unistd.h>

using namespace std;

set<string> availableCommands = {"echo", "type", "exit", "pwd"};

void invalidCommand(string& commandLine);
string checkPath(string& command);
void runProgram(string& path ,string& args);

void CommandsHandler::handleCommand(string& commandLine){
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
        string text;
        if(commandLine.size() > command.size())
            text = commandLine.substr(5);

        CommandsHandler::type(text);
    }
    else if(command == "pwd"){
        printCurDirectory();
    }
    else{
        string path = checkPath(command);
            
        if(!path.empty()){
            string text;
            if(commandLine.size() > command.size())
                text = commandLine.substr(command.size() + 1);
                
            runProgram(path, text);
        }
        else{
            invalidCommand(command);
        }
    }
}

void CommandsHandler::echo(string& text){
    cout << text << endl;
}

void CommandsHandler::cd(){
    return;
}

void CommandsHandler::exitApp(){
    exit(0);
}

void CommandsHandler::type(string& text){
    if(availableCommands.contains(text)){
        cout << text << " is a shell builtin" << endl;
    }
    else{
        string path = checkPath(text);
        if(!path.empty()){
            cout << text << " is " << path << endl;
        }
        else{
            cout << text << ": not found" << endl;
        }
    }
}

string checkPath(string& command){
    string path_env = getenv("PATH");
    stringstream ss(path_env);
    string path;

    while(!ss.eof()){
        getline(ss, path, ':');

        string full_path = path + '/' + command;

        if(filesystem::exists(full_path)){
            return full_path;
        }
    }
    return "";
}

void runProgram(string& path, string& args){
    string runCommand = "exec " + path + " " + args;
    //cout << runCommand << endl;
    system(runCommand.c_str());
}

void CommandsHandler::printCurDirectory(){
    const size_t size = 1024;
    char buffer[size];
    getcwd(buffer, size);
    cout << buffer << endl;
}

void invalidCommand(string& commandLine){
    cout << commandLine << ": command not found" << endl;
}