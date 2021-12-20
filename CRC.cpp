#include <iostream>
#include <string>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <cmath>
using namespace std;
int n1,n2;

string XOR(string data,string div,int i)
{
    for(int k=i;k<i+div.length();k++)
    {
        if(data[k]==div[k-i])
        data[k]='0';
        else
        data[k]='1';
    }
    return data;
}

string encode(string data,string div)
{
    n1= data.length(),n2=div.length();
    for(int i=1;i<n2;i++)
    {
        data+='0';
    }
    string rem=data;
    for(int i=0;i<n1;i++)
    {
        if(rem[i]=='0')
        continue;
        else
        rem= XOR(rem,div,i);
    }
    cout<<endl;
    string code=XOR(data,rem.substr(n1,n2-1),n1);
 return code;
 }

int decode(string code,string div)
{
    n1 = code.length();
    n2 = div.length();
    for(int i=0;i<n1-n2+1;i++)
    {
        if(code[i]=='0')
        continue;
        else
        code= XOR(code,div,i) ;
    }
    int zeroes=0,err=0;
    for(int i=n1-n2;i<n1;i++)
    {
        if(code[i]=='0')
        zeroes++;
    }
    if(zeroes==n2)
    {
        cout << endl <<"--------No Error detected by CRC--------"<<endl;
    }
    else
    {
        cout << endl <<"--------Error detected by CRC---------"<<endl;
        err=1;
   }
return err;
}

string error(string data,float prob)
{
    srand(time(0));
    for(int i=0;i<data.length();i++)
    {
        float x = ((float)rand()/(RAND_MAX));
        if(x<prob)
        {
            if(data[i]=='0')
            data[i]='1';
            else
            data[i]='0';
        }
    }
return data;
}

int mainplot()
{
   int x = 30, y =30;
   setlinestyle(0,1,1);
   settextstyle(8, 1, 1);
   outtextxy(x-5,y+40,"Amplitude");
   settextstyle(8, 0, 1);
   outtextxy(x-5,y,"+V");
   outtextxy(x-5,y+160,"0");
   line(x,y,x,y+200);
   setlinestyle(1,1,1);
   line(x,y+150, x+1200, y+150);
   settextstyle(8, 0, 5);
   outtextxy(x+700,y+240,"Dataword Sent");
   y+=300;
   settextstyle(8, 1, 1);
   outtextxy(x-5,y+40,"Amplitude");
   setlinestyle(0,1,1);
   line(x,y,x,y+200);
   settextstyle(8, 0, 1);
   outtextxy(x-5,y,"+V");
   outtextxy(x-5,y+160,"0");
   setlinestyle(1,1,1);
   line(x,y+150, x+1200, y+150);
   settextstyle(8, 0, 5);
   outtextxy(x+800,y+240,"Dataword Extracted");
}

int main()
{
    start:
    string Dataword,code;
    cout << "Enter the Dataword: ";
    cin >> Dataword;
    n1 = Dataword.length();

    string div="100000111";
    cout << "Divisor for CRC-8 is: "<< div << endl;
    n2 = div.length();

    int hops=0,prob1=0,prob2=0;
    cout << "Enter the number of hops in binary symmetric channel(1 or 2):  ";
    cin >> hops;

    Prob1:
    cout << "Enter the crossover probability(p1): ";
    cin >> prob1;
    if(prob1 > 1)
    {
        cout << "Error! Enter a number between 1 and 0" << endl;
        goto Prob1;
    }
     if(hops==2)
     {
        Prob2:
    cout << "Enter the crossover probability(p2): ";
    cin >> prob2;
    if(prob2 > 1)
    {
        cout << "Error! Enter a number between 1 and 0" << endl;
        goto Prob2;
    }
    }

    float token=16.0,blocks=n1/token;
    int a = n1%(int)token;
    if(n1%(int)token == 0)
    {
        blocks-=0.5;
        a=token;
    }
    int n3 = (int)ceil(blocks);
    string arr[n3];

    for(int i = 1 ; i <= floor(blocks) ; i++)
    {
        arr[i] = Dataword.substr(a + token*(i-1),token);
    }
    arr[0] = Dataword.substr(0,a);

    int t = arr[0].length();

    for(int i = 0 ; i < token-t ; i++)
    {
        arr[0] = '0' + arr[0];
    }

    string codearr[n3];

    for(int i = 0 ; i <= floor(blocks) ; i++)
    {
        codearr[i] = encode(arr[i],div);
        cout << i+1 << ". " << token << " Bit Tokenized Dataword is: "<<arr[i]<<endl;
        cout << "   CodeWord " << i+1 << " at sender side is: "<< codearr[i]<< endl;
    }

    string errarr[(int)ceil(blocks)];
    for(int i=0;i<=floor(blocks);i++)
    {
        errarr[i]=codearr[i];
    }
    for(int i=0;i<hops;i++)
    {
        if(i==0)
        {
           for(int i=0;i<=floor(blocks);i++)
            {
                errarr[i]=error(errarr[i],prob1);
            }
        }
        else{
        for(int i=0;i<=floor(blocks);i++)
        {
            errarr[i]=error(errarr[i],prob2);
        }
        }
    }
    int errno;
    cout << endl;
    for(int i=0;i<=floor(blocks);i++)
    {
        cout<< i+1 <<". Code Word sent is " <<codearr[i]<<endl;
        cout <<"   Code Word recieved is "<<errarr[i]<<endl;
        errno+=decode(errarr[i],div);
        cout<<endl;
    }

    if(errno>0)
    {
        cout<<"--------Discard--------"<<endl;
    }
    else
    {
        cout <<"--------No Error in the recieved Dataword.--------" << endl << endl << "Sent Dataword is: " << Dataword << endl;
        srand(time(0));
        initwindow(1350,600);
        setbkcolor(WHITE);
        cleardevice();
        setcolor(BLACK);
        mainplot();

    int x = 30,y = 180;
    setlinestyle(0,1,1);
    settextstyle(8, 0, 1);
    for(int i=0;i<Dataword.length();i++)
    {
        if(Dataword[i]=='1')
        {
              line(x,y,x,y-90);
              line(x,y-90,x+20,y-90);
              x+=20;
              line(x,y-90,x,y);
              outtextxy(x-3,y-100,"1");
        }
        else
        {
            line(x,y,x+20,y);
            x+=20;
            outtextxy(x-3,y-100,"0");
        }
    }
    x=30,y = 480;
    cout << "Extracted Dataword from Code Word is: ";
    for(int i=0;i<=floor(blocks);i++)
    {
        string tempstr = errarr[i].substr(0,token);
        cout << tempstr;
        for(int j=0;j<tempstr.length();j++)
        {
            if(tempstr[j]=='1')
            {
              line(x,y,x,y-90);
              line(x,y-90,x+20,y-90);
              x+=20;
              line(x,y-90,x,y);
              outtextxy(x-3,y-100,"1");
            }
            else
            {
                line(x,y,x+20,y);
                x+=20;
                outtextxy(x-3,y-100,"0");
            }
        }
    }
    cout << endl << endl;
}
    cout << "Do you want to feed Another dataword?(y/n)";
    char ch;
    cin >> ch;
    if(ch == 'Y' || ch == 'y')
    goto start;
    else
    return 0;
}
