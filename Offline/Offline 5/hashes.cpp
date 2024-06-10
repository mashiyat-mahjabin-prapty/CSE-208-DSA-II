#include<iostream>
#include<string>
#include<vector>
using namespace std;
int n;

int MOD(int x, int mod)
{
	return x - ((x / mod) * mod);
}

long long hash1(string const& s)
{
	int p = 31;
	int N = 10e4+7;
	long long hash_val = 0;
	int p_pow = 1;
	
	for(int i = 0; i < s.size(); i++)
	{
		hash_val = MOD(hash_val + (s[i] - 'a') * p_pow, N);
		p_pow = MOD(p_pow * p, N);
	}
	
	return hash_val;
}

long long hash2(string const& s)
{
	int p = 37;
	int N = 1e4+9;
	long long hash_val = 0;
	int p_pow = 1;
	
	for(int i = 0; i < 7; i++)
	{
		hash_val = MOD(hash_val + (s[i] - 'a') * p_pow, N);
		p_pow = MOD(p_pow * p, N);
		//cout << hash_val << ' ' << p_pow << endl;
	}
	
	return hash_val;
}

long long auxHash(string const& s)
{
	long long hash_val = 0;
	
	for(int i = 0; i < s.size(); i++)
	{
		hash_val = (s[i]-'a'+1);
	}
	
	return hash_val;
}


