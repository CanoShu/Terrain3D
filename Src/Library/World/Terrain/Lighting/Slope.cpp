//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <World/Terrain/Lighting/Slope.h>
#include <World/Terrain/LightMap.h>
#include <World/Terrain/HeightMap.h>

namespace t3d { namespace World { namespace Terrain { namespace Lighting
{
	bool Slope::computeBrightness(LightMap &lm, const HeightMap &hm)
	{
		//ensure the height map and light map are the same size
		if (lm.size() != hm.size())
			return false;

		//just max out the lightmap for now since the sun will shine everywhere max
		for (int y=0; y<lm.size(); y++)
		{
			for (int x=0; x<lm.size(); x++)
			{
				if (y == 0)
				{
					lm.set(x, y, 1.0f);
				}
				else
				{
					float prevHeight = hm.get(x, y-1);
					float curHeight = hm.get(x, y);
					float delta = prevHeight - curHeight;
					float brightness = 1.0f;

					if (delta > 0.0f)
					{
						const float intensity = 15.0f;
						brightness = (1-delta) * intensity;
					}

					lm.set(x, y, std::max(std::max(0.0f, brightness), 1.0f));
				}
			}
		}

		return true;
	}
}}}}