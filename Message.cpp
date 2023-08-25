#include "Message.h"

Message::Message(const char* message)
{
	this->message = message;
}

char* Message::encrypt()
{
	char* result = new char[this->message.size()];
	for(unsigned int i = 0; i < this->message.size();i++)
	{
		result[i] = this->message[i] + 1; 
	}
	return result;
}
