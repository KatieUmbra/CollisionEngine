#pragma once

float CE_clamp_2b(float lower, float value, float upper)
{
	float returned = value;
	if (value < lower)
	{
		returned = lower;
	}
	if (value > upper)
	{
		returned = upper;
	}
	return returned;
}
