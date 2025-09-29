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
			a3hierarchyCreate(hierarchy_out, numSegments, 0);
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
				calibrationUnits = (float)atof(fileLine);
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
			scaleFactor *= 100.0f / 1000.0f;
		}
		poseGroup_out->channel[0] = a3poseChannel_rotate_xyz;
		poseGroup_out->channel[1] = a3poseChannel_scale_xyz;
		poseGroup_out->channel[2] = a3poseChannel_translate_xyz;
		poseGroup_out->channel[3] = a3poseChannel_user_xyz;

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
		if (fscanf(sourceFile, "%s", fileLine));
		if (0 == memcmp(fileLine, "[BasePosition]", 15))
		{
			for (a3ui32 i = 0; i < numSegments; i++)
			{
				a3f32 xComp = 0.0f;
				a3f32 yComp = 0.0f;
				a3f32 zComp = 0.0f;
				a3f32 scaleComp = 1.0f;
				if (fscanf(sourceFile, "%s", fileLine));
				if (isHTRS)
				{
					// Grab transform
					switch (eulerOrder)
					{
					case a3poseEulerOrder_xyz:
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_yzx:
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_zxy:
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_yxz:
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_xzy:
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_zyx:
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						break;
					}
					a3spatialPoseSetTranslation(&poseGroup_out->pose[i], xComp*scaleFactor, yComp*scaleFactor, zComp*scaleFactor);

					// Grab rotation
					switch (eulerOrder)
					{
					case a3poseEulerOrder_xyz:
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_yzx:
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_zxy:
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_yxz:
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_xzy:
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						break;
					case a3poseEulerOrder_zyx:
						if (fscanf(sourceFile, "%s", fileLine));
						zComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						yComp = (float)atof(fileLine);
						if (fscanf(sourceFile, "%s", fileLine));
						xComp = (float)atof(fileLine);
						break;
					}
					a3spatialPoseSetRotation(&poseGroup_out->pose[i], xComp, yComp, zComp);

					// Get scale
					if (fscanf(sourceFile, "%s", fileLine));
					scaleComp = (float)atof(fileLine);
					a3spatialPoseSetScale(&poseGroup_out->pose[i], scaleComp, scaleComp, scaleComp);

					poseGroup_out->pose[i];
				}
				else
				{
					return -1;
				}

				poseGroup_out->hpose[0].hpose_base = &poseGroup_out->pose[0];
				poseGroup_out->hpose[0].hpose_index = 0;
			}



		}
		poseGroup_out->pose[numSegments];
		/*
		// Final part, filling the posegroup with all poses
		a3i32 segmentCounter = numSegments;
		a3i32 hierarchyPoseCounter = 1;
		a3f32 xComp = 0.0f;
		a3f32 yComp = 0.0f;
		a3f32 zComp = 0.0f;
		a3f32 scaleComp = 1.0f;
		while (0 != memcmp(fileLine, "[EndOfFile]", 12))
		{
			if (fscanf(sourceFile, "%s", fileLine));
			if (0 == memcmp(fileLine, hierarchy_out->nodes[0].name, 32))
			{
				
				for (a3ui32 i = 0; i < numSegments; i++)
				{
					while (true)
					{
						if (0 == memcmp(fileLine, "[", 1))
						if (fscanf(sourceFile, "%s", fileLine));

						
						switch (eulerOrder)
						{
						case a3poseEulerOrder_xyz:
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_yzx:
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_zxy:
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_yxz:
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_xzy:
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_zyx:
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							break;
						}
						a3spatialPoseSetTranslation(&poseGroup_out->pose[segmentCounter], xComp * scaleFactor, yComp * scaleFactor, zComp * scaleFactor);

						// Grab rotation
						switch (eulerOrder)
						{
						case a3poseEulerOrder_xyz:
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_yzx:
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_zxy:
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_yxz:
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_xzy:
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							break;
						case a3poseEulerOrder_zyx:
							if (fscanf(sourceFile, "%s", fileLine));
							zComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							yComp = (float)atof(fileLine);
							if (fscanf(sourceFile, "%s", fileLine));
							xComp = (float)atof(fileLine);
							break;
						}
						a3spatialPoseSetRotation(&poseGroup_out->pose[segmentCounter], xComp, yComp, zComp);

						// Get scale
						if (fscanf(sourceFile, "%s", fileLine));
						scaleComp = (float)atof(fileLine);
						a3spatialPoseSetScale(&poseGroup_out->pose[segmentCounter], scaleComp, scaleComp, scaleComp);

						if (i == 0)
						{
							poseGroup_out->hpose[hierarchyPoseCounter].hpose_base = &poseGroup_out->pose[segmentCounter];
							poseGroup_out->hpose[hierarchyPoseCounter].hpose_index = segmentCounter;
						}
						segmentCounter++;
					}
					
				}
			}
		}

		poseGroup_out->channel;
		// a3_SpatialPose* debugPose = poseGroup_out->hpose[1].hpose_base;
		*/
		if (fscanf(sourceFile, "%s", fileLine));
		if (fscanf(sourceFile, "%s", fileLine));
		

		for (a3ui32 i = 67; i < 134; i++)
		{
			a3f32 xComp, yComp, zComp, scaleComp;
			if (fscanf(sourceFile, "%s", fileLine)); // Extract header
			if (fscanf(sourceFile, "%s", fileLine)); // Extract number
			if (fscanf(sourceFile, "%s", fileLine));
			zComp = (float)atof(fileLine);
			if (fscanf(sourceFile, "%s", fileLine));
			yComp = (float)atof(fileLine);
			if (fscanf(sourceFile, "%s", fileLine));
			xComp = (float)atof(fileLine);
			a3spatialPoseSetTranslation(&poseGroup_out->pose[i], xComp, yComp, zComp);
			if (fscanf(sourceFile, "%s", fileLine));
			zComp = (float)atof(fileLine);
			if (fscanf(sourceFile, "%s", fileLine));
			yComp = (float)atof(fileLine);
			if (fscanf(sourceFile, "%s", fileLine));
			xComp = (float)atof(fileLine);
			a3spatialPoseSetRotation(&poseGroup_out->pose[i], xComp, yComp, zComp);
			if (fscanf(sourceFile, "%s", fileLine));
			scaleComp = (float)atof(fileLine);



			for (a3ui32 j = 2; j <= 24; j++)
			{
				if (fscanf(sourceFile, "%s", fileLine));
				if (fscanf(sourceFile, "%s", fileLine));
				if (fscanf(sourceFile, "%s", fileLine));
				if (fscanf(sourceFile, "%s", fileLine));
				if (fscanf(sourceFile, "%s", fileLine));
				if (fscanf(sourceFile, "%s", fileLine));
				if (fscanf(sourceFile, "%s", fileLine));
				if (fscanf(sourceFile, "%s", fileLine));
			}
		}

		poseGroup_out->hpose[1].hpose_base = &poseGroup_out->pose[67];
		/*
a3spatialPoseSetTranslation(&poseGroup_out->pose[67], (float)atof("-8.671660271e-18"), (float)atof("1039.914673"), (float)atof("20.76076508"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[68], (float)atof("9.234152094e-05"), (float)atof("101.8158798"), (float)atof("1.31520927"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[69], (float)atof("2.519402869e-06"), (float)atof("100.8345108"), (float)atof("-10.00804329"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[70], (float)atof("3.4574864e-06"), (float)atof("91.00010681"), (float)atof("-13.73417091"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[71], (float)atof("6.334285445e-06"), (float)atof("166.7166901"), (float)atof("-25.16167831"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[72], (float)atof("-4.242318937e-06"), (float)atof("96.17874908"), (float)atof("16.85007477"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[73], (float)atof("0"), (float)atof("178.2"), (float)atof("25.8"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[74], (float)atof("30.67560577"), (float)atof("64.09507751"), (float)atof("92.83554077"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[75], (float)atof("-30.67550468"), (float)atof("64.09500122"), (float)atof("92.83547211"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[76], (float)atof("45.70446396"), (float)atof("109.4598465"), (float)atof("-26.27988052"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[77], (float)atof("105.9236984"), (float)atof("-5.245829105"), (float)atof("-22.32120132"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[78], (float)atof("278.4151917"), (float)atof("-0.0008942864952"), (float)atof("0.0003745891154"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[79], (float)atof("283.2883911"), (float)atof("-0.0001744071778"), (float)atof("0.0003780452244"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[80], (float)atof("24.66140366"), (float)atof("-15.7504921"), (float)atof("26.82413483"));
a3spatialPoseSetTranslation(&poseGroup_out->pose[81], (float)atof("32.29803848"), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[82], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[83], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[84], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[85], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[86], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[87], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[88], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[89], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[90], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[91], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[92], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[93], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[94], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[95], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[96], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[97], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[98], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[99], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[100], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[101], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[102], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[103], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[104], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[105], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[106], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[107], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[108], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[109], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[110], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[111], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[112], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[113], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[114], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[115], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[116], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[117], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[118], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[119], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[120], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[121], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[122], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[123], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[124], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[125], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[126], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[127], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[128], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[129], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[130], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[131], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[132], (float)atof(""), (float)atof(""), (float)atof(""));
a3spatialPoseSetTranslation(&poseGroup_out->pose[133], (float)atof(""), (float)atof(""), (float)atof(""));
*/
		a3boolean debugBreakpoint = true;
		return 1;
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
