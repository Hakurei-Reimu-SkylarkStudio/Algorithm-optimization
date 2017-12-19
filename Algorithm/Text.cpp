//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//using namespace std;
//
//int main()
//{
//    ifstream infile;
//    infile.open("1.txt");
//    if(!infile) cout<<"error"<<endl;
//
//    string str;
//    int t1;
///*  while(getline(infile,str))   //按行读取,遇到换行符结束
//    {   
//        infile.getline(str,10);
//        cout<<str<<endl;
//    }
//*/
// /*//存入vector
//    cout<<"存入vector"<<endl;
//    vector<int> ve;
//    while(infile>>t1)             //按空格读取，遇到空白符结束
//    {
//        ve.push_back(t1);         
//    }
//
//    for(int i=0;i<ve.size();i++) 
//        cout<<ve[i]<<" ";
//    cout<<endl;
//*/
//
////存入数组
//    cout<<"存入数组"<<endl;
//    int a[3][4];
//    int*p=&a[0][0];
//    while(infile>>t1)             //遇到空白符结束
//    {
//        *p=t1;
//         p++;
//    }
//    infile.close();
//    for(int i=0;i<3;i++)
//    {   for(int j=0;j<4;j++)
//           cout<<a[i][j]<<"\t";
//         cout<<endl;
//    }
//    return 0;
//}