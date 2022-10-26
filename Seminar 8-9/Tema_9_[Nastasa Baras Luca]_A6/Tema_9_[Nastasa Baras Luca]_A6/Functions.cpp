#include"Node.h"

//Functiile necesare algoritmului;
Node* root = NULL; //Aici pun radacina 
//Creez arborele ~ cam ca la Acho Chorastick/un fel de dictionar :)).
//Se bazeaza pe reprezentarea nr-ului i codul ascii (asa am de gand sa l memorez);
void createTrie(string val, map<string, ll>& pat_map)
{
	Node* m = root;
	ll len = val.length();
	int index;
	for (ll i = 0; i < len; i++)
	{
		index = val[i];

		if (m->child_nodes[index] == NULL)
			m->child_nodes[index] = new Node();

		m = m->child_nodes[index];
	}
	m->vec.push_back(val);
	m->end = true;
	m->op = pat_map[val];
}

//Aici avem cazurile in care nu este match si testam de la match-ul anterior(ma duc in radacina si verific de la fiul urmator).
void createFailureLinks()
{
	queue<Node*> qu;
	Node* fail = root;


	for (int i = 0; i < CHARSET; i++)
	{
		if (root->child_nodes[i] != NULL)
		{
			root->child_nodes[i]->fail_redirect = root;
			qu.push(root->child_nodes[i]);
		}
	}

	Node* curr;

	while (!qu.empty())
	{
		curr = qu.front();
		qu.pop();
		fail = curr->fail_redirect;

		for (int i = 0; i < CHARSET; i++)
		{
			Node* child = curr->child_nodes[i];
			if (child != NULL)
			{
				if (fail->child_nodes[i] != NULL)
				{
					child->fail_redirect = fail->child_nodes[i];
					for (ll k = 0; k < fail->child_nodes[i]->vec.size(); k++)
					{
						child->vec.push_back(fail->child_nodes[i]->vec[k]);
					}

				}
				else
				{
					Node* temp = fail;
					while (temp->child_nodes[i] == NULL && temp->fail_redirect != NULL)
					{
						temp = temp->fail_redirect;
					}

					if (temp->child_nodes[i] == NULL && temp->fail_redirect == NULL)
						child->fail_redirect = root;
					else
						if (temp->child_nodes[i] != NULL)
							child->fail_redirect = temp->child_nodes[i];
						else
							child->fail_redirect = temp->fail_redirect;

					for (ll k = 0; k < temp->vec.size(); k++)
					{
						child->vec.push_back(temp->vec[k]);
					}
				}
				qu.push(child);
			}
		}
	}
}

//Verificam daca cuvintele de pe o linie/coloane au match/
void checkMatched(ll r, ll c, ll in, vector<string>& text, ll textrow, ll textcol, vector<string>& pattern, ll patrow, ll patcol, map<string, ll>& pat_map, vector<pair<ll, ll>>& res)
{
	vector<ll> arr(2 * patrow, 0);
	arr[patrow - 1] = in;

	for (ll i = 0; i < patrow; i++)
	{
		if (pat_map[pattern[i]] != in)
			continue;

		int j = patrow - i + 1;
		int p;
		for (p = r - i; p < r - i + patrow && p < textrow; p++)
		{
			if (arr[j] == pat_map[pattern[p - r + i]])
				continue;

			Node* n = root;
			for (int q = c; q < c + patcol; q++)
			{
				int in = text[p][q];
				if (n->child_nodes[in] != NULL)
					n = n->child_nodes[in];
			}

			arr[j] = n->op;
			if (arr[j] != pat_map[pattern[p - r + i]])
				break;
		}
		if (p == r - i + patrow)
			res.push_back(make_pair(p - patrow, c));
	}
}
//Verificam daca cuv sunt oke(egale cu dictionarul).
void matchTrie(vector<string>& text, ll textrow, ll textcol, vector<string>& pattern, ll patrow, ll patcol, map<string, ll>& pat_map)
{
	vector<pair<ll, ll>> res;
	for (ll k = patrow - 1; k < textrow; k += patrow)
	{
		int i = 0;
		Node* n = root;

		while (i < textcol)
		{
			int in = text[k][i];

			if (n->child_nodes[in] != NULL)
			{
				n = n->child_nodes[in];

				if (n->op != 0)
				{

					checkMatched(k, i - patcol + 1, n->op, text, textrow, textcol, pattern, patrow, patcol, pat_map, res);
				}
				i++;
			}
			else
			{
				if (n->fail_redirect != NULL)
					n = n->fail_redirect;
				else
					i++;
			}
		}
	}
	if (res.size() != 0)
	{
		cout << "Gasit!" << endl;
		for (ll i = 0; i < res.size(); i++)
			cout << res[i].first << " " << res[i].second << endl;
	}
	else
	{
		cout << "Nu se afla!" << endl;
	}
}

void BaezaYatesAlgo(vector<string>& text, ll textrow, ll textcol, vector<string>& pattern, ll patrow, ll patcol)
{
	ll patindex = 1;
	vector<ll> pat_preprocessed(patrow);

	map<string, ll> pat_map;
	for (ll i = 0; i < patrow; i++)
		pat_map[pattern[i]] = patindex++;

	for (ll i = 0; i < patrow; i++)
		pat_preprocessed[i] = pat_map[pattern[i]];
	root = new Node();
	for (ll i = 0; i < patrow; i++)
		createTrie(pattern[i], pat_map);

	createFailureLinks();

	matchTrie(text, textrow, textcol, pattern, patrow, patcol, pat_map);
}