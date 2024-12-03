#include "Headers/commands.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>
#include <set>
#include <sstream>
#include <filesystem>
#include <unistd.h>
#include <queue>

using namespace std;

set<string> availableCommands = {"echo", "type", "exit", "pwd"};
static string CURRENT_DIRECTORY = "/app";

void invalidCommand(string& commandLine);
string checkPath(string& command);

CommandsHandler::CommandsHandler(){
    const size_t size = 1024;
    char buffer[size];
    getcwd(buffer, size);
    CURRENT_DIRECTORY = buffer;
}

void CommandsHandler::handleCommand(string& commandLine){
    regex word_regex("\\w+");
    auto firstWord = sregex_iterator(commandLine.begin(), commandLine.end(), word_regex);
    smatch match = *firstWord;
    string command = match.str();
    
    if(command == "echo"){
        string arg = commandLine.substr(5);
        CommandsHandler::echo(arg);
    }
    else if(command == "exit"){
        CommandsHandler::exitApp();
    }
    else if(command == "type"){
        string arg;
        if(commandLine.size() > command.size())
            arg = commandLine.substr(5);

        CommandsHandler::type(arg);
    }
    else if(command == "pwd"){
        printCurDirectory();
    }
    else if(command == "cd"){
        string arg;
        if(commandLine.size() > command.size())
            arg = commandLine.substr(3);
        
        if(arg[0] == '.'){
            CommandsHandler::changeDirectoryRel(arg);
        }
        else if(arg[0] == '~'){
            changeDirectoryToHome();
        }
        else{
            CommandsHandler::changeDirectoryAbs(arg);
        }
    }
    else{
        string path = checkPath(command);
            
        if(!path.empty()){
            string text;
            if(commandLine.size() > command.size())
                text = commandLine.substr(command.size() + 1);
                
            CommandsHandler::runProgram(path, text);
        }
        else{
            invalidCommand(command);
        }
    }
}

void CommandsHandler::echo(string& arg){
    cout << arg << endl;
}

void CommandsHandler::exitApp(){
    exit(0);
}

void CommandsHandler::type(string& arg){
    if(availableCommands.contains(arg)){
        cout << arg << " is a shell builtin" << endl;
    }
    else{
        string path = checkPath(arg);
        if(!path.empty()){
            cout << arg << " is " << path << endl;
        }
        else{
            cout << arg << ": not found" << endl;
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

void CommandsHandler::runProgram(string& path, string& args){
    string runCommand = "exec " + path + " " + args;
    //cout << runCommand << endl;
    system(runCommand.c_str());
}

void CommandsHandler::printCurDirectory(){
    cout << CURRENT_DIRECTORY << endl;
}

void CommandsHandler::changeDirectoryAbs(string& arg){
    if(filesystem::exists(arg)){
        CURRENT_DIRECTORY = arg;
    }
    else{
        cout << "cd: " << arg << ": No such file or directory" << endl;
    }
}

void CommandsHandler::changeDirectoryRel(string& arg){
    queue<string> pathQueue;

    int i = 0;
    string s;
    char separator = '/';
    while(arg[i] != '\0'){
        if(arg[i] != separator){
            s += arg[i];
        }
        else{
            pathQueue.push(s);
            s.clear();
        }
        ++i;
    }
    pathQueue.push(s);
    s.clear();

    string tempAbsPath = CURRENT_DIRECTORY;
    int j = 0;
    while(!pathQueue.empty()){
        string currTempPath = pathQueue.front();
        pathQueue.pop();
        //cout << currTempPath << " " << j++ << endl;

        if(currTempPath == "."){
            continue;
        }
        else if(currTempPath == ".."){
            int lastSlashIndex = tempAbsPath.rfind('/');
            tempAbsPath = tempAbsPath.substr(0, lastSlashIndex);
        }
        else if(!currTempPath.empty() && currTempPath != " " && currTempPath != "\n"){
            tempAbsPath += "/" + currTempPath; // test again (last test freezed) x2
        }
    }

    //cout << tempAbsPath << endl;
    CommandsHandler::changeDirectoryAbs(tempAbsPath);
}

void CommandsHandler::changeDirectoryToHome(){
    string home_env = getenv("HOME");
    CURRENT_DIRECTORY = home_env;
}

void invalidCommand(string& commandLine){
    cout << commandLine << ": command not found" << endl;
}