#include<iostream>
#include<string>
#include<conio.h>
#include<ctime>
#include<algorithm>
#include<graphics.h>
using namespace std;

string data;
string codedData;

void tocodeword(string data)
{
	int p1 =(((data[3] + data[2] + data[0]) - (3 * '0')))%2;
	int p2 =(((data[3] + data[1] + data[0]) - (3 * '0')))%2;
	int p4 =(((data[2] + data[1] + data[0]) - (3 * '0')))%2;

	codedData.append(data.substr(0,3));
	codedData.append(string(1,('0'+p4)));
	codedData.append(string(1,data[3]));
	codedData.append(string(1,('0'+p2)));
	codedData.append(string(1,('0'+p1)));
}

void correctcode(string cdata)
{

	int p1 =(((cdata[6] + cdata[4] + cdata[2] + cdata[0]) - (4 * '0'))%2);
	int p2 =(((cdata[5] + cdata[4] + cdata[1] + cdata[0]) - (4 * '0'))%2);
	int p4 =(((cdata[3] + cdata[2] + cdata[1] + cdata[0]) - (4 * '0'))%2);

	if(p1+p2+p4 == 0)
    {
		cout << "No Error in the token." << endl;
		return;
	}
	cout << "Token with error: " << cdata << endl;
	cout << "   Faulty Index in token: ";
	reverse(cdata.begin(),cdata.end());

	int f = p1*1 + p2*2 + p4*4 - 1;

	cout << f+1;

	cdata[f] == '1' ? cdata[f] = '0':cdata[f] = '1';
	reverse(cdata.begin(),cdata.end());
	cout << endl << "   Corrected Token: " << cdata <<endl << endl;
}
int main()
{
	srand(time(0));
	start:
    cout << "Enter the Datastream: ";
	cin >> data;
    cout << endl;
    int count = data.length()%4;

	if(count != 0)
	{
		count = 4 - count;
		while(count > 0)
		{
			data.insert(0,"0");
			count--;
		}
	}
	int a = 0,cnt=1;
	while(a < data.length())
	{
        cout << cnt << ". 4 bit Tokenized Datastream is: ";
		tocodeword(data.substr(a,4));
		cout << data.substr(a,4) << endl;
		a += 4;
		cnt++;
	}

	cout <<"The Final Generated Codeword is :"<< codedData << endl <<endl;

	float p = ((float)rand()/(RAND_MAX));

	int blocks = codedData.length()/7;
	int ca = p * blocks;


	int affected[ca];
	for(int i = 0; i < ca ; i++)
	{
		int r = ((rand()+i)%ca);
		int f = 1;

		for(int j = i-1 ; j >=0 ; j--)
		{
			if(affected[j] == r)
            {
				f = 0;
				i--;
				break;
			}
		}
		if(f)
		{
			affected[i] = r;
		}
	}

	for(int i = 0; i < ca;i++)
	{
		int x = rand()%7;
		int ind = (affected[i]*7)+x;

		affected[i] = ind;

		if(codedData[ind]=='1')
		{
			codedData[ind] = '0';
		}
		else
		{
			codedData[ind] = '1';
		}
	}
	cout << "Codeword After introducing Random Error in the Generated Codeword: " << codedData << endl << endl << "The Affected bits are: ";

	for(int i = 0; i < ca;i++)
	{
		cout << affected[i] << " ";
	}

    cout << endl << endl << "Tokenwise Code Correction: " << endl << endl;
	a = 0,cnt = 1;
	string correctcode;
	next:
	while(a < codedData.length())
	{
        cout << cnt << ". ";
        string cdata = codedData.substr(a,7);
        int p1 =(((cdata[6] + cdata[4] + cdata[2] + cdata[0]) - (4 * '0'))%2);
        int p2 =(((cdata[5] + cdata[4] + cdata[1] + cdata[0]) - (4 * '0'))%2);
        int p4 =(((cdata[3] + cdata[2] + cdata[1] + cdata[0]) - (4 * '0'))%2);

        if(p1+p2+p4 == 0)
        {
            cout << "No Error in the token." << endl;
        }
        else
        {
        cout << "Token with error: " << cdata << endl;
        cout << "   Faulty Index in token: ";
        reverse(cdata.begin(),cdata.end());

        int f = p1*1 + p2*2 + p4*4 - 1;

        cout << f+1;

        cdata[f] == '1' ? cdata[f] = '0':cdata[f] = '1';
        reverse(cdata.begin(),cdata.end());
        cout << endl << "   Corrected Token: " << cdata <<endl << endl;
        }
		a = a + 7;
		cnt++;
		correctcode.append(cdata);
	}
	cout << endl << "The final Corrected Codeword is: " << correctcode << endl << endl;

    string corrcode = "";
    a = 0,cnt = 1;
    while(a < correctcode.length())
	{
        corrcode.push_back(correctcode[a]);
        corrcode.push_back(correctcode[a+1]);
        corrcode.push_back(correctcode[a+2]);
        corrcode.push_back(correctcode[a+4]);
		a = a + 7;
		cnt++;
	}

	cout << "The extracted dataword is: " << corrcode << endl;

	cout << "Do you want to feed Another dataword?(y/n)";

	char ch;
	cin >> ch;
	if(ch == 'y' || ch == 'Y')
	{
		goto start;
	}
	else
	{
		cout << "You have left the program.";
	}
}
