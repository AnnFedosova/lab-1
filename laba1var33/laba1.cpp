#include <string.h>
#include <stdio.h>
#include <iostream>

typedef struct Item {
	int pos;		//�������
	int	info;		//����� != 0
	Item* next;
}item_t;

typedef struct Link {
	int pos;		//�������
	item_t* pItem;
	Link* next;
}link_t;

int getNum(int*, char*);
int add_string (item_t**, int);		
int input(link_t**,int,int);	//�������� ������� �������
int getB(int, int,int*, link_t* );	//��������� ������� B		B[i] = S1 - S2
int getS1(link_t*);	// s1 ����� ������ ����� � ������
int getS2(link_t*,int);	// s2 ��������� ����� � ������
void output(int*);		//����� ������� �� �����
void outputB(int*, int);

//������ � ������
int getB(int m,int n, int* B, link_t* matrix)
{
	link_t* curLink = matrix;
	for(int i = 0; i < m; i++)
	{
		if ((curLink != NULL) && ( i == curLink->pos))
		{
			int S1 = getS1(curLink);
			int S2 = getS2(curLink,n);
			B[i] = S1 - S2;
			curLink = curLink->next;
		}
		else
			B[i] = 0;
	}
	return 0;
}

void outputB(int* B,int m)
{
	std::cout<<"array B:"<<std::endl;
	for(int i = 0; i < m; i++)
		std::cout<<B[i]<<" "<<std::endl;
}

//����� ���� ������ �������� ��������� ������
int getS1(link_t* Link)
{
	item_t* curItem = Link->pItem;
	int S1 = 0;
	while(curItem != NULL)
	{
		if ((curItem->info % 2) == 0 )
			S1 += curItem->info;
		curItem = curItem->next;
	}
	return S1;
}

//������� �������� ��������� ������� � ������ (�������, 0 ��� �� 0)
int getS2(link_t* Link, int n)
{
	int S2 = 0;
	item_t* lastItem;
	item_t* curItem = Link->pItem;
	
	while (curItem != NULL)
	{
		lastItem = curItem;
		curItem = curItem->next;
	}
	if ((lastItem != 0) && (lastItem->pos == (n - 1)))
		S2 = lastItem->info;

	return S2;
}

//������� �������� �����
int getNum(int* a, char* info)
{
	int data;
	std::cout<<info;
	std::cin>>data;
	*a = data;
	if (!std::cin.good())
	{
		std::cout<<"error"<<std::endl;
		std::cin.clear();
		return -1;
	}
	return 0;
}

int add_string (item_t** Item, int n)
{
	int res = 0;

   int data;
   item_t* curItem = NULL;
   *Item = curItem;
   for(int i = 0; i < n; i++)
   {
     if ((res = getNum(&data, "data:\n")) < 0)
      break;
     if(data != 0)
     {
	    // �������� ������ ��� newItem
		item_t* newItem;
		try{ newItem = new item_t; }
		catch(std::bad_alloc) {	std::cout<<"error bad_alloc"<<std::endl; }
         newItem->pos = i;
         newItem->info = data;
         newItem->next = NULL;
         if (curItem != NULL)
            curItem->next = newItem;
         else
            *Item = newItem; //  ���������� ������ ������
         curItem = newItem;
     }
   }
   return res;
}

/*
//�������� �������� ���������
int creatItem(item_t& Item )
{
	Item.next = NULL;
	int res = getNum(Item.pos);
	if (res != 0)
		return -1;
	 getNum(Item.info);

	if (res != 0)
		return -1;
	return 0;
}
*/

//�������� ������ �������
int input(link_t** matrix, int m, int n)
{
	int res = 0;
	*matrix = NULL;
	link_t* curLink = NULL;
	for(int i = 0; i < m; i++)
	{
		item_t* CurItem;
		if ((res = add_string(&CurItem, n)) < 0) // ��������� ������
			break;
		if (CurItem != NULL)	// ���� ������ �� ������ (���� ������ �������� �� 0) - ��������� ������ � �������
		{
			link_t* newLink;
			try{ newLink = new link_t; }
			catch(std::bad_alloc) { 
				std::cout<<"error bad_alloc"<<std::endl; }
			if (curLink != NULL)
				curLink->next = newLink;
			else
				*matrix = newLink; // ��������� ������ �������
			newLink->pItem = CurItem;
			newLink->pos = i;
			newLink->next = NULL;
			curLink = newLink;
		}
	}
	return res;
}

void print_string(item_t* Item, int n)
{
	item_t* curItem = Item;
	for(int i = 0; i < n; i++)
	{
		int data = 0; 
		if ((curItem != NULL) &&			// ������� ����
			  (curItem->pos == i))			// � ������� �� ������
		{
			data = curItem->info;
			curItem = curItem->next;
		}
		std::cout << data << " ";
	}
	std::cout<<std::endl;
}

//������� ������� �������
void output(link_t* matrix, int m, int n)
{

	std::cout<<"result marix:"<<std::endl;
	if (matrix == NULL)
		std::cout<<"empty marix:"<<std::endl;
	link_t* curLink = matrix;
	for(int i = 0; i < m; i++)
	{
		item_t* pString = NULL;
		if ((curLink != NULL) &&		// ������ ����
		  (curLink->pos == i))			// � ��� ������ �� ������
		{
			pString = curLink->pItem;
			curLink = curLink->next;
		}
		print_string (pString, n);
	}
}


int main()
{
	
	int m = 0, n = 0;		// m - ���-�� �����, n - ���-�� !=0 ���� � ������

	if ((getNum(&m, "amount of rows:\n")!=0) || (m <= 0) )
		return -1;
	if ((getNum(&n, "amount of columns:\n")!=0) || (n <= 0) )
		return -1;

	link_t* matrix = NULL;
	input(&matrix,m,n);
	output(matrix, m, n);

	int *B = new int[m];
	getB(m, n, B, matrix);
	outputB(B, m);
	system ("pause");
	return 0;
}
