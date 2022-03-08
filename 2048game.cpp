#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <conio.h>
/*
宣告一個指標型態的陣列，0~15項分別為2048中的四個格子 
----------------------------
|  0  |   1  |   2  |   3  |
----------------------------
|  4  |   5  |   6  |   7  |
----------------------------
|  8  |   9  |  10  |  11  |
----------------------------
|  12 |  13  |  14  |  15  |
----------------------------

規則：

1.  遊戲開始時生成兩個數字。 
2.  生成的數字可能為2或4，2的出現機率=90%，4的出現機率=10%。 
3.  每次移動可選擇上下左右之中的一個方向。 
4.  移動後會在空格處隨機生成一個數字，生成方法同規則2。
5.  移動時，會將所有數字往移動的方向進行移動與兩兩合併，合併後的數字不會再進行重複合併
6.  若出現(2,2,2,0)的情況時，往左方移動會出現(4,2,0,0)，而不是(2,4,0,0)，左邊的會先合併 

功能表：

1.  random_generate_2_or_4()  //隨機在棋盤中生成2或4 
2.  *combine(int *a, int *b, int *c, int *d)  //合併一行數字
3.  record()  //紀錄上一步 
4.  record_now()  //暫存現在局面 
5.  back_to_record()  //回到上一步 
6.  back_to_now()  //回到移動前局面 
7.  compare_with_now()  //將移動後的局面和移動前的局面比較，1代表不一樣，0代表一樣
8.  show()  //印出現在局面 
9.  up()  //向上移 
10. right()  //向右移 
11. down()  //向下移 
12. left()  //向左移 
13. check_end()  //檢查是否遊戲結束並回傳結果，1代表遊戲結束，0代表還可以繼續玩  

功能關係表： 

1.  包含：
2.  包含：  
3.  包含：  
4.  包含：  
5.  包含： 
6.  包含：
7.  包含：  
8.  包含：
9.  包含：1.2.4.7.  
10. 包含：1.2.4.7.
11. 包含：1.2.4.7.
12. 包含：1.2.4.7.
13. 包含：4.6.7.9.10.11.12.
*/
int array_2048[16]={0};//實際2048遊戲內容 
int record_array_2048[16]={0};//紀錄上一步的2048遊戲內容 
int now_array_2048[16]={0};//紀錄這一步的2048遊戲內容 
void random_generate_2_or_4()
{
	int flag = 0 ;
    int num = 0 ;
    srand(time(NULL));
	while (!flag)
	{
		num = rand()%16 ;
		if (array_2048[num] == 0)
		{
			array_2048[num] = 2 * (((rand()%10+1)/10)+1) ; //生成的數字可能為2或4，2的出現機率=90%，4的出現機率=10%
			flag = 1 ;
		}
	}	
}
void *combine(int *a, int *b, int *c, int *d)	//合併任意一排row或一列column的四個數字，由第四項往第一項合併 
{
	int arr[4]={*a,*b,*c,*d};
	int non_zero_arr[4]={0};
	int combine_arr[4]={0};
	int i,j = 0 ;
	int check_combine = 0 ; //紀錄合併次數 
	for( i = 0 ; i < 4 ; i++ ) //完成數字移動，得到新的陣列，此陣列已經將非0數字向第一項移動，而0則往第四項移動 
	{
		if (arr[i] != 0)
		{
			non_zero_arr[j] = arr[i] ;
			j++;
		}
	} 	
	if( non_zero_arr[0]==non_zero_arr[1] && non_zero_arr[2]==non_zero_arr[3] )    //檢查是否為兩兩可合併的情況，除此之外只可能合併一組，
	{																			  //因為合併後的數字當次不能再被合併，合併後的形式為[x,y,0,0] 
		combine_arr[0] = non_zero_arr[0]*2 ;
		combine_arr[1] = non_zero_arr[2]*2 ;
		check_combine = 2 ;
	}
	else
	{
		for( i = 0 ; i < 3 ; i++ )    //只有恰一組數字可以合併的情況，優先以第一、二項合併，再來是二、三項合併，最後才是合併三、四項，
		{							  //確保0從第四項開始出現，非0數字從第一項開始出現 
			if (non_zero_arr[i] == non_zero_arr[i+1]) //若有合併的情況出現，最多只有三項非0 
			{
				combine_arr[i] = non_zero_arr[i]*2 ;
				combine_arr[(i+1)%3] = non_zero_arr[(i+2)%4] ;
				combine_arr[(i+2)%3] = non_zero_arr[(i+3)%4] ;
				check_combine = 1 ;
				break;	 			  //找到重複地就跳出，因為去除特例後只會有一組重複，避免重複計算 
			}
		}
	}
	if (check_combine == 0 )
	{	
		*a = *(non_zero_arr+0);
		*b = *(non_zero_arr+1);
		*c = *(non_zero_arr+2);
		*d = *(non_zero_arr+3);
		
	}
	else
	{
		*a = *(combine_arr+0);
		*b = *(combine_arr+1);
		*c = *(combine_arr+2);
		*d = *(combine_arr+3);
	} 	
}
void record()//紀錄上一步 
{
	int i = 0;
	for (i=0;i<16;i++)
	{
		*(record_array_2048+i)=*(now_array_2048+i);
	}
}
void record_now()//紀錄移動前的局面 
{
	int i = 0;
	for (i=0;i<16;i++)
	{
		*(now_array_2048+i)=*(array_2048+i);
	}
}
void back_to_record()//回到紀錄(上一步) 
{
	int i = 0;
	for (i=0;i<16;i++)
	{		
		*(array_2048+i)=*(record_array_2048+i);
	}
} 
void back_to_now()//回到移動前的局面 
{
	int i = 0;
	for (i=0;i<16;i++)
	{		
		*(array_2048+i)=*(now_array_2048+i);
	}
} 
int compare_with_now()//將移動後的局面和移動前的局面比較，1代表不一樣，0代表一樣
{
	int i = 0;
	for (i=0;i<16;i++)
	{
		if(*(now_array_2048+i)!=*(array_2048+i))
		{
			return 1 ;
		}
	}
	return 0;
}
void show()//印出2048遊戲內容 
{
	printf("\n-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+0),*(array_2048+1),*(array_2048+2),*(array_2048+3));
	printf("-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+4),*(array_2048+5),*(array_2048+6),*(array_2048+7));
	printf("-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+8),*(array_2048+9),*(array_2048+10),*(array_2048+11));
	printf("-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+12),*(array_2048+13),*(array_2048+14),*(array_2048+15));
	printf("-------------------------\n");
}
void up()
{
	record_now();
	combine(array_2048+0,array_2048+4,array_2048+8,array_2048+12);//0 4 8 12
	combine(array_2048+1,array_2048+5,array_2048+9,array_2048+13);//1 5 9 13
	combine(array_2048+2,array_2048+6,array_2048+10,array_2048+14);//2 6 10 14
	combine(array_2048+3,array_2048+7,array_2048+11,array_2048+15);//3 7 11 15
	if (compare_with_now()==1) //如果局面有改變，就隨機生成數字，並印出局面 
	{
		random_generate_2_or_4();
	}
	else //如果局面沒有改變，就顯示訊息 
	{
		printf("不能往上\n");
	}
}
void right()
{
	record_now();
	combine(array_2048+3,array_2048+2,array_2048+1,array_2048+0);//3 2 1 0
	combine(array_2048+7,array_2048+6,array_2048+5,array_2048+4);//7 6 5 4
	combine(array_2048+11,array_2048+10,array_2048+9,array_2048+8);//11 10 9 8
	combine(array_2048+15,array_2048+14,array_2048+13,array_2048+12);//15 14 13 12
	if (compare_with_now()==1) //如果局面有改變，就隨機生成數字，並印出局面 
	{
		random_generate_2_or_4();
	}
	else //如果局面沒有改變，就顯示訊息 
	{
		printf("不能往右\n");
	}
}
void down()
{
	record_now();
	combine(array_2048+12,array_2048+8,array_2048+4,array_2048+0);//12 8 4 0
	combine(array_2048+13,array_2048+9,array_2048+5,array_2048+1);//13 9 5 1
	combine(array_2048+14,array_2048+10,array_2048+6,array_2048+2);//14 10 6 2
	combine(array_2048+15,array_2048+11,array_2048+7,array_2048+3);//15 11 7 3
	if (compare_with_now()==1) //如果局面有改變，就隨機生成數字，並印出局面 
	{
		random_generate_2_or_4();
	}
	else //如果局面沒有改變，就顯示訊息 
	{
		printf("不能往下\n");
	}
}
void left()
{
	record_now();
	combine(array_2048+0,array_2048+1,array_2048+2,array_2048+3);//0 1 2 3
	combine(array_2048+4,array_2048+5,array_2048+6,array_2048+7);//4 5 6 7
	combine(array_2048+8,array_2048+9,array_2048+10,array_2048+11);//8 9 10 11
	combine(array_2048+12,array_2048+13,array_2048+14,array_2048+15);//12 13 14 15
	if (compare_with_now()==1) //如果局面有改變，就隨機生成數字，並印出局面 
	{
		random_generate_2_or_4();
	}
	else //如果局面沒有改變，就顯示訊息 
	{
		printf("不能往左\n");
	}
}
void check_end()//檢查是否遊戲結束，如果遊戲結束就顯示遊戲結束，否則不做任何動作(上下左右各跑一遍，如果都沒變就代表遊戲結束)
{
	record_now();//暫存移動前的局面 
	int i = 0 ;
	up();	//往上 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();
	right();//往右 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();
	down();//往下 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();
	left();//往左 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();//回到移動前的局面 
	if(i==0)
	{		
		printf("遊戲結束");	
	}
}
int main()
{
	random_generate_2_or_4();
	random_generate_2_or_4();
	show();	
	int ch1 = 0 ;
	int ch2 = 0 ;
	while(1)
	{
		printf("請輸入按鍵\n");
		if(ch1=getch())//使用getch來取得鍵盤指令，如果是上下左右的話，會一次回傳兩個值，第一個值皆為224，要根據第二個值才能判斷上下左右 
		{
			if (ch1 == 224)
			{
				ch2 = getch();
				switch(ch2)
				{
				case 72 : 
					printf("上\n"); 					
					up();
					show();
					break;
				case 80 : 
					printf("下\n"); 
					down();
					show();
					break;
				case 75 : 
					printf("左\n"); 
					left();
					show();
					break;
				case 77 : 
					printf("右\n"); 
					right();
					show();
					break;
				default : 
					printf("無效按鍵\n"); 
					break; 
				}
				check_end();	
			}
			else
			{
				printf("無效按鍵\n"); 
			}
    	} 
	}
} 
