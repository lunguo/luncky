#include<iostream>    
#include<cstring>    
#include<stack>    
#include<algorithm> 
#include<cmath>    
using namespace std;    
    
stack<char> s1,s2;    
stack<int> s3;    
char ch[150]={0};//用来存表达式    
int num[11];//用来暂时存数字    
          
int priority(char ch)//用于比较字符优先级    
{    
    if(ch==')'||ch=='(') return 1;    
    if(ch=='+'||ch=='-') return 2;    
    if(ch=='*'||ch=='/') return 3;         
}    
         
int Scal(int x,int y,char ope)//两个数的运算    
{    
    if(ope=='+') return x+y;    
    if(ope=='-') return x-y;    
    if(ope=='*') return x*y;    
    if(ope=='/'&&y!=0) return x/y;    
}    
    
void Transform(int n)//将中缀表达式转化为后缀表达式    
{    
    int k=0;    
    for(int i=0;i<n;i++)       
        if(ch[i]>='0'&&ch[i]<='9')//当是数字的情况       
            if(i+1<n&&(ch[i+1]<'0'||ch[i+1]>'9')||i==n-1)//当是最后一个数字，或下一个元素是运算符    
            {    
                s2.push(ch[i]);    
                s2.push('#');    
            }    
            else    
                s2.push(ch[i]);     
        else      
            if(s1.empty()||ch[i]=='('||priority(ch[i])>priority(s1.top()))//当是运算符，有3种情况直接入栈    
                s1.push(ch[i]);                 
            else if(ch[i]==')')//当是右括号的情况    
            {    
                while(s1.top()!='(')    
                {    
                    s2.push(s1.top());      
                    s1.pop();    
                }    
                s1.pop();    
            }    
            else//当运算符优先级小于或等于S1栈顶运算符的优先级  
            {    
                while(!s1.empty()&&priority(ch[i])<=priority(s1.top())&&s1.top()!='(')//这里还要注意两个界限    
                {    
                    s2.push(s1.top());    
                    s1.pop();               
                }    
                s1.push(ch[i]);     
            }       
    while(!s1.empty())//当表达式结束    
    {    
        s2.push(s1.top());    
        s1.pop();           
    }    
    while(!s2.empty()) //将栈内元素放回S2中    
    {    
        ch[k++]=s2.top();    
        s2.pop();       
    }    
    reverse(ch,ch+k);//将ch[]反向    
    ch[k]=0;    
}    
    
int Cal(int n)//后缀表达式计算    
{    
    int x,y,tmp=0,k=0;    
    for(int i=0;i<n;i++)       
        if(ch[i]=='#')//是#直接跳过    
            continue;    
        else if(ch[i]=='+'||ch[i]=='-'||ch[i]=='*'||ch[i]=='/')//是运算符弹出栈顶两元素计算后放回栈    
        {    
            x=s3.top();    
            s3.pop();    
            y=s3.top();    
            s3.pop();    
            x=Scal(y,x,ch[i]);    
            s3.push(x);    
        }    
        else//是数字字符       
            if(ch[i+1]=='#')//下一个元素是#    
            {    
                num[k++]=ch[i]-'0';    
                for(int i=0;i<k;i++)    
                    tmp+=(num[i]*(int)pow(10,k-i-1));    
                s3.push(tmp);    
                tmp=0;    
                k=0;                    
            }    
            else//下一个元素不是#       
                num[k++]=ch[i]-'0';                  
    return s3.top();    
}    
    
int main()    
{    
    printf("<<"); 
    scanf("%s",ch);
    while(ch[0]!='0')
    {
        Transform(strlen(ch));    
        cout<<Cal(strlen(ch))<<endl;  
        printf("<<"); 
        scanf("%s",ch);
    }
    return 0;    
}    
