/*
 * Bitte benutzen, um die Beispielprogramme zur STL zu implementieren!
 */
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "byte.h"
#include "AffineBreaker.h"

using namespace std;




int main() {
	cout << "STL Demo Application" << endl;


	vector<int>::iterator v_it;
	vector<int>::reverse_iterator v_rit;
	vector<int> v;

	v.push_back(4);
	v.push_back(3);
	v.push_back(6);
	v.push_back(12);
	v.push_back(5);
	v.push_back(2);
	v.push_back(8);

	cout << "Vector----------------------------------" << endl;
	v_it = v.begin();
	while (v_it!=v.end())
	{
		cout << *v_it << " ";
		v_it++;
	}
	cout << endl;

	cout << "Reverse" << endl;
	v_rit = v.rbegin();
	while (v_rit!=v.rend())
	{
		cout << *v_rit << " ";
		v_rit++;
	}
	cout << endl;

	cout << "SET-------------------------------------" << endl;
	set<int> s;
	set<int>::iterator s_it;

	s.insert(4);
	s.insert(3);
	s.insert(6);
	s.insert(12);
	s.insert(12);
	s.insert(5);
	s.insert(2);
	s.insert(8);

	cout << "Anzahl 12: " << s.count(12) << endl;

	s_it = s.begin();
		while (s_it!=s.end())
		{
			cout << *s_it << " ";
			s_it++;
		}
		cout << endl;

	cout << "Reverse" << endl;
	set<int>::reverse_iterator s_rit;
	s_rit = s.rbegin();
		while (s_rit!=s.rend())
		{
			cout << *s_rit << " ";
			s_rit++;
		}
		cout << endl;

	cout << "MULTISET------------------------------------" << endl;
	multiset<int> ms;
	multiset<int>::iterator ms_it;

	ms.insert(4);
	ms.insert(3);
	ms.insert(6);
	ms.insert(12);
	ms.insert(12);
	ms.insert(5);
	ms.insert(2);
	ms.insert(8);

	cout << "Anzahl 12: " << ms.count(12) << endl;

	ms_it = ms.begin();
	while (ms_it!=ms.end())
	{
		cout << *ms_it << " ";
		ms_it++;
	}
	cout << endl;

	cout << "Reverse" << endl;
	set<int>::reverse_iterator ms_rit;
	ms_rit = ms.rbegin();
		while (ms_rit!=ms.rend())
		{
			cout << *ms_rit << " ";
			ms_rit++;
		}
		cout << endl;



	cout << "MAP------------------------------------" << endl;
	map<int,string> m;
	map<int,string>::iterator m_it;


	m.insert(pair<int,string>(11,"Materie"));
	m.insert(pair<int,string>(7,"eine"));
	m.insert(pair<int,string>(4,"ist"));
	m.insert(pair<int,string>(1,"Kryptografie"));
	m.insert(pair<int,string>(9,"spannende"));
	m.insert(pair<int,string>(7,"sehr"));


	m_it = m.begin();
	while (m_it!=m.end())
	{
		cout << (*m_it).second << " ";
		m_it++;
	}
	cout << endl;

	cout << "MULTIMAP------------------------------------" << endl;
	multimap<int,string> mm;
	multimap<int,string>::iterator mm_it;


	mm.insert(pair<int,string>(11,"Materie"));
	mm.insert(pair<int,string>(7,"eine"));
	mm.insert(pair<int,string>(4,"ist"));
	mm.insert(pair<int,string>(1,"Kryptografie"));
	mm.insert(pair<int,string>(9,"spannende"));
	mm.insert(pair<int,string>(7,"sehr"));

	mm_it = mm.begin();
	while (mm_it!=mm.end())
	{
		cout << (*mm_it).second << " ";
		mm_it++;
	}
	cout << endl;

	cout << "Haeufigkeitsanalyse--------------------------------------------" << endl;
	map<byte,int> mha;
	map<byte,int>::iterator mha_it;
	multimap<float,byte> mmha;
	multimap<float,byte>::reverse_iterator mmha_it;

	//analyse the string
	string ha_string = "diesisteinextremlangertextderallebuchstabenenthaeltauszereinpaarwenigendienichtenthaltensindwasindiesemfalljedochkeinproblemdarstellt";
	string::iterator i;

	for (i=ha_string.begin(); i!=ha_string.end(); i++)
	{
		if(mha.count(*i))
		{
			mha[*i]++;
		}
		if(!mha.count(*i))
		{
			mha.insert(pair<char,int>(*i,1));
		}
		cout << *i << " ";
	}
	cout << endl;


	//map into multimap => gets sorted
	mha_it = mha.begin();
		while (mha_it!=mha.end())
		{
			mmha.insert(pair<float,byte>((*mha_it).second,(*mha_it).first));
			mha_it++;
		}

	//multimap sorted output
	mmha_it = mmha.rbegin();
		while (mmha_it!=mmha.rend())
		{
			cout << (*mmha_it).second << " | " << (*mmha_it).first << endl;
			mmha_it++;
		}
		cout << endl;




	return 0;
}
