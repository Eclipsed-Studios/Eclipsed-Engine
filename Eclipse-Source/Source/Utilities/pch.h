#pragma once

#include "ChatGPT_Dump/Base64.hpp"


#include "Common/MainSingleton.h"
#include "Common/Timer.h"


#include "Containers/BitMask.hpp"
#include "Containers/RingBuffer.h"


#include "Debug/Output/DebugLogBuffer.h"
#include "Debug/Output/DebugLogger.h"

#include "Debug/Profiling/DebugInformationCollector.h"


#include "Files/DirectoryTree.h"
#include "Files/FileInfo.h"
#include "Files/FileWatcher.h"


#include "Macros/defines.h"


#include "Math/Color.h"
#include "Math/CommonMath.h"
#include "Math/Random.h"
#include "Math/Rect.h"
#include "Math/RectSizePos.h"
#include "Math/Vector/Vector2.h"
#include "Math/Vector/Vector3.h"
#include "Math/Vector/Vector4.h"


#include "PlatformIntegration/DiscordIntegration.h"
#include "PlatformIntegration/IntegrationManager.h"


#include "Reflection/AbstractSerializedVariable.h"
#include "Reflection/Reflection.h"
#include "Reflection/ReflectionTypeChecks.h"
#include "Reflection/SerializedEnum.hpp"
#include "Reflection/SerializedVariable.h"
#include "Reflection/Registry/ComponentRegistry.h"
#include "Reflection/Registry/WindowRegistry.h"


#include "Settings/Settings.h"
#include "Settings/TemporarySettingsSingleton.h"
