#include <iostream>
#include <string>
class Message
{
public:
Message(const char* message);
char* encrypt();
private:
std::string message;
};
