#include <stdio.h>
#include <assert.h>

#define SEQ_MAX_SIZE	(20000)

#define MAP_MAX_SIZE	((SEQ_MAX_SIZE / 8) + 2) 

typedef unsigned char ubyte;

//	MapsUpdate �������ڸ��� maps ָ�������� bit�������ظ���ǰ��ֵ 
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
	//	��¼�������������еĸ��� 
	int total = 0;
	
	for (int si = 0; si < ASize; si++) {
		
		//	����һ��λӳ�䣬����������ͬ��ŵ�����(ֱ�����ñ���������ʼ��)
		ubyte maps[MAP_MAX_SIZE] = {0};
		
		//	�����Ӵ��ļ��� 
		int counter = 0; 
		
		for (int ei = si; ei < ASize; ei++) {
			
			
			//	����maps������ȡ����ǰ��ֵ 
			int old = MapsUpdate(maps, A[ei]); 
			if (0 == old) {
				//	����Ѿ��ﵽ��K���������Ͳ��������Ӽ����ˣ�Ӧ����ֹ
				if (counter == K) {
					break; 
				}
				
				//	�������ǰΪ0����ʾA[ei]�������ӵģ���Ҫ���������Ӵ����ȼ��� 
				counter++; 
			}
			
			//	������� 
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
	
	//	�����ܸ��� 
	return total; 
}

#define TESTCASE(vM)	if (1)
	
int main(int argc, char *argv[])
{
	TESTCASE("��������1") {
    	int A[] = {1,2,1,2,3};
    	int K = 2;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(7 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("��������2") {
    	int A[] = {1,2,1,3,4};
    	int K = 3;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(3 == subarraysWithKDistinct(A, ASize, K));
	}
	
	TESTCASE("��ȫ����") {
    	int A[] = {1,2,3,4,5};
    	int K = 1;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(5 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("�պ���ȫ���") {
    	int A[] = {2,2,2,2,2};
    	int K = 3;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(0 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("�պ���ȫ�ظ��������Ǵղ���") {
    	int A[] = {2,2,2,2,2};
    	int K = 2;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(0 == subarraysWithKDistinct(A, ASize, K));
	}

	TESTCASE("K̫��") {
    	int A[] = {2,3,2,1,2};
    	int K = 30;
    	int ASize = sizeof(A) / sizeof(A[0]);
    	assert(0 == subarraysWithKDistinct(A, ASize, K));
	}
	
	return 0;
}
