#include<stdio.h>
#include<stdlib.h>
#include<iostream.h>
#include<math.h>
#define maxsize 1000
/***************判断输入数据是否有效**************/
int decide(char str[])
{   
	int i=0;
	while(str[i]!='\0')
	{
		if(str[i]<'0'||str[i]>'9')
		{
			return 0;
			break;
		} 
		  i++;
	}
	return i;
}
/******************将字符串转换成数字**************/
int trans(char str[],int a)
{
	int i;
	int sum;
	for(i=0;i<a;i++)
	{   
		sum=sum+(int)((str[i]-'0')*pow(10,a-i-1));
	}
    return sum;
}
/*************冒泡排序法***********/
int *bubble(int cidao[],int m)
{
	  int i,j;
	  int temp;
	    for(i=0;i<m;i++)
		for(j=i+1;j<m;j++)
		{
		   if(cidao[i]>cidao[j])
		   { 
			    temp=cidao[j];
				cidao[i]=cidao[j];
				cidao[j]=temp;
		   }
		}
		cout<<"排序后的磁盘序列:";
		for(i=0;i<m;i++)
		{
		cout<<cidao[i]<<"  ";   //输出排序结果
}
       cout<<endl;
        return cidao;
  }
  /***********当前磁道输入***********/
  int printnow()
  {
	  char str[10];
	  int a,now;
	  cout<<"请输入当前的磁道号:";
A:cin>>str;
  a=decide(str);
  if(a==0)
  {  
	  cout<<"输入数据的类型错误,请重新输入！"<<endl;
	  goto A;
  }
  else
	   now=trans(str,a);
  return now;
  }
  /***********直接由外向内依次给予和各服务请求*************/
   int printout(int cidao[],int now,int m)
   {
	   int i;
	   int sum=0;
	   cout<<"磁盘扫描序列为:";
	   for(i=m-1;i>=0;i--)
	   {
		   cout<<cidao[i]<<" ";
		   now=cidao[i];
	   }
	   return sum;
   }
   /*********直接由内向外依次给予请求服务**************/
    int printin(int cidao[],int now,int m)
	{
		int i;
		 int sum=0;
		 cout<<"磁盘扫描序列为：";
			 for(i=0;i<m;i++)
			 {
				 cout<<cidao[i]<<"  ";
          sum+=abs(cidao[m-1]-now);
		  now=cidao[i];
			 }
			 return sum;
			 }
	/***********先向磁道减小的方向，再向增加的方向**********/

    int prints(int cidao[],int now,int m,int l,int r)
	{
		int j;
		int sum=0;
		while(l>0)
		{
			cout<<cidao[l]<<" ";
			sum+=now-cidao[l];
			now=cidao[l];
			l=l-1;
		}
		now=cidao[0];
		for(j=r;j<m;j++)
		{
			cout<<cidao[j]<<"  ";
			sum+=cidao[j]-now;
			now=cidao[j];
		}
		return sum;
	}
	/***********先向磁道增加的方向，再向磁道减小的方向***********/
	int printl(int cidao[],int now,int m,int l,int r)
	{
		int j;
		int sum=0;
		while(r<m)
		{
			cout<<cidao[r]<<" ";
			sum+=cidao[r]-now;
			now=cidao[r];
			r=r+1;
		}
		now=cidao[m-1];
		for(j=1;j>=0;j--)
		{
			cout<<cidao[j]<<" ";
			sum+=now-cidao[j];
			now=cidao[j];
		}
		return sum;
	}
	/*******先来先服务算法**********/
	void FCFS(int cidao[],int m)
	{
		int now;
		float sum=0;
		int j,i;
		float ave;
		cout<<"请求磁盘序列为：";
		for(i=0;i<m;i++)
		{
			cout<<cidao[i]<<"  ";
		}
		cout<<endl;
		now=printnow();
    cout<<"磁盘扫描序列为:";
      for(i=0;i<m;i++)
	  {  
     cout<<cidao[i]<<" ";
	  }
        for(i=0,j=1;j<m;i++,j++)
		{
      sum+=abs(cidao[j]-cidao[i]);
      ave=(float)(sum)/(float)(m);
		}
		cout<<endl;
		cout<<"平均寻道长度:"<<ave<<endl;
	}
     /****************最短寻道时间优先算法**************/
	void SSTF(int cidao[],int m)
	{
		int k=1;
		int now,l,r;
		int sum;
		float ave;
		cidao=bubble(cidao,m);
		now=printnow();
  if(cidao[m-1]<=now)
 sum=printout(cidao,now,m);//若当前磁道号大于请求序列中最大者
  if(cidao[0]>=now)
 if(now>cidao[0]&&now<cidao[m-1])//做当前磁道号大于请求序列最小者且小于最大者
 {  cout<<"磁盘扫描序列为：";
   while(cidao[k]<now)  //确定当前磁道在意排列的序列中的位置
   {
          k++;
 }
     l=k-1;
     r=k;
         
			  if((now-cidao[l]<=cidao[r]-now)) //先向磁道减少的方向访问
			  {
				  sum=prints(cidao,now,m,l,r);
			  }
             else 
			 {
				 sum=printl(cidao,now,m,l,r);
			 }
		  }
		  ave=(float)(sum)/(float)(m);
		  cout<<endl;
		  cout<<"平均寻道长度:"<<ave<<endl;
 }

 /****************扫描调度算法**************/
  void SCAN(int cidao[],int m)
  {
	  int k=1;
	  int now,l,r,d;
	  int sum;
	  float ave;
	  cidao=bubble(cidao,m);
         now=printnow();//输入当前磁道号
  cout<<"请输入当前移动臂的移动的方向: ";
 cin>>d;
 if(cidao[m-1]<=now) //若当前磁道号大于请求序列中的最大者，则直接由外向内依次给予各请求服务，此情况统最短寻道优先
  sum=printout(cidao,now,m);

if(cidao[0]>=now) //若当前磁道号小于请求序列中的最大者，则直接由外向内依次给予各请求服务，此情况统最短寻道优先
   sum=printin(cidao,now,m);

if(now>cidao[0]&&now<cidao[m-1]) //若当前磁道号大于请求序列中的最小者且小于最大者
{
     while(cidao[k]<now)
	 {
              k++;
	 }
         l=k-1;
          r=k;
       if(d=0)  //先向磁道号减小方向询问
     sum=prints(cidao,now,m,l,r);
      if(d=1)
       sum=printl(cidao,now,m,l,r);
}
     ave=(float)(sum)/(float)(m);
	 cout<<endl;
	 cout<<"平均寻道长度:"<<ave<<endl;
} 
/*****************主函数**************/
	  void main()
			{
				int a;     //菜单项
				int c;
				int cidao[maxsize];
				int i=0;
				int m,n;
				char str[10];
				cout<<"输入寻找的范围:"<<endl;
			
			cin>>m;
			if(m>65536)
			{
				cout<<"输入数据范围超出范围，请重新输入!"<<endl;
				cout<<"输入磁盘调度序列的个数:";
					cin>>n;
				cout<<"随机产生刺到序列为:"<<endl;
              for(i=0;i<n;i++)
			  {
				  cidao[i]=rand()%m;
			  }
			  for(i=0;i<n;i++)
			  {
				  cout<<cidao[i]<<"  ";
			  }
			  cout<<endl;
			  while(1)
				  cout<<endl;
			  cout<<"**************************************"<<endl;
			  cout<<"********          系统菜单    *********"<<endl;
			  cout<<"**************************************"<<endl;
              cout<<"***                                ***"<<endl;
			  cout<<"**           1.先来先服务         **"<<endl;
			  cout<<"**           2.最短寻道优先       **"<<endl;
			  cout<<"**           3.扫描调度           **"<<endl;
			  cout<<"**           4.退出               **"<<endl;
B:cout<<"请选择算法:";
C:cin>>str;
                a=decide(str);
					if(a==0)
					{
						cout<<"输入的类型错误，请重新输入！"<<endl;
						goto C;
					}
					else 
						c=trans(str,a);
					if(c>=5)
					{
						cout<<"数据输入错误，请重试"<<endl;
						goto B;
					}
					switch(c)
          
					{
					case 1:
						FCFS(cidao,n);
						break;
					case 2:
						SSTF(cidao,n);
						break;
					case 3:
						SCAN(cidao,n);
						break;
					case 4:
						exit(0);
					}
			}
	  }