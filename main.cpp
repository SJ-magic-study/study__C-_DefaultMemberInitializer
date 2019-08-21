/************************************************************
[参考URL]
	C++ メンバ変数の初期化｜コンストラクタでの初期化とメンバ宣言時の初期化
		https://marycore.jp/prog/cpp/initialize-data-member/#デフォルトメンバ初期化子を用いたメンバ宣言
		

[注意]
	下記codeは、
		ITEM b = ITEM(0);
		ITEM c[] = { ITEM(0), ITEM(1), };
	いずれも、
		compile時:
			デフォルト コンストラクタ(引数付き)を使って、temporary変数を作成し、コピーコンストラクタで配列の要素を初期化
		動作時:
			デフォルト コンストラクタ(引数付き)のみがcallされる
	
	compileの最適化に寄る動作と思われる。
	実動作時に通らないとは言え、copy constructorをprivateにすると、compileが通らないので注意。

	
	
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
	ITEM()
	: a(0)
	{
		printf("ITEM:default constructor:a=%d\n", a);
		fflush(stdout);
	}
	
	ITEM(int _a)
	: a(_a)
	{
		printf("ITEM:Param constructor:a=%d\n", a);
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
	ITEM item = ITEM(99);							// Param constructor
													// Param constructorでtemporary変数を作成し、copy constructorで初期化 かと思ったが違った。
													// compilerの最適化だろうか?
													// 
													// But : 動作時はcopy constructorを通ってないのに、これをprivateにすると、compile Error.

	ITEM items[3] = { ITEM(0), ITEM(1), ITEM(2), };	// Param constructor
													// こちらも、copy constructorをprivateにすると、compile Error.
	
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
	/********************
	********************/
	TEMP temp;
	printf("%d, %d, %d, %d, %d, %d\n", temp.a, temp.b, temp.c, temp.d[0], temp.d[1], temp.d[2]); // 1, 2, 9 : constructor側の初期化が優先される.
	
	/********************
	********************/
	// ITEM a;			// default construcrot
	
	// ITEM b = a;	// copy constructor
	
	// ITEM b;	// default constructor
	// b = a;	// operator =
	// b.print();
	
	// ITEM b;	// default constructor
	// b = ITEM(0);	// Param constructorでtemporary変数を作成し、operator=
					// copy constructorがprivateでもok.
	
	// ITEM b(a);	// copy constructor
	

	/**********
	!! 注意 !!
	**********/
	// ITEM b = ITEM(0);	// Param constructor
						// Param constructorでtemporary変数を作成し、copy constructorでbを初期化 かと思ったが違った。
						// compilerの最適化だろうか?
						// 
						// But : 動作時はcopy constructorを通ってないのに、これをprivateにすると、compile Error.
	
	// ITEM b(ITEM(1));	// Param constructor
						// copy constructorをprivateにすると、compile Error
						
	// ITEM c[] = { ITEM(0), ITEM(1), };	// Param constructor.
										// こちらも、copy constructorをprivateにすると、comipile Error
	
	/********************
	********************/
	USER user;
	user.print();
	
	return 0;
}
