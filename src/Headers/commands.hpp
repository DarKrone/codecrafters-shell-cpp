#include <string>

class CommandsHandler{
    public:
        CommandsHandler();
        void handleCommand(std::string& command);
        void echo(std::string& arg);
        void exitApp();
        void printCurDirectory();
        void runProgram(std::string& path, std::string& args);
        void changeDirectory(std::string& arg);
        void type(std::string& arg);
};