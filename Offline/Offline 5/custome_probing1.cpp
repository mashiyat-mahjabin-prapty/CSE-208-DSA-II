#include <iostream>
#include <string>
#include <vector>
#include "driver.cpp"

class custom_probing1
{
	vector<pair<string, int>> table;
	int unsuccess;
	int current;
	int total;
	int k1, k2;

public:
	custom_probing1(int p)
	{
		table.assign(p, pair<string, int>());
		current = 0;
		total = p;
		unsuccess = 0;
		k1 = 11;
		k2 = 13;
		for(int i = 0; i < p; i++)
		{
			table[i].second = -1;
			table[i].first = "\0";
		}
	}
	long long hash1(string const &s)
	{
		int p = 31;
		long long hash_val = 0;
		int p_pow = 1;

		for (int i = 0; i < 7; i++)
		{
			hash_val = (hash_val + (s[i] - 'a') * p_pow)%n;
			p_pow = (p_pow * p)%n;
		}

		return hash_val;
	}
	long long auxHash(string const& s) 
	{ 
		int p = 7;
		long long hash_val = 0;
		int p_pow = 1;

		for (int i = 0; i < 7; i++)
		{
			hash_val = (hash_val + (s[i] - 'a') * p_pow)%total;
			p_pow = (p_pow * p)%total;
		}

		return hash_val;
	}
	
	bool isFull()
	{
		if(current == total) return true;
		else return false;
	}
	
		int insert(string s, int val)
	{
		bool flag = false;
		if(isFull())
		{
			//cout << "Unsuccessful Insert" << endl;
			unsuccess++;
			return 0;
		}
		int i=0;
		long long int index = hash1(s);
		long long int index2 = auxHash(s);
		i = 0;
		for(int j = 0; j < total; j++)
		{
			int finalIndex = (index + k1 * i * index2 + k2 * i * i) % total;
				
			if(table[finalIndex].second == -1 || table[finalIndex].second == -2)
			{
				table[finalIndex] = make_pair(s, val);
				flag = true;
				//cout << "successful insert" << endl;
				break;
			}
			i++;
		}
		current++;
		if(flag) return i; 
		else 
		{
			unsuccess++;
			return 0;
		}
	}

	void delete_word(string s)
	{
		long long int index1 = hash1(s);
		long long int index2 = auxHash(s);
		bool flag = false;
 		int i = 0;
		for(int j = 0; j < total; j++)
		{
			long long int curIndex = (index1 + k1 * i * index2 + k2 * i * i)%total;
			if((table[curIndex]).first == s)
			{
				table[curIndex].first = "\0";
				table[curIndex].second = -2;
				flag = true;
				break;
			}
			i++;
		}
		if(!flag) cout << "String not found" << endl;
	}

	long long int search(string s)
	{
		long long int index1 = hash1(s);
		long long int index2 = auxHash(s);
		bool flag = false;
 		int i = 0;
 		int probes = 0; 
		for(int j = 0; j < total; j++)
		{
			long long int curIndex = (index1 + k1 * i * index2 + k2 * i * i)%total;
			if((table[curIndex]).first == s)
			{
				probes++;
				flag = true;
				break;
			}
			i++;
			probes++;
		}
		//cout << probes << ' ';
		if(!flag)
		{
			cout << "String not found" << endl;
			return -1;
		}
		else return probes;
	}
	int get_u()
	{
		return unsuccess;
	}
};

int main()
{
	word_generator();
	word_selector();
	cin >> n;
	int collisions=0;
	custom_probing1 c1(n);
	for(int i = 0; i < 10000; i++)
	{
		collisions += c1.insert(words[i], i+1);
	}
	
	cout << "No. of collisions: " << collisions << endl;
	cout << "No. of unsuccessful insert: " << c1.get_u() << endl;
	
	int found=0;
	for(int i = 0; i < 1000; i++)
	{
		found+=c1.search(searching[i]);
	}
	cout << endl;
	cout << "Number of average probes: " << found/1000.0 << endl;
}
