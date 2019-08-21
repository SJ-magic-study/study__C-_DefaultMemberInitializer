/************************************************************
[参考URL]
	C++ メンバ変数の初期化｜コンストラクタでの初期化とメンバ宣言時の初期化
		https://marycore.jp/prog/cpp/initialize-data-member/#デフォルトメンバ初期化子を用いたメンバ宣言
		

[注意]
下記codeでは、
	ITEM items[3] = {
		ITEM(0),
		ITEM(1),
		ITEM(2),
	};
	
	compile時:
		コンストラクタを使って、temporary変数を作成し、コピーコンストラクタで配列の要素を初期化
	動作時:
		コピーコンストラクタを通らず、直接要素の初期化が行われている。
		配列が定義された時に「引数なしコンストラクタ」が呼ばれることもない。
		
と動いている様子。
例えばコピーコンストラクタをprivateにしてコピー禁止classにすると、compileが通らなかった。
動作時は通らないのに、何故こうなるのかは不明のまま。


以前にも同じ内容を検討していた・・・
	https://github.com/SJ-magic-study/study__init_Array_by_CopyConstructor
		

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
	
	ITEM(const ITEM& src)
	{
		a = src.a;
		
		printf("ITEM:copy constructor:a=%d\n", a);
		fflush(stdout);
	}
	
	void operator =(const ITEM& src)
	{
		a = src.a;
		
		printf("ITEM:equal:a=%d\n", a);
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
	ITEM items[3] = {
		ITEM(0),
		ITEM(1),
		ITEM(2),
	};
	
public:
	void print(){
		item.print();
		
		for(int i = 0; i < 5; i++){
			items[i].print();
		}
	}
	
	ITEM& get_item(int id){
		if(3 <= id) id = 0;
		return items[id];
	}
};

int main()
{
	TEMP temp;
	printf("%d, %d, %d, %d, %d, %d\n", temp.a, temp.b, temp.c, temp.d[0], temp.d[1], temp.d[2]); // 1, 2, 9 : constructor側の初期化が優先される.
	
	USER user;
	user.print();
	
	ITEM item(user.get_item(2));
	
	return 0;
}
