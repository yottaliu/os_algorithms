#include<stdio.h>
#include<stdlib.h>
#include<iostream.h>
#include<math.h>
#define maxsize 1000
/***************�ж����������Ƿ���Ч**************/
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
/******************���ַ���ת��������**************/
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
/*************ð������***********/
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
		cout<<"�����Ĵ�������:";
		for(i=0;i<m;i++)
		{
		cout<<cidao[i]<<"  ";   //���������
}
       cout<<endl;
        return cidao;
  }
  /***********��ǰ�ŵ�����***********/
  int printnow()
  {
	  char str[10];
	  int a,now;
	  cout<<"�����뵱ǰ�Ĵŵ���:";
A:cin>>str;
  a=decide(str);
  if(a==0)
  {  
	  cout<<"�������ݵ����ʹ���,���������룡"<<endl;
	  goto A;
  }
  else
	   now=trans(str,a);
  return now;
  }
  /***********ֱ�������������θ���͸���������*************/
   int printout(int cidao[],int now,int m)
   {
	   int i;
	   int sum=0;
	   cout<<"����ɨ������Ϊ:";
	   for(i=m-1;i>=0;i--)
	   {
		   cout<<cidao[i]<<" ";
		   now=cidao[i];
	   }
	   return sum;
   }
   /*********ֱ�������������θ����������**************/
    int printin(int cidao[],int now,int m)
	{
		int i;
		 int sum=0;
		 cout<<"����ɨ������Ϊ��";
			 for(i=0;i<m;i++)
			 {
				 cout<<cidao[i]<<"  ";
          sum+=abs(cidao[m-1]-now);
		  now=cidao[i];
			 }
			 return sum;
			 }
	/***********����ŵ���С�ķ����������ӵķ���**********/

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
	/***********����ŵ����ӵķ�������ŵ���С�ķ���***********/
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
	/*******�����ȷ����㷨**********/
	void FCFS(int cidao[],int m)
	{
		int now;
		float sum=0;
		int j,i;
		float ave;
		cout<<"�����������Ϊ��";
		for(i=0;i<m;i++)
		{
			cout<<cidao[i]<<"  ";
		}
		cout<<endl;
		now=printnow();
    cout<<"����ɨ������Ϊ:";
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
		cout<<"ƽ��Ѱ������:"<<ave<<endl;
	}
     /****************���Ѱ��ʱ�������㷨**************/
	void SSTF(int cidao[],int m)
	{
		int k=1;
		int now,l,r;
		int sum;
		float ave;
		cidao=bubble(cidao,m);
		now=printnow();
  if(cidao[m-1]<=now)
 sum=printout(cidao,now,m);//����ǰ�ŵ��Ŵ������������������
  if(cidao[0]>=now)
 if(now>cidao[0]&&now<cidao[m-1])//����ǰ�ŵ��Ŵ�������������С����С�������
 {  cout<<"����ɨ������Ϊ��";
   while(cidao[k]<now)  //ȷ����ǰ�ŵ��������е������е�λ��
   {
          k++;
 }
     l=k-1;
     r=k;
         
			  if((now-cidao[l]<=cidao[r]-now)) //����ŵ����ٵķ������
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
		  cout<<"ƽ��Ѱ������:"<<ave<<endl;
 }

 /****************ɨ������㷨**************/
  void SCAN(int cidao[],int m)
  {
	  int k=1;
	  int now,l,r,d;
	  int sum;
	  float ave;
	  cidao=bubble(cidao,m);
         now=printnow();//���뵱ǰ�ŵ���
  cout<<"�����뵱ǰ�ƶ��۵��ƶ��ķ���: ";
 cin>>d;
 if(cidao[m-1]<=now) //����ǰ�ŵ��Ŵ������������е�����ߣ���ֱ�������������θ����������񣬴����ͳ���Ѱ������
  sum=printout(cidao,now,m);

if(cidao[0]>=now) //����ǰ�ŵ���С�����������е�����ߣ���ֱ�������������θ����������񣬴����ͳ���Ѱ������
   sum=printin(cidao,now,m);

if(now>cidao[0]&&now<cidao[m-1]) //����ǰ�ŵ��Ŵ������������е���С����С�������
{
     while(cidao[k]<now)
	 {
              k++;
	 }
         l=k-1;
          r=k;
       if(d=0)  //����ŵ��ż�С����ѯ��
     sum=prints(cidao,now,m,l,r);
      if(d=1)
       sum=printl(cidao,now,m,l,r);
}
     ave=(float)(sum)/(float)(m);
	 cout<<endl;
	 cout<<"ƽ��Ѱ������:"<<ave<<endl;
} 
/*****************������**************/
	  void main()
			{
				int a;     //�˵���
				int c;
				int cidao[maxsize];
				int i=0;
				int m,n;
				char str[10];
				cout<<"����Ѱ�ҵķ�Χ:"<<endl;
			
			cin>>m;
			if(m>65536)
			{
				cout<<"�������ݷ�Χ������Χ������������!"<<endl;
				cout<<"������̵������еĸ���:";
					cin>>n;
				cout<<"��������̵�����Ϊ:"<<endl;
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
			  cout<<"********          ϵͳ�˵�    *********"<<endl;
			  cout<<"**************************************"<<endl;
              cout<<"***                                ***"<<endl;
			  cout<<"**           1.�����ȷ���         **"<<endl;
			  cout<<"**           2.���Ѱ������       **"<<endl;
			  cout<<"**           3.ɨ�����           **"<<endl;
			  cout<<"**           4.�˳�               **"<<endl;
B:cout<<"��ѡ���㷨:";
C:cin>>str;
                a=decide(str);
					if(a==0)
					{
						cout<<"��������ʹ������������룡"<<endl;
						goto C;
					}
					else 
						c=trans(str,a);
					if(c>=5)
					{
						cout<<"�����������������"<<endl;
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