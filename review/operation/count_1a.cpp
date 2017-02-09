#include "count_1a.h"

int count_one_bits(unsigned value){
	int ones;
	// 当这个值还有一些值为1的位时
	for (ones = 0; value != 0; value = value >> 1)
	{
		if(value % 2){
			ones ++;
		}
	}
	return ones;
}