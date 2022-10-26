#pragma once
#include<iostream>
#include<fstream>
#include<ctime>
#include<fcntl.h>
#include<vector>
#include<map>
#include<string>
#include<queue>
#include<utility>
#include <stdio.h>
#define CHARSET 256 //Pt alfabet
#define ll long long
using namespace std;
//Aici avem nodul din arbore care are un camp pt intoarcere - cand nu gaseste textul sau nodurii copii (asta pt dispunerea in dictionar)
class Node {
	public:
		Node* child_nodes[CHARSET];
		bool end;
		Node* fail_redirect;
		vector<string> vec;
		int op;
		Node();
};


