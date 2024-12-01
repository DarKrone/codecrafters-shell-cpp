#include <string>

class CommandsHandler{
    public:
        void handleCommand(std::string& command);
        void echo(std::string& text);
        void cd();
        void exitApp();
        void type(std::string& text);
};