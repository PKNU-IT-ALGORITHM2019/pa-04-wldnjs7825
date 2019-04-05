#include<stdio.h>
#include<stdlib.h>
#include<time.h>
double BubbleSort(int a[], int n);
double SelectionSort(int a[], int n);
double InsertionSort(int a[], int n);
double MergeSort(int a[], int p, int r);
void Merge(int a[], int first, int m, int last);
double QuickSort(int a[], int first, int last);
int Partition(int a[], int first, int last);
double QuickSort_m(int a[], int first, int last);
int Partition_m(int a[], int first, int last);
double QuickSort_r(int a[], int first, int last);
int Partition_r(int a[], int first, int last);
void Max_Heapify(int a[], int root, int heap_size);
void Build_Max_Heap(int a[], int n);
double HeapSort(int a[], int heap_size);


void Reset(int n);
void swap(int a[], int i, int max);

clock_t start, stop;
int tmp;
int temp[100000]; //merge함수를 위한 추가배열
double playtime[9][6]; //0.bubble 1.selection 2.insertion 3.merge 4.quick 5.quick_m 6.quick_r 7.heap 8.qsort
int rev_1000[1000];//거꾸로 정렬
int rev_10000[10000];
int rev_100000[100000];
int rand_1000[1000];//랜덤 정렬
int rand_10000[10000];
int rand_100000[100000];

typedef struct {
	int num;
}Num;

Num member_rev1000[1000];
Num member_rev10000[10000];
Num member_rev100000[100000];
Num member_rand1000[1000];
Num member_rand10000[10000];
Num member_rand100000[100000];

void Reset(int n) //1.rev초기화 2.rand초기화
{
	int num1 = 1000, num2 = 10000, num3 = 100000;
	if (n == 1)
	{
		for (int i = 0; i < num1; i++)
		{	
			rev_1000[i] = num1 - i;
			member_rev1000[i].num = num1 - i;
		}
		for (int i = 0; i < num2; i++)
		{
			rev_10000[i] = num2 - i;
			member_rev10000[i].num = num2 - i;
		}
		for (int i = 0; i < num3; i++)
		{
			rev_100000[i] = num3 - i;
			member_rev100000[i].num = num3 - i;
		}
	}
	else if (n == 2)
	{
		for (int i = 0; i < num1; i++)
		{
			rand_1000[i] = rand() % num1 + 1;
			member_rand1000[i].num = num1 - i;
		}
		for (int i = 0; i < num2; i++)
		{
			rand_10000[i] = rand() % num2 + 1;
			member_rand10000[i].num = num2 - i;

		}
		for (int i = 0; i < num3; i++)
		{
			rand_100000[i] = rand() % num3 + 1;
			member_rand100000[i].num = num3 - i;
		}
	}	
	
}

void swap(int a[], int i, int max)
{
	tmp = a[i];
	a[i] = a[max];
	a[max] = tmp;
}

