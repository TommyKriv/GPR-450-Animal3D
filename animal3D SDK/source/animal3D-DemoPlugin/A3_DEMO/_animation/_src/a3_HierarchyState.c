/*
	Copyright 2011-2025 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_HierarchyState.c
	Implementation of transform hierarchy state.
*/

#include "../a3_HierarchyState.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//-----------------------------------------------------------------------------

// initialize pose set given an initialized hierarchy and key pose count
a3i32 a3hierarchyPoseGroupCreate(a3_HierarchyPoseGroup *poseGroup_out, const a3_Hierarchy *hierarchy, const a3ui32 poseCount)
{
	// validate params and initialization states
	//	(output is not yet initialized, hierarchy is initialized)
	if (poseGroup_out && hierarchy && !poseGroup_out->hierarchy && hierarchy->nodes)
	{
		// determine memory requirements
		a3ui32 const nodeCount = hierarchy->numNodes;
		a3ui32 const hposeCount = poseCount, hposeSpace = sizeof(a3_HierarchyPose) * hposeCount;
		a3ui32 const sposeCount = hposeCount * nodeCount, sposeSpace = sizeof(a3_SpatialPose) * sposeCount;
		a3ui32 const channelSpace = sizeof(a3_SpatialPoseChannel) * nodeCount;
		a3ui32 const orderSpace = sizeof(a3_SpatialPoseEulerOrder) * nodeCount;
		a3ui32 const memreq = hposeSpace + sposeSpace + channelSpace + orderSpace;
		a3index i;

		// allocate everything (one malloc)
		poseGroup_out->hpose = (a3_HierarchyPose*)malloc(memreq);
		poseGroup_out->hpose->hpose_base = poseGroup_out->pose = (a3_SpatialPose*)(poseGroup_out->hpose + hposeCount);
		poseGroup_out->channel = (a3_SpatialPoseChannel*)(poseGroup_out->pose + sposeCount);
		poseGroup_out->order = (a3_SpatialPoseEulerOrder*)(poseGroup_out->channel + nodeCount);

		// set pointers
		for (i = 1; i < hposeCount; ++i)
		{
			poseGroup_out->hpose[i].hpose_base = poseGroup_out->hpose[i - 1].hpose_base + nodeCount;
			poseGroup_out->hpose[i].hpose_index = i * nodeCount;
		}

		// reset all data
		a3hierarchyPoseReset(poseGroup_out->hpose, sposeCount);
		memset(poseGroup_out->channel, a3poseChannel_none, channelSpace);
		memset(poseGroup_out->order, a3poseEulerOrder_xyz, orderSpace);
		poseGroup_out->hierarchy = hierarchy;
		poseGroup_out->hposeCount = hposeCount;
		poseGroup_out->poseCount = sposeCount;

		// done
		return 1;
	}
	return -1;
}

// release pose set
a3i32 a3hierarchyPoseGroupRelease(a3_HierarchyPoseGroup *poseGroup)
{
	// validate param exists and is initialized
	if (poseGroup && poseGroup->hierarchy)
	{
		// release everything (one free)
		free(poseGroup->hpose);

		// reset pointers
		poseGroup->hierarchy = 0;
		poseGroup->hpose = 0;
		poseGroup->pose = 0;
		poseGroup->channel = 0;
		poseGroup->order = 0;

		// done
		return 1;
	}
	return -1;
}

// load binary
a3i32 a3hierarchyPoseGroupLoadBinary(a3_HierarchyPoseGroup* poseGroup, a3_FileStream const* fileStream)
{
	FILE* fp;
	a3ui32 ret = 0;
	a3ui32 dataSize = 0;
	if (poseGroup && fileStream)
	{
		if (poseGroup->hierarchy && !poseGroup->pose)
		{
			fp = fileStream->stream;
			if (fp)
			{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------
				


//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
			}
			return ret;
		}
	}
	return -1;
}

// save binary
a3i32 a3hierarchyPoseGroupSaveBinary(a3_HierarchyPoseGroup const* poseGroup, a3_FileStream const* fileStream)
{
	FILE* fp;
	a3ui32 ret = 0;
	if (poseGroup && fileStream)
	{
		if (poseGroup->hierarchy && poseGroup->pose)
		{
			fp = fileStream->stream;
			if (fp)
			{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------
				


//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
			}
			return ret;
		}
	}
	return -1;
}


