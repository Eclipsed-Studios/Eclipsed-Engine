#include "Client.h"

#include "NetworkEngine/Shared/Message.h"

#include <iostream>

namespace Eclipse
{
	void Client::HandleRecieve(const NetMessage& message)
	{
		HandleRecieveFunc(message);
	}
}