#include <string>

class CommandsHandler{
    public:
        CommandsHandler();
        void handleCommand(std::string& command);
        void echo(std::string& arg);
        void exitApp();
        void printCurDirectory();
        void runProgram(std::string& path, std::string& args);
        void changeDirectoryAbs(std::string& arg);
        void changeDirectoryRel(std::string& arg);
        void changeDirectoryToHome();
        void type(std::string& arg);
};