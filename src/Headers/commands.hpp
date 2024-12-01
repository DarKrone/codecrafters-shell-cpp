#include <string>

class CommandsHandler{
    public:
        CommandsHandler();
        void handleCommand(std::string& command);
        void echo(std::string& arg);
        void cd();
        void exitApp();
        void printCurDirectory();
        void changeDirectory(string& arg);
        void type(std::string& arg);
};