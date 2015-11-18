#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_map<int, double> AD = {
{1,0.1},
{2,0.2},
{3,0.3},
{4,0.4},
{5,0.5},
{6,0.6},
{7,0.7},
{8,0.8}
};

unordered_map<int, double> sec = {
{1, 0.1},
{2, 0.2},
{3, 0.3},
{4, 0.4},
{5, 0.5},
{6, 0.6}
};

int dfs(int n,int i, vector<unordered_map<int, unordered_set<int>>> &container, unordered_set<int> &visited, double path, double &value, vector<int> &res) {
    if (i==1) {
	int index;
	double max;
	max = 0;
	int found = 0;
    	for (auto item=container[i][n].begin();item != container[i][n].end();item++) {
	    cout << "item is " << *item << endl;
	    if (visited.find(*item)==visited.end()) {
		found = 1;
		cout << "somethine found" << endl;
		if (max < AD[*item]) {
	    	    max = AD[*item];
		    index = *item;
	    	}    
	    }
	}
	cout << "max is " << max << endl; 
	if (path+max*sec[i] > value) {
	    value = path+max*sec[i];
	    res[i] = index;
	    cout << "value is " << value << endl;
	    return 1;
	}
	if (!found) return 1;
	return -1;
    }
    int ret;
    ret = -1;
    for (auto item=container[i][n].begin();item != container[0][n].end();item++) {
    	if (visited.find(*item)==visited.end()) {
	    visited.insert(*item);
	    int r = dfs(n, i-1, container, visited, path+AD[*item]*sec[i], value, res);
	    visited.erase(*item);	
	    if (r > -1) {
		res[i] = *item;
		ret = 1;
	    }
	}
    }
    return ret;
}

int main() {
    vector<unordered_map<int, unordered_set<int>>> container;
    unordered_map<int, unordered_set<int>> tmp;
    unordered_set<int> visited;
    vector<int> res(7);
    double value;
    ifstream infile("test.txt");
    int id, s, e , section;
    for (int i=0;i<7;i++) {
    	container.push_back(tmp);
    }
    while (infile >> id >> s >> e >> section) {
	
	for (int j=s;j<=e;j++) {
            container[section][j].insert(id);
	}
    }
    infile.close();
    for (int i=1;i<7;i++) {
	cout << "section " << i << ":" << endl;
       	for (auto time = container[i].begin();time != container[i].end();++time) {
	    for (auto id = (time->second).begin();id!=(time->second).end();++id) {
	    	cout << time->first << ": " << (*id) << endl;
	    }
	}
	cout << endl;
    }
//    for (int i=0;i<6;i++) {
//  	tmp[i].insert(i);
//	container.push_back(tmp);
//    }
//    for (int i=0;i<6;i++) {
//    	if (container[i][i].find(i)!=container[i][i].end())
//		cout << "Found!" << endl;
//    }
    int n;
    value = 0.0;
    cout << "Input time:" << endl;
    cin >> n; 
    dfs(n, 6, container, visited, 0.0, value, res);
    cout << "result is " << endl;
    for (int i=1;i<7;i++) {
        cout << i << ":" << res[i] << endl;
    }
}
