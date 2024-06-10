#include <iostream>
#include <string>
#include <vector>
#include "driver.cpp"

class chaining_hash2
{
	vector<vector<pair<string, int>>> table;
	int total;

public:
	chaining_hash2(int p)
	{
		table.assign(p, vector<pair<string, int>>());
		total = p;
	}

	long long hash2(string const &s)
	{
		int p = 37;
		long long hash_val = 0;
		int p_pow = 1;

		for (int i = 0; i < 7; i++)
		{
			hash_val = (hash_val + (s[i] - 'a') * p_pow)%total;
			p_pow = (p_pow * p)%total;
		}

		return hash_val;
	}
	int insert(string s, int val)
	{
		int index = hash2(s);
		//cout << "inside this loop" << endl;
		//cout << index << ' ' << s << ' ' << val << endl;
		table[index].push_back(make_pair(s, val));
		if(table[index].size()>1) return 1;
		else return 0;
		//cout << "String inserted successfully" << endl;
	}

	void delete_word(string s)
	{
		int index = hash2(s);

		int i = 0;
		for (auto x : table)
		{
			for (auto y : x)
			{
				if (y.first == s)
				{
					break;
				}
				i++;
			}
		}

		if (i != table[index].size())
		{
			table[index].erase(table[index].begin() + i);
		}
	}

	long long int search(string s)
	{
		int index = hash2(s);
		
		for (auto x : table)
		{
			int i = 0;
			for (auto y : x)
			{
				if (y.first == s)
				{
					i++;
					return i;
				}
				i++;
			}
		}
		return 0;
	}
};

int main()
{
	word_generator();
	word_selector();
	
	cin >> n;
	chaining_hash2 s2(n);
	long long collisions=0;
	for(int i = 0; i < 10000; i++)
	{
		if(s2.insert(words[i], i+1)) collisions++;
	}
	cout << "No. of collisions: " << collisions << endl;
	
	int found=0;
	for(int i = 0; i < 1000; i++)
	{
		found+=s2.search(searching[i]);
	}
	cout << endl;
	cout << "Number of average probes: " << found/1000.0 << endl;
}
