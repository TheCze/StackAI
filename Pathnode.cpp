#pragma once
#include "Pathnode.h"

int Pathnode::length(int i)
{
	i++;
	if (next) 
		return next->length(i);	
	else
		return i;
}
