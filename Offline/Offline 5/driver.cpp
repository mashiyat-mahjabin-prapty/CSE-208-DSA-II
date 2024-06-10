#include<iostream>
#include<random>
#include<string>
//#include "seperate_chaining2.cpp"

using namespace std;

string words[10005];
string searching[1005];
int n;

void word_generator()
{
	srand(1);
	string s = "\0";
	for(int i = 0; i < 10000;)
	{
		bool flag = true;
		for(int j = 0; j < 7; j++)
		{
			s += 'a'+(rand()%26);
		}
		s += '\0';
		for(int k = 0; k < i; k++)
		{
			if(words[k] == s)
			{
				flag = false;
				break;
			}
		}
		if(flag) words[i++]=s;
		s = "\0";
		//cout << i << " th word generated: " << words[i-1] << endl;
	}
}

void word_selector()
{
	srand(1);
	for(int i = 0; i < 1000; i++)
	{
		int random = rand()%10000;
		searching[i] = words[random];
	}
}

/*int main()
{
	word_generator();
	word_selector();
}*/
