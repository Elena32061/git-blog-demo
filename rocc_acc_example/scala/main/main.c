#include<stdio.h>
#include "rocc.h"
#include "encoding.h"
#define SIZE 10

unsigned long long  gcdCompute(unsigned long long  a, unsigned long long  b){
	long long unsigned temp;
	while(a != b){
		if(a>b){
			temp = b;
			b = a;
			a = temp;
		}
		b = b - a;
	}
	return a;
}

int main(void){
	unsigned long long  randNum1[SIZE] = {
            26985, 84546, 46198, 38570, 46417, 49941, 8138, 8827, 99324, 96819}; 
	unsigned long long  randNum2[SIZE] = {
            2826, 77394, 39239, 46078, 43985, 43458, 34337, 66575, 76502, 17900};
	unsigned long long  swLcmRes[SIZE] = {0};
	unsigned long long  hwLcmRes[SIZE] = {0};	
	unsigned long long  start, end;
	// 软件计算
	start = rdcycle();
	for(int i=0; i<SIZE; i++){
		swLcmRes[i] = randNum1[i]*randNum2[i]/gcdCompute(randNum1[i], randNum2[i]);
	}
	end = rdcycle();
	// printf("LCM compute:\n");
	// for(int i=0; i<SIZE; i++){
	// 	printf("(%lld, %lld) -> %lld\n", randNum1[i], randNum2[i], swLcmRes[i]);
	// }
	printf("SW average cycles used:  %lld\n", (end-start)/SIZE);
	
	// RoCC 加速
	start = rdcycle();
	for(int i=0; i<SIZE; i++){
		asm volatile ("fence"); // 保证数据都存会内存
		ROCC_INSTRUCTION_DSS(0, hwLcmRes[i], randNum1[i], randNum2[i], 0);
		asm volatile ("fence" ::: "memory");
	}	
	end = rdcycle();

	for(int i=0; i<SIZE; i++){
		if(swLcmRes[i] != hwLcmRes[i]){
			printf("test failed! %lld and %lld LCM: swLcmRes: %lld, hwLcmRes: %lld\n", randNum1[i], randNum2[i], swLcmRes[i], hwLcmRes[i]);
			return 0;
		}
	}	
	printf("HW average cycles used:  %lld\n", (end-start)/SIZE);
	printf("test successed! \n");
	return 0;
	
}