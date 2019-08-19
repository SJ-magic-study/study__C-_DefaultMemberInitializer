/************************************************************
参考URL
	C++ メンバ変数の初期化｜コンストラクタでの初期化とメンバ宣言時の初期化
		https://marycore.jp/prog/cpp/initialize-data-member/#デフォルトメンバ初期化子を用いたメンバ宣言
************************************************************/
#include <stdio.h>

class TEMP{
private:
public:
	int a = 1;
	int b{2};
	int c = {3};
	TEMP() : c(9) {} // 
	
	int d[3] = {0, 1, 2};
};

class ITEM{
private:
	int a;
public:
	ITEM(int _a)
	: a(_a)
	{
		printf("ITEM:constructor:a=%d\n", a);
		fflush(stdout);
	}
	
	~ITEM(){
		printf("ITEM:desttructor:%d\n", a);
		fflush(stdout);
	}
	
	void print() { printf("a = %d\n", a); fflush(stdout); }
};

class USER{
private:
	ITEM item = ITEM(99);
	ITEM items[5] = {
		ITEM(0),
		ITEM(1),
		ITEM(2),
		ITEM(3),
		ITEM(4),
	};
	
public:
	void print(){
		item.print();
		
		for(int i = 0; i < 5; i++){
			items[i].print();
		}
	}
};

int main()
{
	TEMP temp;
	printf("%d, %d, %d, %d, %d, %d\n", temp.a, temp.b, temp.c, temp.d[0], temp.d[1], temp.d[2]); // 1, 2, 9 : constructor側の初期化が優先される.
	
	USER user;
	user.print();
	
	return 0;
}

