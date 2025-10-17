#pragma once

#include "Utilities/ChatGPT_Dump/Base64.hpp"

#include "Utilities/Common/MainSingleton.h"
#include "Utilities/Common/Timer.h"


#include "Utilities/Containers/BitMask.hpp"
#include "Utilities/Containers/RingBuffer.h"


#include "Utilities/Debug/Output/DebugLogBuffer.h"
#include "Utilities/Debug/Output/DebugLogger.h"

#include "Utilities/Debug/Profiling/DebugInformationCollector.h"


#include "Utilities/Files/DirectoryTree.h"
#include "Utilities/Files/FileInfo.h"
#include "Utilities/Files/FileWatcher.h"


#include "Utilities/Macros/defines.h"

#include "Utilities/Math/Color.h"
#include "Utilities/Math/CommonMath.h"
#include "Utilities/Math/Random.h"
#include "Utilities/Math/Rect.h"
#include "Utilities/Math/RectSizePos.h"
#include "Utilities/Math/Vector/Vector2.h"
#include "Utilities/Math/Vector/Vector3.h"
#include "Utilities/Math/Vector/Vector4.h"


#include "Utilities/PlatformIntegration/DiscordIntegration.h"
#include "Utilities/PlatformIntegration/IntegrationManager.h"


#include "Utilities/Reflection/AbstractSerializedVariable.h"
#include "Utilities/Reflection/Reflection.h"
#include "Utilities/Reflection/ReflectionTypeChecks.h"
#include "Utilities/Reflection/SerializedEnum.hpp"
#include "Utilities/Reflection/SerializedVariable.h"
#include "Utilities/Reflection/Registry/ComponentRegistry.h"
#include "Utilities/Reflection/Registry/WindowRegistry.h"


#include "Utilities/Settings/Settings.h"
#include "Utilities/Settings/TemporarySettingsSingleton.h"

#include "Utilities/EventSystem/events.h"