//-----------------------------------------------------------------------------

// initialize hierarchy state given an initialized hierarchy
a3i32 a3hierarchyStateCreate(a3_HierarchyState *state_out, const a3_Hierarchy *hierarchy)
{
	// validate params and initialization states
	//	(output is not yet initialized, hierarchy is initialized)
	if (state_out && hierarchy && !state_out->hierarchy && hierarchy->nodes)
	{
		// determine memory requirements
		a3ui32 const nodeCount = hierarchy->numNodes;
		a3ui32 const hposeCount = sizeof(state_out->hpose) / sizeof(a3_HierarchyPose);
		a3ui32 const sposeCount = hposeCount * nodeCount;
		a3ui32 const memreq = sizeof(a3_SpatialPose) * sposeCount;
		a3index i;

		// allocate everything (one malloc)
		state_out->hpose->hpose_base = (a3_SpatialPose*)malloc(memreq);

		// set pointers
		state_out->hierarchy = hierarchy;
		for (i = 1; i < hposeCount; ++i)
		{
			state_out->hpose[i].hpose_base = state_out->hpose[i - 1].hpose_base + nodeCount;
			state_out->hpose[i].hpose_index = i * nodeCount;
		}

		// reset all data
		a3hierarchyPoseReset(state_out->hpose, sposeCount);

		// done
		return 1;
	}
	return -1;
}

// release hierarchy state
a3i32 a3hierarchyStateRelease(a3_HierarchyState *state)
{
	// validate param exists and is initialized
	if (state && state->hierarchy)
	{
		a3ui32 const hposeCount = sizeof(state->hpose) / sizeof(a3_HierarchyPose);
		a3ui32 i;

		// release everything (one free)
		free(state->hpose->hpose_base);

		// reset pointers
		state->hierarchy = 0;
		for (i = 0; i < hposeCount; ++i)
		{
			state->hpose[i].hpose_base = 0;
			state->hpose[i].hpose_index = 0;
		}

		// done
		return 1;
	}
	return -1;
}


//-----------------------------------------------------------------------------

// update inverse local-space matrices
a3i32 a3hierarchyStateUpdateLocalInverse(const a3_HierarchyState* state)
{
	if (state && state->hierarchy)
	{
		a3index i = 0;
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------
 
		for (i = 0; i < state->hierarchy->numNodes; i++)
		{
			a3real4x4TransformInverse(state->localSpaceInv->hpose_base[i].transformMat.m,
				state->localSpace->hpose_base[i].transformMat.m);
		}

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
		return i;
	}
	return -1;
}

// update inverse object-space matrices
a3i32 a3hierarchyStateUpdateObjectInverse(const a3_HierarchyState* state)
{
	if (state && state->hierarchy)
	{
		a3index i = 0;
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------
		
		for (i = 0; i < state->hierarchy->numNodes; i++)
		{
			a3real4x4TransformInverse(state->objectSpaceInv->hpose_base[i].transformMat.m,
				state->objectSpace->hpose_base[i].transformMat.m);
		}

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
		return i;
	}
	return -1;
}

// update inverse object-space bind-to-current matrices
a3i32 a3hierarchyStateUpdateObjectBindToCurrent(const a3_HierarchyState* state, const a3_HierarchyState* state_bind)
{
	if (state && state->hierarchy && state_bind && state_bind->hierarchy)
	{
		a3index i = 0;
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------
		
		// loop nodes
		for (i = 0; i < state->hierarchy->numNodes; i++)
		{
			a3real4x4Product(state->objectSpaceBindToCurrent->hpose_base[i].transformMat.m,   // dest
				state->objectSpace->hpose_base[i].transformMat.m,                // current object-space
				state_bind->objectSpaceInv->hpose_base[i].transformMat.m);       // bind object-space inverse
		}

//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
		return i;
	}
	return -1;
}


