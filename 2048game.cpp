#include <stdio.h>
#include <stdlib.h>
/*
�ŧi�@�ӫ��Ы��A���}�C�A0~15�����O��2048�����|�Ӯ�l 
----------------------------
|  0  |   1  |   2  |   3  |
----------------------------
|  4  |   5  |   6  |   7  |
----------------------------
|  8  |   9  |  10  |  11  |
----------------------------
|  12 |  13  |  14  |  15  |
----------------------------
*/
int array_2048[16]={0};//���2048�C�����e 
int record_array_2048[16]={0};//�����W�@�B��2048�C�����e 
int now_array_2048[16]={0};//�����o�@�B��2048�C�����e 
void random_generate_2_or_4()
{
	
}
void *combine(int *a, int *b, int *c, int *d)	//�X�֥��N�@��row�Τ@�Ccolumn���|�ӼƦr�A�Ѳĥ|�����Ĥ@���X�� 
{
	int arr[4]={*a,*b,*c,*d};
	int non_zero_arr[4]={0};
	int combine_arr[4]={0};
	int i,j = 0 ;
	int check_combine = 0 ; //�����X�֦��� 
	for( i = 0 ; i < 4 ; i++ ) //�����Ʀr���ʡA�o��s���}�C�A���}�C�w�g�N�D0�Ʀr�V�Ĥ@�����ʡA��0�h���ĥ|������ 
	{
		if (arr[i] != 0)
		{
			non_zero_arr[j] = arr[i] ;
			j++;
		}
	} 	
	if( non_zero_arr[0]==non_zero_arr[1] && non_zero_arr[2]==non_zero_arr[3] )    //�ˬd�O�_�����i�X�֪����p�A�������~�u�i��X�֤@�աA
	{																			  //�]���X�᪺֫�Ʀr������A�Q�X�֡A�X�᪺֫�Φ���[x,y,0,0] 
		combine_arr[0] = non_zero_arr[0]*2 ;
		combine_arr[1] = non_zero_arr[2]*2 ;
		check_combine = 2 ;
	}
	else
	{
		for( i = 0 ; i < 3 ; i++ )    //�u����@�ռƦr�i�H�X�֪����p�A�u���H�Ĥ@�B�G���X�֡A�A�ӬO�G�B�T���X�֡A�̫�~�O�X�֤T�B�|���A
		{							  //�T�O0�q�ĥ|���}�l�X�{�A�D0�Ʀr�q�Ĥ@���}�l�X�{ 
			if (non_zero_arr[i] == non_zero_arr[i+1]) //�Y���X�֪����p�X�{�A�̦h�u���T���D0 
			{
				combine_arr[i] = non_zero_arr[i]*2 ;
				combine_arr[(i+1)%3] = non_zero_arr[(i+2)%4] ;
				combine_arr[(i+2)%3] = non_zero_arr[(i+3)%4] ;
				check_combine = 1 ;
				break;	 			  //��쭫�Ʀa�N���X�A�]���h���S�ҫ�u�|���@�խ��ơA�קK���ƭp�� 
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

void up()
{
	combine(array_2048+0,array_2048+4,array_2048+8,array_2048+12);//0 4 8 12
	combine(array_2048+1,array_2048+5,array_2048+9,array_2048+13);//1 5 9 13
	combine(array_2048+2,array_2048+6,array_2048+10,array_2048+14);//2 6 10 14
	combine(array_2048+3,array_2048+7,array_2048+11,array_2048+15);//3 7 11 15
}

void right()
{
	combine(array_2048+3,array_2048+2,array_2048+1,array_2048+0);//3 2 1 0
	combine(array_2048+7,array_2048+6,array_2048+5,array_2048+4);//7 6 5 4
	combine(array_2048+11,array_2048+10,array_2048+9,array_2048+8);//11 10 9 8
	combine(array_2048+15,array_2048+14,array_2048+13,array_2048+12);//15 14 13 12
	
}

void down()
{
	combine(array_2048+12,array_2048+8,array_2048+4,array_2048+0);//12 8 4 0
	combine(array_2048+13,array_2048+9,array_2048+5,array_2048+1);//13 9 5 1
	combine(array_2048+14,array_2048+10,array_2048+6,array_2048+2);//14 10 6 2
	combine(array_2048+15,array_2048+11,array_2048+7,array_2048+3);//15 11 7 3
}

void left()
{
	combine(array_2048+0,array_2048+1,array_2048+2,array_2048+3);//0 1 2 3
	combine(array_2048+4,array_2048+5,array_2048+6,array_2048+7);//4 5 6 7
	combine(array_2048+8,array_2048+9,array_2048+10,array_2048+11);//8 9 10 11
	combine(array_2048+12,array_2048+13,array_2048+14,array_2048+15);//12 13 14 15
}
void record()//�����W�@�B 
{
	int i = 0;
	for (i=0;i<16;i++)
	{
		*(record_array_2048+i)=*(array_2048+i);
	}
}
void record_now()//�����o�@�B 
{
	int i = 0;
	for (i=0;i<16;i++)
	{
		*(now_array_2048+i)=*(array_2048+i);
	}
}

void back_to_record()//�^�����(�W�@�B) 
{
	int i = 0;
	for (i=0;i<16;i++)
	{		
		*(array_2048+i)=*(record_array_2048+i);
	}
} 
void back_to_now()//�^�����(�o�@�B) 
{
	int i = 0;
	for (i=0;i<16;i++)
	{		
		*(array_2048+i)=*(record_array_2048+i);
	}
} 

int compare_with_now()//��o�@�B�������e�M2048�C�����e������æ^�ǵ��G�A1�N���@�ˡA0�N��@��
{
	int i = 0;
	for (i=0;i<16;i++)
	{
		if(*(record_array_2048+i)!=*(array_2048+i))
		{
			return 1 ;
		}
	}
	return 0;
}
int check_end()//�ˬd�O�_�C�������æ^�ǵ��G�A1�N��C�������A0�N���٥i�H�~�� 
{
	record();
	record_now();
	up();	
	if (compare_with_record() == 1){
		return 1;
	}
	back_to_now()
	right();
	if (compare_with_record() == 1){
		return 1;
	}
	back_to_now()
	down();
	if (compare_with_record() == 1){
		return 1;
	}
	back_to_now()
	left();
	if (compare_with_record() == 1){
		return 1;
	}
	back_to_now()
	return 0 ;
}

void show()//�L�X2048�C�����e 
{
	printf("-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+0),*(array_2048+1),*(array_2048+2),*(array_2048+3));
	printf("-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+4),*(array_2048+5),*(array_2048+6),*(array_2048+7));
	printf("-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+8),*(array_2048+9),*(array_2048+10),*(array_2048+11));
	printf("-------------------------\n");
	printf("|%5d|%5d|%5d|%5d|\n",*(array_2048+12),*(array_2048+13),*(array_2048+14),*(array_2048+15));
	printf("-------------------------\n");
}
int main()
{
} 

