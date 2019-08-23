#include <stdio.h>
#include <assert.h>

#define SEQ_MAX_SIZE	(20000)

#define MAP_MAX_SIZE	((SEQ_MAX_SIZE / 8) + 2) 

typedef unsigned char ubyte;

//	MapsUpdate 函数用于更新 maps 指定索引的 bit，并返回更新前的值 
static inline int MapsUpdate(ubyte* maps, int index)
{
	static ubyte masks[] = {
		0x01,
		0x02,
		0x04,
		0x08,
		0x10,
		0x20,
		0x40,
		0x80
	};
	
	int byteIndex = index / 8;
	int bitsIndex = index % 8;
	int old = ((maps[byteIndex] & masks[bitsIndex])?1:0);
	maps[byteIndex] |= masks[bitsIndex];
	
	return old;
}

int subarraysWithKDistinct(int* A, int ASize, int K) 
{
	//	记录满足条件的序列的个数 
	int total = 0;
	
	for (int si = 0; si < ASize; si++) {
		
		//	定义一个位映射，用来跟踪相同编号的数字(直接利用编译器来初始化)
		ubyte maps[MAP_MAX_SIZE] = {0};
		
		//	连续子串的计数 
		int counter = 0; 
		
		for (int ei = si; ei < ASize; ei++) {
			
			
			//	更新maps，并获取更新前的值 
			int old = MapsUpdate(maps, A[ei]); 
			if (0 == old) {
				//	如果已经达到了K的条件，就不该再增加计数了，应该终止
				if (counter == K) {
					break; 
				}
				
				//	如果更新前为0，表示A[ei]是新增加的，需要增加连续子串长度计数 
				counter++; 
			}
			
			//	如果计数 
			if (counter == K) {
				total++;

//				printf("** ");
//				for (int k = si; k <= ei; k++) {
//    				printf("%d ", A[k]);
//				}
//				printf("\n");
			}
		}
	}
	
	//	返回总个数 
	return total; 
}

#define TESTCASE(vM)	if (1)
	
int main(int argc, char *argv[])
{
	TESTCASE("基本用例1") {
    	int A[] = {1,2,1,2,3};
    	int K = 2;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(7 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("基本用例2") {
    	int A[] = {1,2,1,3,4};
    	int K = 3;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(3 == subarraysWithKDistinct(A, ASize, K));
	}
	
	TESTCASE("完全独立") {
    	int A[] = {1,2,3,4,5};
    	int K = 1;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(5 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("刚好完全相等") {
    	int A[] = {2,2,2,2,2};
    	int K = 3;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(0 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("刚好完全重复，但就是凑不齐") {
    	int A[] = {2,2,2,2,2};
    	int K = 2;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(0 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("K太大") {
    	int A[] = {2,3,2,1,2};
    	int K = 30;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(0 == subarraysWithKDistinct(A, ASize, K));
	}
	
	return 0;
}