//-----------------------------------------------------------------------------
// https://research.cs.wisc.edu/graphics/Courses/cs-838-1999/Jeff/HTR.html
// This source was used for assistance
// load HTR file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupLoadHTR(a3_HierarchyPoseGroup* poseGroup_out, a3_Hierarchy* hierarchy_out, const a3byte* resourceFilePath)
{
	if (poseGroup_out && !poseGroup_out->hierarchy && hierarchy_out && !hierarchy_out->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-2: IMPLEMENT ME
//-----------------------------------------------------------------------------
		// Ethan do these
		/*
		//Some variable declarations. These need to be accessed in several steps
		a3boolean isHTR = true;
		a3boolean isHTRS = true;
		a3ui32 numSegments = 0;
		a3i32 numFrames = 0;
		a3i32 framerate = 0;
		a3_SpatialPoseEulerOrder eulerOrder = a3poseEulerOrder_xyz; // Default to XYZ
		a3_BasisAxis axisToUse = basis_yp;
		float calibrationUnits = 0.0f;
		a3boolean isDegrees = true;
		// Axis
		// 0 = X
		// 1 = Y
		// 2 = Z
		a3i32 globalGravityAxis = 1; // Y by default
		a3i32 boneAxis = 1; // Y by default
		float scaleFactor;

		
		// Opening file and prepping buffer
		FILE* sourceFile = fopen(resourceFilePath, "r");
		sourceFile;
		char fileLine[100];


		if(fscanf(sourceFile, "%s", fileLine));
		// Grab from the file until we find the header to remove any meaningless junk in front of it
		while (fileLine != "[Header]" && !EOF)
		{
			if(fscanf(sourceFile, "%s", fileLine));
		}

		// Get file data first
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "FileType", 9))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 == memcmp(fileLine, "GTR", 4))
			{
				isHTR = false;
			}
			else // Assume HTR if it isn't GTR
			{
				isHTR = true;
			}
		}
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "DataType", 9))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 != memcmp(fileLine, "HTRS", 5))
			{
				isHTRS = false;
				// Solve other orders later, doesn't matter since the file is in the proper order
				return -1;
			}
			else // Assume it is Transform rotation scale
			{
				isHTRS = true;
			}
		}
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "FileVersion", 12))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 != memcmp(fileLine, "1", 2))
			{
				// file should be version 1
				return -1;
			}
			else // Move forward
			{
				
			}
		}

		// Now it's time to fetch the data for the hierarchy
		// Retrieve the number of segments
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "NumSegments", 12))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			numSegments = atoi(fileLine);
			//hierarchy_out->numNodes = numSegments;
			a3hierarchyCreate(hierarchy_out, numSegments, NULL);
		}
		// Retrieve the numnber of frames
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "NumFrames", 10))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			numFrames = atoi(fileLine);
			a3hierarchyPoseGroupCreate(poseGroup_out, hierarchy_out, numFrames);
		}
		// Retrieve Framerate
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "DataFrameRate", 14))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			framerate = atoi(fileLine);
		}
		// Retrieve euler angle order
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "EulerRotationOrder", 19))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 == memcmp(fileLine, "XYZ", 4)) { eulerOrder = a3poseEulerOrder_xyz; }
			else if (0 == memcmp(fileLine, "YZX", 4)) { eulerOrder = a3poseEulerOrder_yzx; }
			else if (0 == memcmp(fileLine, "ZXY", 4)) { eulerOrder = a3poseEulerOrder_zxy; }
			else if (0 == memcmp(fileLine, "YXZ", 4)) { eulerOrder = a3poseEulerOrder_yxz; }
			else if (0 == memcmp(fileLine, "XZY", 4)) { eulerOrder = a3poseEulerOrder_xzy; }
			else if (0 == memcmp(fileLine, "ZYX", 4)) { eulerOrder = a3poseEulerOrder_zyx; }
			poseGroup_out->order[0] = eulerOrder;
		}
		// Retrieve calibration units
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "CalibrationUnits", 17))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 == memcmp(fileLine, "mm", 3)) { calibrationUnits = .001f; }
			else
			{
				// WIP
				int index = 0;
				char firstNum[100];
				while (fileLine[index] != '/')
				{
					firstNum[index] = fileLine[index];
					index++;
				}
			}
		}
		// Retrieve rotation units
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "RotationUnits", 14))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 == memcmp(fileLine, "Degrees", 8)) { isDegrees = true; }
			else
			{
				isDegrees = false;
			}
		}
		// Retrieve gravity axis
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "GlobalAxisofGravity", 20))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 == memcmp(fileLine, "Y", 2)) { globalGravityAxis = 1; }
			else if(0 == memcmp(fileLine, "X", 2)) { globalGravityAxis = 0; }
			else if(0 == memcmp(fileLine, "Z", 2)) { globalGravityAxis = 2; }
		}
		// Retrieve bone axis
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "BoneLengthAxis", 15))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 == memcmp(fileLine, "Y", 2)) { boneAxis = 1; }
			else if (0 == memcmp(fileLine, "X", 2)) { boneAxis = 0; }
			else if (0 == memcmp(fileLine, "Z", 2)) { boneAxis = 2; }
		}
		// Retrieve global scale factor
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "ScaleFactor", 12))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			scaleFactor = (float)atof(fileLine);
		}
		// Moving on to setting up the hierarchy
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "[SegmentNames&Hierarchy]", 25))
		{
			for (a3ui32 i = 0; i < numSegments; i++)
			{
				char nodeName[32] = "";
				char parentName[32] = "";
				if (fscanf(sourceFile, "%s", fileLine));
				strcpy(nodeName, fileLine);
				if (fscanf(sourceFile, "%s", fileLine));
				strcpy(parentName, fileLine);
				a3i32 parentIndex = -1;
				if (0 == memcmp(parentName, "GLOBAL", 7))
				{
					parentIndex = -1;
				}
				else
				{
					for (a3ui32 j = 0; j < hierarchy_out->numNodes; j++)
					{
						if (0 == memcmp(parentName, hierarchy_out->nodes[j].name, 32))
						{
							parentIndex = j;
							break;
						}
					}
				}
				a3hierarchySetNode(hierarchy_out, i, parentIndex, nodeName);				
			}
		}

		// Extract base pose


		
		// Final part, filling the posegroup with all poses
		for (a3ui32 i = 0; i < numFrames; i++)
		{
			for (a3ui32 j = 0; j < numFrames; j++)
			{
				a3boolean shouldLoop = true;
				while (shouldLoop)
				{
					if (fscanf(sourceFile, "%s", fileLine)); // Clear the header
					if (0 == memcmp(fileLine, "[", 1))
					{
						shouldLoop = false;
					}
				}
				a3_SpatialPose newPose;
				


				//a3spatialPoseSetTranslation(newPose, );
			}
		}

		poseGroup_out->channel;
		// a3_SpatialPose* debugPose = poseGroup_out->hpose[1].hpose_base;

		*/
		a3boolean debugBreakpoint = true;
		
//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-2
//-----------------------------------------------------------------------------
	}
	return -1;
}

