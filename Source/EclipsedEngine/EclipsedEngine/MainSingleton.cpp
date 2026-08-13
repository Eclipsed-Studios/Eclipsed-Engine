//#include "MainSingleton.h"
//
//namespace Eclipse
//{
//	void MainSingleton::Destroy()
//	{
//		for (auto& [type, singleton] : mySingletons)
//		{
//			if (!singleton.useDestructor) continue;
//			singleton.deleter(singleton.instance);
//		}
//	}
//}