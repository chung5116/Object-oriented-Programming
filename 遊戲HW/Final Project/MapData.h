#ifndef MAPDATA_H
#define MAPDATA_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

struct Postion{		//�Ψ��x�s�y��
	int x = 0;
	int y = 0;
};

struct doorDataS {		//�x�s��
	Postion pos;
	bool exist = false;		//�P�_���O�_�}��
};

struct enemyDataS {		//�x�s�Ǫ���T
	string name;	//�Ǫ�ID
	char icon;		//�Ǫ����N��
	Postion pos;
	int kindOfEnemy;	//���q�κ�^�Ǫ�   1:���q  2: �׭^
	bool exist = false;   //�P�_�Ǫ��O�_���`
};

struct characterDataS {		//�x�s�}���T
	string name;	//�}��ID
	char icon;		//�}�⪺�N��
	Postion pos;
	bool exist = false;	   //�P�_�}��O�_���`
};

class MapData {
private:
	int mapRow;			//map����
	int mapColumn;		//map���e
	struct validPosS {
		bool passSameRole =false;		//if true , ��ܳo��m��role ; if false �o��m�O�Ŧa
		bool validPos = false;				// if true, �o��i�H���d ; if false �o��i��O��� �άO �̫�@�B���i�brole�W
	};
public:
	MapData(string s, int characterNum);
	int defaultX, defaultY;	//�w�]��m
	int round_int = 0; //�^�M��
	characterDataS characterData[4];    // �}��y�и�T(�̦h4�H)  �s�W��
	enemyDataS enemyData[50];
	int doorNum = 0;    //�����x�s���y�� �Ϊ��ƶq�P�_
	int monsterNum = 0;		//�Ǫ��ƶq(�w�]0)
	int characterNum;		//�}��ƶq
	int validPos[100][100]; //�i�ݨ��a�ϤW�s1 2 3�A��L�s0
	/*�x�s��l�a�� (�u�� 0 ����A�L�k�q�L�B�S������
	1���q�a�O�A�i�H�q�L�B
	2 ��ê���A�L�k�q�L��������
	3��,�b�C��������, ���ⰱ�b���W�B���W�S���Ǫ�, �N�|�}�ҤU�@���ж�, �}�ҫ��ܬ����q�a�O, �b���}�ҫe��Ǫ��ӻ��O��ê��)*/
	vector<string> map;
	vector<string> tempMap;    //�ΨӼȦs�a��
	void findValidPos(int x, int y);	//�M��i�ݨ��ϰ�
	void tempPrintMap();	//��ܧ��}��_�l��m�e���L�a�Ϥ覡
	void printMap();	//�L�a��
	void decideInitialPos();	//��ܸ}��_�l��m
	void roleMove(string type, int index, string moveCommand);  //role ���ʫ��O
	bool checkPosValid(Postion nextPost,string type, validPosS& validPos);	// check �����ʦ�m�O�_�i�H   retrun 1 �i�H ; 0 ����
	int characterMove(int index, int numOfMove);  //character ���ʫ��O
	void printRound(); // print round x : 
	bool sight(Postion posC, Postion posM);			//�P�_���S������ true: ���Afalse: �S��
	//bool allDoorsOpen();		//�ˬd�������O�_�H�}��
};

#endif // !MAPDATA_H
