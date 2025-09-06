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
	
	a3_KeyframeAnimationController.c
	Implementation of keyframe animation controller.
*/

#include "../a3_KeyframeAnimationController.h"

#include <string.h>


// macros to help with names
#define A3_CLIPCTRL_DEFAULTNAME		("unnamed clip ctrl")
#define A3_CLIPCTRL_SEARCHNAME		((ctrlName && *ctrlName) ? ctrlName : A3_CLIPCTRL_DEFAULTNAME)


//-----------------------------------------------------------------------------

// initialize clip controller
a3i32 a3clipControllerInit(a3_ClipController* clipCtrl_out, const a3byte ctrlName[a3keyframeAnimation_nameLenMax], const a3_ClipPool* clipPool, const a3ui32 clipIndex_pool, const a3i32 playback_step, const a3f64 playback_stepPerSec)
{
	a3i32 const ret = a3clipControllerSetClip(clipCtrl_out, clipPool, clipIndex_pool, playback_step, playback_stepPerSec);
	if (ret >= 0)
	{
		strncpy(clipCtrl_out->name, A3_CLIPCTRL_SEARCHNAME, a3keyframeAnimation_nameLenMax);
		return ret;
	}
	return -1;
}

// update clip controller
a3i32 a3clipControllerUpdate(a3_ClipController* clipCtrl, a3f64 dt)
{
	if (clipCtrl && clipCtrl->clipPool)
	{
//-----------------------------------------------------------------------------
//****TO-DO-ANIM-PROJECT-1: IMPLEMENT ME
//-----------------------------------------------------------------------------
		a3f64 t = clipCtrl->keyframe->duration_sec; //Uncertain why not clipCtrl->keyframeTime_sec
		a3f64 t1 = clipCtrl->clipPool->keyframe[clipCtrl->keyframeIndex].duration_sec;
		a3f64 t0 = t1 - t;
		//Attempted with 0-1 increments
		/*clipCtrl->keyframeParam += 1 / dt; 
		clipCtrl->clipParam += 1 / dt;
		if (clipCtrl->keyframeParam >= 1)
		{
			clipCtrl->keyframeIndex++;
			clipCtrl->clipPool++;
		}*/
		while (t < t1)
		{
			
			//if (dt = 0) //1 Case Paused
			//{
			//	return;
			//}
			//if (dt > 0) //2 Case Forward
			//{
			//	t += dt;
			//	clipCtrl->clipTime_sec += dt;
			//}
			//if (dt < 0) //3 Case Reverse
			//{
			//	t1 = clipCtrl->clipPool->keyframe[clipCtrl->keyframeIndex--].duration_sec;
			//}
		}

		//if (t >= t1) //Checking for passing over keyframe duration
		//{
		//	if (t1 != clipCtrl->clipPool->keyframeCount) //4 Case Forward Skip
		//	{
		//		t1 = clipCtrl->clipPool->keyframe[clipCtrl->keyframeIndex++].duration_sec;
		//		t = 0;
		//	}
		//	else //5 Case Forward Terminus
		//	{
		//		clipCtrl->clipIndex++;
		//	}
		//}
		//if (t <= t0) //Checking for passing under keyframe duration
		//{
		//	if (t1 != 0)  //6 Case Reverse Skip
		//	{
		//		t1 = clipCtrl->clipPool->keyframe[clipCtrl->keyframeIndex--].duration_sec;
		//	}
		//	else //7 Case Reverse Terminus
		//	{
		//		clipCtrl->clipIndex--;
		//	}
		//}
		
//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-1
//-----------------------------------------------------------------------------
	}
	return -1;
}


//-----------------------------------------------------------------------------
