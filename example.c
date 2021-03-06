#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFSIZE		100000000

#define FUNC_TIME_SPEC(func) do{\
	struct	timeval ts,te;\
	float	f;\
	gettimeofday(&ts,NULL);\
	func;\
	gettimeofday(&te,NULL);\
	f = 1000000 * (te.tv_sec - ts.tv_sec) \
		+ te.tv_usec - ts.tv_usec;\
	f /= 1000000;\
 	printf("%fs\n",f);\
}while(0)


//宏:交换两数的值。
#define swap(a, b) {	\
	a ^= b; 			\
	b ^= a; 			\
	a ^= b; 			\
}

/*
	功能:只排序数组最后一位
	arr:数组
	length:数组长度
	*/
int insert_sort_only_last(int *arr, int length){
	if(length < 2) return -1;

	int i = length - 2, key = arr[length - 1];

	while(key < arr[i]){
		arr[i+1] = arr[i];
		i--;
		if(i < 0) break;
	}
	
	arr[i+1] = key;

	return 0;
}

/*
	算法导论习题2.3-4
	递归插入排序
	arr:数组
	length:数组长度
	*/
int recursive_insert_sort(int *arr, int length){
	if(length <= 1) return -1;
	recursive_insert_sort(arr, length - 1);
	insert_sort_only_last(arr, length);


	return 0;
}

//算法导论习题2.2-2，选择排序算法
int select_sort(int *arr, int length){
	int i = 0, j = 0;
	int key = 0;
	//循环，0 to length -1 
	for(i; i < length - 1; i++){ 					//  n 
		//key = i to length -2，储存最小值的下标
		key = i;									//n-1
		//循环，i+1 to length -1 
		for(j = i + 1; j < length; j++){			// (n * n+1) /2
			//比较，小于就把下标赋值给key
			if(arr[j] < arr[key])					//(n * n+1) /2 - 1
				key = j;							//n	
		}
		//跳出内循环，找到第一轮最小值下标key
		if(arr[key] != arr[i])						// n -1
			//交换数组位于下标i和下标key的值
			swap(arr[i], arr[key]);					//n-1 
	}
	return 0;
}

//算法导论习题，2.3-2 
int merge(int *arr, int p, int q, int r){
	

	int m  = 0, n = 0, i = 0;
	int n1 = q - p + 1;
	int n2 = r - q;
	//申请动态内存
	int *Larr = calloc(sizeof(int),  n1);
	int *Rarr = calloc(sizeof(int),  n2);
	//将左半部copy到Larr
	memcpy(Larr, &arr[p], sizeof(int) * n1);
	//右半部copy到Rarr
	memcpy(Rarr, &arr[q+1], sizeof(int) * n2);
	//循环，从下标p到r
	for (i = p; i <= r; i++){
		//如果左边第一个数据较小，copy到arr
		if(Larr[m] <= Rarr[n]){
			arr[i] = Larr[m];
			//copy完将m+1
			m++;
			//m超出数组最大长度，将Rarr剩下部分copy到arr，然后跳出循环。
			if(m >= n1){
				while(++i <= r){
					arr[i] = Rarr[n++];
				}
				//memcpy(&arr[i+1], &Rarr[n], n2-n);
				break;
			}

		}
		//如果右边第一个数据较小，copy到arr
		else{
			arr[i] = Rarr[n];
			n++;
			//n超出数组最大长度，将Larr剩下部分copy到arr
			if(n >= n2){
				while(++i <= r){
					arr[i] = Larr[m++];
				}
				//memcpy(&arr[i+1], &Larr[m], n1-m);
				break;
			}
		}
	
	}

	free(Larr);
	free(Rarr);
	return 0;

}
/*	归并排序
	arr:数组
	p:左下标
	r:右下标
*/
int merge_sort(int *arr, int p, int r){

	//如果只有一个数据，就退出。
	if(p >= r) return -1;
	//递归循环左半部
	merge_sort(arr, p, (p + r)/2);
	//递归循环右半部
	merge_sort(arr, (p + r)/2 + 1, r);
	//左右合并
	merge(arr, p , (p + r)/2, r);

	return 0;
}