double BubbleSort(int a[], int n) {
	start = clock();
	for (int i = n; i > 1; i--) //n-1번 반복
	{
		for (int j = 0; j < i - 1; j++)
		{
			if (a[j] > a[j + 1])
				swap(a, j, j + 1);
		}
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

double SelectionSort(int a[], int n) {
	start = clock();
	int max = 0;
	int j = 0;
	int max_index = 0;
	for (int i = n - 1; i > 0; i--)
	{
		max = i;
		for (j = 0; j <= i; j++)
		{
			if (a[j] > a[max])
				max = j;
		}
		swap(a, i, max);
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

double InsertionSort(int a[], int n)
{
	start = clock();
	for (int i = 1; i < n; i++)
	{
		tmp = a[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (tmp < a[j])
			{
				a[j + 1] = a[j];
				if (j == 0)
					a[j] = tmp;
			}
			else
			{
				a[j + 1] = tmp;
				break;
			}
		}
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

double MergeSort(int a[], int first, int last) //first = 0; last = 999;
{
	start = clock();
	int m;
	if (first < last)
	{
		m = (first + last) / 2;
		MergeSort(a, first, m);
		MergeSort(a, m + 1, last);
		Merge(a, first, m, last);
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

void Merge(int a[], int first, int m, int last) //정렬되어 있는 두 배열을 합함
{
	int i = first;
	int j = m + 1;
	int cnt = 0;

	while (i <= m && j <= last)
	{
		if (a[i] <= a[j])
			temp[cnt++] = a[i++];
		else
			temp[cnt++] = a[j++];
	}
	while (i <= m)
		temp[cnt++] = a[i++];
	while (j <= last)
		temp[cnt++] = a[j++];
	for (int k = 0; k < cnt; k++)
		a[first++] = temp[k];
}

double QuickSort(int a[], int first, int last) //마지막 값을 피봇으로 선택
{
	start = clock();
	if (first < last)
	{
		int m = Partition(a, first, last);
		QuickSort(a, first, m - 1);
		QuickSort(a, m + 1, last);
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

int Partition(int a[], int first, int last)
{
	int pivot = a[last]; //pivot
	int i = first - 1; //pivot보다 작은 값들 중 마지막 값
	for (int j = first; j < last; j++) //j가 지금 검사 하려는 값
	{
		if (a[j] < pivot)
		{
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, last);

	return i + 1;//pivot을 반환
}

double QuickSort_m(int a[], int first, int last)//중간값을 피봇으로 선택
{
	start = clock();
	if (first < last)
	{
		int m = Partition_m(a, first, last);
		QuickSort_m(a, first, m - 1);
		QuickSort_m(a, m + 1, last);
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

int Partition_m(int a[], int first, int last)
{

	int i = first - 1; //pivot보다 작은 값들 중 마지막 값
	int m = (first + last) / 2;
	if ((a[first] >= a[last] && a[first] <= a[m]) || (a[first] <= a[last] && a[first] >= a[m]))
		swap(a, first, last);
	else if ((a[m] >= a[first] && a[m] <= a[last]) || (a[m] <= a[first] && a[m] >= a[last]))
		swap(a, m, last);
	int pivot = a[last];

	for (int j = first; j < last; j++) //j가 지금 검사 하려는 값
	{
		if (a[j] < pivot)
		{
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, last);

	return i + 1;//pivot을 반환
}

double QuickSort_r(int a[], int first, int last)//랜덤값을 피봇으로 선택
{
	start = clock();
	if (first < last)
	{
		int m = Partition_r(a, first, last);
		QuickSort_r(a, first, m - 1);
		QuickSort_r(a, m + 1, last);
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

int Partition_r(int a[], int first, int last)
{
	int r = a[rand() % (last - first + 1) + first];
	int i = first - 1; //pivot보다 작은 값들 중 마지막 값

	swap(a, r, last);
	int pivot = a[last];

	for (int j = first; j < last; j++) //j가 지금 검사 하려는 값
	{
		if (a[j] < pivot)
		{
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, last);

	return i + 1;//pivot을 반환
}

void Max_Heapify(int a[], int root, int heap_size)
{
	int child;
	if (root >= heap_size / 2)
		return;
	if ((root * 2 + 1) != heap_size - 1)
	{
		if (a[root * 2 + 1] >= a[root * 2 + 2])
			child = root * 2 + 1;
		else
			child = root * 2 + 2;
	}
	else
		child = root * 2 + 1;

	if (a[child] > a[root])
		swap(a, child, root);
	else
		return;
	Max_Heapify(a, child, heap_size);
	return;
}

void Build_Max_Heap(int a[], int heap_size)
{
	for (int root = heap_size / 2 - 1; root >= 0; root--)
		Max_Heapify(a, root, heap_size);
}

double HeapSort(int a[], int heap_size)
{
	start = clock();
	Build_Max_Heap(a, heap_size);
	for (int i = heap_size - 1; i >= 1; i--)
	{
		swap(a, 0, i);
		heap_size--;
		Max_Heapify(a, 0, heap_size);
	}
	stop = clock();
	return ((double)stop - start) / 1000;
}

int CompareByNum(const void *v1, const void *v2)
{
	const Num *m1 = (const Num *)v1;
	const Num *m2 = (const Num *)v2;
	return m1->num - m2->num;
}

int main() {
	srand(time(NULL));
	double sum1 = 0, sum2 = 0, sum3 = 0;

	Reset(1);	
	playtime[0][0] = BubbleSort(rev_1000, 1000);
	playtime[0][2] = BubbleSort(rev_10000, 10000);
    //playtime[0][4] = BubbleSort(rev_100000, 100000);
	for (int i = 0; i < 10; i++) {
		Reset(2); 
		sum1 += BubbleSort(rand_1000, 1000);
		sum2 += BubbleSort(rand_10000, 10000);
		//sum3 += BubbleSort(rand_100000, 100000); 
	}
	playtime[0][1] = sum1 / 10; sum1 = 0;
	playtime[0][3] = sum2 / 10; sum2 = 0;
	playtime[0][5] = sum3 / 10; sum3 = 0;
	
	Reset(1);
	playtime[1][0] = SelectionSort(rev_1000, 1000);
	playtime[1][2] = SelectionSort(rev_10000, 10000);
	//playtime[1][4] =  SelectionSort(rev_100000, 100000);
	for (int i = 0; i < 10; i++) {
		Reset(2);
		sum1 += SelectionSort(rand_1000, 1000);
		sum2 += SelectionSort(rand_10000, 10000);
		//sum3 +=  SelectionSort(rand_100000, 100000); 
	}
	playtime[1][1] = sum1 / 10; sum1 = 0;
	playtime[1][3] = sum2 / 10; sum2 = 0;
	playtime[1][5] = sum3 / 10; sum3 = 0;

	Reset(1);
	playtime[2][0] = InsertionSort(rev_1000, 1000);
	playtime[2][2] = InsertionSort(rev_10000, 10000);
	//playtime[2][4] = InsertionSort(rev_100000, 100000);
	for (int i = 0; i < 10; i++) {
		Reset(2);
		sum1 += InsertionSort(rand_1000, 1000);
		sum2 += InsertionSort(rand_10000, 10000);
		//sum3 += InsertionSort(rand_100000, 100000); 
	}
	playtime[2][1] = sum1 / 10; sum1 = 0;
	playtime[2][3] = sum2 / 10; sum2 = 0;
	playtime[2][5] = sum3 / 10; sum3 = 0;


	Reset(1);
	playtime[3][0] = MergeSort(rev_1000, 0, 999);
	playtime[3][2] = MergeSort(rev_10000, 0, 9999);
	playtime[3][4] = MergeSort(rev_100000, 0, 99999);
	for (int i = 0; i < 10; i++) {
		Reset(2);
		sum1 += MergeSort(rand_1000, 0, 999);
		sum2 += MergeSort(rand_10000, 0, 9999);
		sum3 += MergeSort(rand_100000, 0, 99999);
	}
	playtime[3][1] = sum1 / 10; sum1 = 0;
	playtime[3][3] = sum2 / 10; sum2 = 0;
	playtime[3][5] = sum3 / 10; sum3 = 0;

	Reset(1);
	playtime[4][0] = QuickSort(rev_1000, 0, 999);
	//playtime[4][2] = QuickSort(rev_10000, 0, 9999);
	//playtime[4][4] = QuickSort(rev_100000, 0, 99999);
	for (int i = 0; i < 10; i++) {
		Reset(2);
		sum1 += QuickSort(rand_1000, 0, 999);
		sum2 += QuickSort(rand_10000, 0, 9999);
		sum3 += QuickSort(rand_100000, 0, 99999);
	}
	playtime[4][1] = sum1 / 10; sum1 = 0;
	playtime[4][3] = sum2 / 10; sum2 = 0;
	playtime[4][5] = sum3 / 10; sum3 = 0;

	Reset(1);
	playtime[5][0] = QuickSort_m(rev_1000, 0, 999);
	playtime[5][2] = QuickSort_m(rev_10000, 0, 9999);
	playtime[5][4] = QuickSort_m(rev_100000, 0, 99999);
	for (int i = 0; i < 10; i++) {
		Reset(2);
		sum1 += QuickSort_m(rand_1000, 0, 999);
		sum2 += QuickSort_m(rand_10000, 0, 9999);
		sum3 += QuickSort_m(rand_100000, 0, 99999);
	}
	playtime[5][1] = sum1 / 10; sum1 = 0;
	playtime[5][3] = sum2 / 10; sum2 = 0;
	playtime[5][5] = sum3 / 10; sum3 = 0;

	Reset(1);
	playtime[6][0] = QuickSort_r(rev_1000, 0, 999);
	playtime[6][2] = QuickSort_r(rev_10000, 0, 9999);
	playtime[6][4] = QuickSort_r(rev_100000, 0, 99999);
	for (int i = 0; i < 10; i++) {
		Reset(2);
		sum1 += QuickSort_r(rand_1000, 0, 999);
		sum2 += QuickSort_r(rand_10000, 0, 9999);
		sum3 += QuickSort_r(rand_100000, 0, 99999);
	}
	playtime[6][1] = sum1 / 10; sum1 = 0;
	playtime[6][3] = sum2 / 10; sum2 = 0;
	playtime[6][5] = sum3 / 10; sum3 = 0;
	
	Reset(1);
	playtime[7][0] = HeapSort(rev_1000, 1000); 
	playtime[7][2] = HeapSort(rev_10000, 10000); 
	playtime[7][4] = HeapSort(rev_100000, 100000);
	for (int i = 0; i < 10; i++) {
		Reset(2);
		sum1 += HeapSort(rand_1000, 1000);
		sum2 += HeapSort(rand_10000, 10000);
		sum3 += HeapSort(rand_100000, 100000);
	}
	playtime[7][1] = sum1 / 10; sum1 = 0;
	playtime[7][3] = sum2 / 10; sum2 = 0;
	playtime[7][5] = sum3 / 10; sum3 = 0;
	
	Reset(1);
	start = clock();
	qsort(member_rev1000, 1000, sizeof(Num), CompareByNum);
	stop = clock();
	playtime[8][0] = ((double)stop - start) / 1000;
	start = clock();
	qsort(member_rev10000, 10000, sizeof(Num), CompareByNum);
	stop = clock();
	playtime[8][2] = ((double)stop - start) / 1000;
	start = clock();
	qsort(member_rev100000, 100000, sizeof(Num), CompareByNum);
	stop = clock();
	playtime[8][4] = ((double)stop - start) / 1000;
	for (int i = 0; i < 10; i++) {
		Reset(2);
		start = clock();
		qsort(member_rand1000, 1000, sizeof(Num), CompareByNum);
		stop = clock();
		sum1 += ((double)stop - start) / 1000;
		start = clock();
		qsort(member_rand10000, 10000, sizeof(Num), CompareByNum);
		stop = clock();
		sum2 += ((double)stop - start) / 1000;
		start = clock();
		qsort(member_rand100000, 100000, sizeof(Num), CompareByNum);
		stop = clock();
		sum3 += ((double)stop - start) / 1000;
	}
	playtime[8][1] = sum1 / 10; sum1 = 0;
	playtime[8][3] = sum2 / 10; sum2 = 0;
	playtime[8][5] = sum3 / 10; sum3 = 0;

	

	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("\t\tReverse1000\tRandom1000\tReverse10000\tRandom10000\tReverse100000\tRandom100000\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("Bubble\t\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[0][i]); printf("\n");
	printf("Selection\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[1][i]); printf("\n");
	printf("Insertion\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[2][i]); printf("\n");
	printf("Merge\t\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[3][i]); printf("\n");
	printf("Quick1\t\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[4][i]); printf("\n");
	printf("Quick2\t\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[5][i]); printf("\n");
	printf("Quick3\t\t");
	for (int i = 0; i < 6; i++)
	printf(" %f\t", playtime[6][i]); printf("\n");
	printf("Heap\t\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[7][i]); printf("\n");
	printf("Qsort\t\t");
	for (int i = 0; i < 6; i++)
		printf(" %f\t", playtime[8][i]); printf("\n");

	return 0;
}