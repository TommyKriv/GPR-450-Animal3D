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

a3boolean reverse = a3false;

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
		if (reverse == 1)
		{
			dt *= -1;
		}
		a3f64 newKeyTimeSecs = dt + (clipCtrl->keyframeTime_sec); // This is the new time in seconds
		a3f64 newClipTimeSecs = (clipCtrl->clipTime_sec) + dt;
		// Playback is paused, do nothing and skip over lol lmao
		if (dt == 0)
		{
			
		}
		// We are moving forward. Apply forward logic here
		else if (dt > 0)
		{
			

			// Loops until we have reached the desired new keyframe
			while (newKeyTimeSecs >= clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec)
			{
				// If forward terminus
				if (newClipTimeSecs >= clipCtrl->clip[clipCtrl->clipIndex].duration_sec) //replaced prior check with clipCtrl->clip[clipCtrl->clipIndex].duration_sec, prior was just checking for sample clip duration
				{
					// Loop the clip
					//newClipTimeSecs -= clipCtrl->clipTime_sec;
					//newKeyTimeSecs -= clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					//if (newClipTimeSecs != newKeyTimeSecs)
					//{
					//	int help = 0; // If this breakpoint is ever triggered, god help us all
					//}
					//clipCtrl->keyframeIndex = 0;
					newClipTimeSecs = clipCtrl->clip[clipCtrl->clipIndex].duration_sec;
					newKeyTimeSecs = clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					reverse = 1; // flip
					break; // stop advancing
				}
				else // If not, normal skip
				{
					//newKeyTimeSecs -= clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					newKeyTimeSecs = 0; //Set to 0 as its a new keyframe, previous version was skipping ahead.
					clipCtrl->keyframeIndex++;
				}
			}

		}
		// We are moving backwards, apply backwards logic
		else if (dt < 0)
		{
			// Loops until we have reached the desired new keyframe
			while (newKeyTimeSecs <= 0)
			{
				// If reverse terminus
				if (newClipTimeSecs <= 0.01)
				{
					//// Loop the clip
					//newClipTimeSecs += clipCtrl->clipTime_sec;
					////newKeyTimeSecs -= clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec;
					//clipCtrl->keyframeIndex = clipCtrl->clip->keyframeCount-1;
					newClipTimeSecs = 0;
					newKeyTimeSecs = 0;
					reverse = a3false; // flip
					break; // stop rewinding
				}
				else // If not, normal reverse skip
				{
					newKeyTimeSecs += clipCtrl->keyframe[clipCtrl->keyframeIndex - 1].duration_sec;
					clipCtrl->keyframeIndex--;
				}
			}
		}
		else
		{
			// All hell has broken lose...
		}


		// Set the new values of the clip controller as determined by the logic above
		clipCtrl->keyframeTime_sec = newKeyTimeSecs;
		clipCtrl->clipTime_sec = newClipTimeSecs;
		clipCtrl->keyframeParam = newKeyTimeSecs / clipCtrl->keyframe[clipCtrl->keyframeIndex].duration_sec; 
		clipCtrl->clipParam = newClipTimeSecs / clipCtrl->clip[clipCtrl->clipIndex].duration_sec;		
//-----------------------------------------------------------------------------
//****END-TO-DO-PROJECT-1
//-----------------------------------------------------------------------------
	}
	return -1;
}


//-----------------------------------------------------------------------------
