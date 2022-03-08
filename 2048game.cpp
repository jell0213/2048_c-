#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <conio.h>
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

�W�h�G

1.  �C���}�l�ɥͦ���ӼƦr�C 
2.  �ͦ����Ʀr�i�ର2��4�A2���X�{���v=90%�A4���X�{���v=10%�C 
3.  �C�����ʥi��ܤW�U���k�������@�Ӥ�V�C 
4.  ���ʫ�|�b�Ů�B�H���ͦ��@�ӼƦr�A�ͦ���k�P�W�h2�C
5.  ���ʮɡA�|�N�Ҧ��Ʀr�����ʪ���V�i�沾�ʻP���X�֡A�X�᪺֫�Ʀr���|�A�i�歫�ƦX��
6.  �Y�X�{(2,2,2,0)�����p�ɡA�����貾�ʷ|�X�{(4,2,0,0)�A�Ӥ��O(2,4,0,0)�A���䪺�|���X�� 

�\���G

1.  random_generate_2_or_4()  //�H���b�ѽL���ͦ�2��4 
2.  *combine(int *a, int *b, int *c, int *d)  //�X�֤@��Ʀr
3.  record()  //�����W�@�B 
4.  record_now()  //�Ȧs�{�b���� 
5.  back_to_record()  //�^��W�@�B 
6.  back_to_now()  //�^�첾�ʫe���� 
7.  compare_with_now()  //�N���ʫ᪺�����M���ʫe����������A1�N���@�ˡA0�N��@��
8.  show()  //�L�X�{�b���� 
9.  up()  //�V�W�� 
10. right()  //�V�k�� 
11. down()  //�V�U�� 
12. left()  //�V���� 
13. check_end()  //�ˬd�O�_�C�������æ^�ǵ��G�A1�N��C�������A0�N���٥i�H�~��  

�\�����Y��G 

1.  �]�t�G
2.  �]�t�G  
3.  �]�t�G  
4.  �]�t�G  
5.  �]�t�G 
6.  �]�t�G
7.  �]�t�G  
8.  �]�t�G
9.  �]�t�G1.2.4.7.  
10. �]�t�G1.2.4.7.
11. �]�t�G1.2.4.7.
12. �]�t�G1.2.4.7.
13. �]�t�G4.6.7.9.10.11.12.
*/
int array_2048[16]={0};//���2048�C�����e 
int record_array_2048[16]={0};//�����W�@�B��2048�C�����e 
int now_array_2048[16]={0};//�����o�@�B��2048�C�����e 
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
			array_2048[num] = 2 * (((rand()%10+1)/10)+1) ; //�ͦ����Ʀr�i�ର2��4�A2���X�{���v=90%�A4���X�{���v=10%
			flag = 1 ;
		}
	}	
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
void record()//�����W�@�B 
{
	int i = 0;
	for (i=0;i<16;i++)
	{
		*(record_array_2048+i)=*(now_array_2048+i);
	}
}
void record_now()//�������ʫe������ 
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
void back_to_now()//�^�첾�ʫe������ 
{
	int i = 0;
	for (i=0;i<16;i++)
	{		
		*(array_2048+i)=*(now_array_2048+i);
	}
} 
int compare_with_now()//�N���ʫ᪺�����M���ʫe����������A1�N���@�ˡA0�N��@��
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
void show()//�L�X2048�C�����e 
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
	if (compare_with_now()==1) //�p�G���������ܡA�N�H���ͦ��Ʀr�A�æL�X���� 
	{
		random_generate_2_or_4();
	}
	else //�p�G�����S�����ܡA�N��ܰT�� 
	{
		printf("���੹�W\n");
	}
}
void right()
{
	record_now();
	combine(array_2048+3,array_2048+2,array_2048+1,array_2048+0);//3 2 1 0
	combine(array_2048+7,array_2048+6,array_2048+5,array_2048+4);//7 6 5 4
	combine(array_2048+11,array_2048+10,array_2048+9,array_2048+8);//11 10 9 8
	combine(array_2048+15,array_2048+14,array_2048+13,array_2048+12);//15 14 13 12
	if (compare_with_now()==1) //�p�G���������ܡA�N�H���ͦ��Ʀr�A�æL�X���� 
	{
		random_generate_2_or_4();
	}
	else //�p�G�����S�����ܡA�N��ܰT�� 
	{
		printf("���੹�k\n");
	}
}
void down()
{
	record_now();
	combine(array_2048+12,array_2048+8,array_2048+4,array_2048+0);//12 8 4 0
	combine(array_2048+13,array_2048+9,array_2048+5,array_2048+1);//13 9 5 1
	combine(array_2048+14,array_2048+10,array_2048+6,array_2048+2);//14 10 6 2
	combine(array_2048+15,array_2048+11,array_2048+7,array_2048+3);//15 11 7 3
	if (compare_with_now()==1) //�p�G���������ܡA�N�H���ͦ��Ʀr�A�æL�X���� 
	{
		random_generate_2_or_4();
	}
	else //�p�G�����S�����ܡA�N��ܰT�� 
	{
		printf("���੹�U\n");
	}
}
void left()
{
	record_now();
	combine(array_2048+0,array_2048+1,array_2048+2,array_2048+3);//0 1 2 3
	combine(array_2048+4,array_2048+5,array_2048+6,array_2048+7);//4 5 6 7
	combine(array_2048+8,array_2048+9,array_2048+10,array_2048+11);//8 9 10 11
	combine(array_2048+12,array_2048+13,array_2048+14,array_2048+15);//12 13 14 15
	if (compare_with_now()==1) //�p�G���������ܡA�N�H���ͦ��Ʀr�A�æL�X���� 
	{
		random_generate_2_or_4();
	}
	else //�p�G�����S�����ܡA�N��ܰT�� 
	{
		printf("���੹��\n");
	}
}
void check_end()//�ˬd�O�_�C�������A�p�G�C�������N��ܹC�������A�_�h��������ʧ@(�W�U���k�U�]�@�M�A�p�G���S�ܴN�N��C������)
{
	record_now();//�Ȧs���ʫe������ 
	int i = 0 ;
	up();	//���W 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();
	right();//���k 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();
	down();//���U 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();
	left();//���� 
	if (compare_with_now() == 1){
		i++;
	}
	back_to_now();//�^�첾�ʫe������ 
	if(i==0)
	{		
		printf("�C������");	
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
		printf("�п�J����\n");
		if(ch1=getch())//�ϥ�getch�Ө��o��L���O�A�p�G�O�W�U���k���ܡA�|�@���^�Ǩ�ӭȡA�Ĥ@�ӭȬҬ�224�A�n�ھڲĤG�ӭȤ~��P�_�W�U���k 
		{
			if (ch1 == 224)
			{
				ch2 = getch();
				switch(ch2)
				{
				case 72 : 
					printf("�W\n"); 					
					up();
					show();
					break;
				case 80 : 
					printf("�U\n"); 
					down();
					show();
					break;
				case 75 : 
					printf("��\n"); 
					left();
					show();
					break;
				case 77 : 
					printf("�k\n"); 
					right();
					show();
					break;
				default : 
					printf("�L�ī���\n"); 
					break; 
				}
				check_end();	
			}
			else
			{
				printf("�L�ī���\n"); 
			}
    	} 
	}
} 