//算法导论习题2.1-2
int insert_sort(int *arr, int len){
	//数组元素个数小于2就退出
	if(len < 2) return -1;
	
	int i = 1, j = 0, key = 0;
	//循环，从数组第二个元素开始，直到最后一个元素
	for(i = 1; i < len; i++){
		
		//暂时保存当前要排序的元素
		key = arr[i];
		
		//此下标赋值为当前排序元素的前一个下标
		j = i - 1;

		//循环，比较当前排序元素和下标为j的元素
		while(arr[j] < key){
			//key较大，则向后移动下标j的元素
			arr[j + 1] = arr[j];
			j--;
			//最后一个元素已经比较完
			if(j < 0) break;
		}
		//将当前要排序的元素key，赋值给下标j+1的位置
		arr[j+1] = key;
	}

	return 0;
}

/*
	思考题2-4

*/

int inversion_number_sum(int *arr, int p, int q, int r){

	int m  = 0, n = 0, i = 0;
	int n1 = q - p + 1;
	int n2 = r - q;
	int num = 0;
	//申请动态内存
	int *Larr = calloc(sizeof(int),  n1);
	int *Rarr = calloc(sizeof(int),  n2);
	//将左半部copy到Larr
	memcpy(Larr, &arr[p], sizeof(int) * n1);
	//右半部copy到Rarr
	memcpy(Rarr, &arr[q+1], sizeof(int) * n2);
	//循环，从下标p到r
	for (i = p; i <= r; i++){
		//如果左边第一个数据较小，copy到arr
		if(Larr[m] <= Rarr[n]){
			arr[i] = Larr[m];
			//copy完将m+1
			m++;
			//m超出数组最大长度，将Rarr剩下部分copy到arr，然后跳出循环。
			if(m >= n1){
				while(++i <= r){
					arr[i] = Rarr[n++];
				}
				//memcpy(&arr[i+1], &Rarr[n], n2-n);
				break;
			}

		}
		//如果右边第一个数据较小，copy到arr
		else{
			arr[i] = Rarr[n];
			n++;
			num += n1 - m;
			//n超出数组最大长度，将Larr剩下部分copy到arr
			if(n >= n2){
				while(++i <= r){
					arr[i] = Larr[m++];
				}
				//memcpy(&arr[i+1], &Larr[m], n1-m);
				break;
			}
		}
	
	}

	free(Larr);
	free(Rarr);
	return num;

}

int recursive_inversion_number_sum(int *arr, int p, int r){

	if(p >= r) return 0;

	int number = 0;
	int q = (p+r)/2;
	number += recursive_inversion_number_sum(arr, p, q);
	number += recursive_inversion_number_sum(arr, q+1, r);
	number += inversion_number_sum(arr, p, q, r);
	return number;
}
int main(int argc, char ** argv){
	int arr[5] = {2,1,5,3,2};
	int arr1[8] = {8,7,6,5,1,2,3,4};
	int num = 0;
	struct	timeval ts,te;
	int *buf = NULL;
	int i = 0;

	buf = (int*)calloc(sizeof(int),BUFSIZE);
	if(!buf) return 0;

	for(i=0; i<BUFSIZE; i++){
		buf[i] = BUFSIZE-i;
	}
	//选择排序
	//select_sort(arr, sizeof(arr)/sizeof(int));

	//归并排序
	//merge_sort(arr, 0, sizeof(arr)/sizeof(int) - 1);
	FUNC_TIME_SPEC(merge_sort(buf, 0, BUFSIZE - 1));

	//递归插入排序
	//recursive_insert_sort(arr, sizeof(arr)/sizeof(int));

	//插入排序
	//insert_sort(arr, sizeof(arr)/sizeof(int));
	
	//逆序对
	//num = recursive_inversion_number_sum(arr, 0, sizeof(arr)/sizeof(int)-1);

	free(buf);
	return 0;
}
