#ifndef MAPDATA_H
#define MAPDATA_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

struct Postion{		//用來儲存座標
	int x = 0;
	int y = 0;
};

struct doorDataS {		//儲存門
	Postion pos;
	bool exist = false;		//判斷門是否開啟
};

struct enemyDataS {		//儲存怪物資訊
	string name;	//怪物ID
	char icon;		//怪物的代號
	Postion pos;
	int kindOfEnemy;	//普通或精英怪物   1:普通  2: 菁英
	bool exist = false;   //判斷怪物是否死亡
};

struct characterDataS {		//儲存腳色資訊
	string name;	//腳色ID
	char icon;		//腳色的代號
	Postion pos;
	bool exist = false;	   //判斷腳色是否死亡
};

class MapData {
private:
	int mapRow;			//map的高
	int mapColumn;		//map的寬
	struct validPosS {
		bool passSameRole =false;		//if true , 表示這位置有role ; if false 這位置是空地
		bool validPos = false;				// if true, 這格可以停留 ; if false 這格可能是牆壁 或是 最後一步不可在role上
	};
public:
	MapData(string s, int characterNum);
	int defaultX, defaultY;	//預設位置
	int round_int = 0; //回和數
	characterDataS characterData[4];    // 腳色座標資訊(最多4人)  新增的
	enemyDataS enemyData[50];
	int doorNum = 0;    //不用儲存門座標 用門數量判斷
	int monsterNum = 0;		//怪物數量(預設0)
	int characterNum;		//腳色數量
	int validPos[100][100]; //可看見地圖上存1 2 3，其他存0
	/*儲存初始地圖 (只有 0 牆壁，無法通過且沒有視野
	1普通地板，可以通過、
	2 障礙物，無法通過但有視野
	3門,在每輪結束時, 當角色停在門上且場上沒有怪物, 將會開啟下一間房間, 開啟後變為普通地板, 在未開啟前對怪物來說是障礙物)*/
	vector<string> map;
	vector<string> tempMap;    //用來暫存地圖
	void findValidPos(int x, int y);	//尋找可看見區域
	void tempPrintMap();	//選擇完腳色起始位置前的印地圖方式
	void printMap();	//印地圖
	void decideInitialPos();	//選擇腳色起始位置
	void roleMove(string type, int index, string moveCommand);  //role 移動指令
	bool checkPosValid(Postion nextPost,string type, validPosS& validPos);	// check 欲移動位置是否可以   retrun 1 可以 ; 0 不行
	int characterMove(int index, int numOfMove);  //character 移動指令
	void printRound(); // print round x : 
	bool sight(Postion posC, Postion posM);			//判斷有沒有視野 true: 有，false: 沒有
	//bool allDoorsOpen();		//檢查全部門是否以開啟
};

#endif // !MAPDATA_H
