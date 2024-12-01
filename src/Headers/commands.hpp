#include <string>

class CommandsHandler{
    public:
        void handleCommand(std::string command);
        void echo();
        void cd();
        void exitApp();
};