#include "Message.h"

string Message::getMessage() const {
	return sender + ": " + text;
}

string Message::getRecipient() const { return recipient; }

string Message::getSender() const { return sender; }