// load BVH file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupLoadBVH(a3_HierarchyPoseGroup* poseGroup_out, a3_Hierarchy* hierarchy_out, const a3byte* resourceFilePath)
{
	if (poseGroup_out && !poseGroup_out->hierarchy && hierarchy_out && !hierarchy_out->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
	}
	return -1;
}

// save HTR file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupSaveHTR(const a3_HierarchyPoseGroup* poseGroup_in, const a3_Hierarchy* hierarchy_in, const a3byte* resourceFilePath)
{
	if (poseGroup_in && poseGroup_in->hierarchy && hierarchy_in && hierarchy_in->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------
		// Ethan do these


//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
	}
	return -1;
}

// save BVH file, read and store complete pose group and hierarchy
a3i32 a3hierarchyPoseGroupSaveBVH(const a3_HierarchyPoseGroup* poseGroup_in, const a3_Hierarchy* hierarchy_in, const a3byte* resourceFilePath)
{
	if (poseGroup_in && poseGroup_in->hierarchy && hierarchy_in && hierarchy_in->nodes && resourceFilePath && *resourceFilePath)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-OPTIONAL: IMPLEMENT ME
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//****END-TO-DO-OPTIONAL
//-----------------------------------------------------------------------------
	}
	return -1;
}


//-----------------------------------------------------------------------------
