#include "Networking/Client/Client.h"

#include "Networking/Shared/Message.h"

namespace Eclipse
{
	void Client::HandleRecieve(const NetMessage& message)
	{
		HandleRecieveFunc(message);
	}
}