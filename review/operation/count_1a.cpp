#include "count_1a.h"

int count_one_bits(unsigned value){
	int ones;
	// �����ֵ����һЩֵΪ1��λʱ
	for (ones = 0; value != 0; value = value >> 1)
	{
		if(value % 2){
			ones ++;
		}
	}
	return ones;
}