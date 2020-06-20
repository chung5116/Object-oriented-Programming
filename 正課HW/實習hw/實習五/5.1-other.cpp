//#include <iostream>
//#include <iomanip>
//#include <math.h>
//using namespace std;
//int main()
//{ 
//	double x;
//	int m,n;		
//	char c;
//	while (!cin.eof())
//	{
//		cin.clear(); 
//		cin >> x;
//		cin >> m;
//		cin >> n;
//		cin >> c;		
//		int count = 1;
//		double unsignx=abs(x);
//		while(unsignx >=(double)pow(10.0,count))
//        	++count;
//    	int count2=  x >= 0 ?  count:(count+1);
//    	if(n>0){
//    		int fill=m-count2-n-1;
//    		if(fill>0)
//	    		for(int i=0;i<fill;i++)
//					cout << c;
//			cout <<fixed<< setprecision(n) << x-0.0000000009<<  endl;//-0.0000000009防止自動進位 
//			cout.unsetf( ios::fixed );//關掉fixed功能
//		}else{
//			//n=0，不用小數點 
//			int fill=m-count2;
//			if(fill>0)
//	    		for(int i=0;i<fill;i++)
//					cout << c;
//			int integer= (int) (x);
//			if(x >= 0)
//				cout << setprecision(count2) << integer<<  endl;
//			else
//				cout << setprecision(count2-1) <<integer<<  endl;
//		}
//	}
//	return 0;
//}
