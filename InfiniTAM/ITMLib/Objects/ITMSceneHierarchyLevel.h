// Copyright 2014 Isis Innovation Limited and the authors of InfiniTAM

#pragma once

#include "../Utils/ITMLibDefines.h"

namespace ITMLib
{
	namespace Objects
	{
		class ITMSceneHierarchyLevel
		{
		public:
			int levelId;

			bool rotationOnly;

			ITMFloat4Image *pointsMap;
			ITMFloat4Image *normalsMap;
			Vector4f intrinsics;

			bool manageData;

			ITMSceneHierarchyLevel(Vector2i imgSize, int levelId, bool rotationOnly, MemoryDeviceType memoryType, bool skipAllocation = false)
			{
				this->manageData = !skipAllocation;
				this->levelId = levelId;
				this->rotationOnly = rotationOnly;

				if (!skipAllocation) {
					this->pointsMap = new ITMFloat4Image(imgSize, memoryType);
					this->normalsMap = new ITMFloat4Image(imgSize, memoryType);
				}
			}

			void UpdateHostFromDevice()
			{ 
				this->pointsMap->UpdateHostFromDevice();
				this->normalsMap->UpdateHostFromDevice();
			}

			void UpdateDeviceFromHost()
			{ 
				this->pointsMap->UpdateDeviceFromHost();
				this->normalsMap->UpdateDeviceFromHost();
			}

			~ITMSceneHierarchyLevel(void)
			{
				if (manageData) {
					delete pointsMap;
					delete normalsMap;
				}
			}

			// Suppress the default copy constructor and assignment operator
			ITMSceneHierarchyLevel(const ITMSceneHierarchyLevel&);
			ITMSceneHierarchyLevel& operator=(const ITMSceneHierarchyLevel&);
		};
	}
}
