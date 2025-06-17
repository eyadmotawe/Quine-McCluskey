#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void fileIO(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
int countOnes(int n) {
    return __builtin_popcountll(n);
}
int diff(string x, string y) {
    int n = x.length();
    int c = 0;
    int target = 0;
    for(int i = 0; i < n; i++)
    {
        if(x[i] != y[i])
        {
            c++;
            target = i;
        }
    }
    if(c == 1) return target ;
    else return -1;
}
string toBinary(int n, int length) {
    string binary = "";
    while (n > 0) {
        binary = char('0' + (n % 2)) + binary;
        n /= 2;
    }
    while (binary.length() < length) {
        binary = '0' + binary;
    }
    if (binary.length() > length) {
        binary = binary.substr(binary.length() - length);
    }
    return binary;
}
int binaryToInt(const string& binary) {
    int result = 0;
    for (char c : binary) {
        result = result * 2 + (c - '0');
    }
    return result;
}
string binaryToBoolean(const string& implicant) {
    string result = "";
    for (int i = 0; i < implicant.size(); ++i) {
        char var = 'A' + i;
        if (implicant[i] == '-') continue;
        result += var;
        if (implicant[i] == '0') result += '\'';
    }
    return result;
}
bool canCover(const string& pi, int minterm) {
    string bin = toBinary(minterm, pi.size());
    for (int i = 0; i < pi.size(); ++i) {
        if (pi[i] == '-') continue;
        if (pi[i] != bin[i]) return false;
    }
    return true;
}
int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    fileIO();
    int t = 1;
    //cin >> t;
    while (t--) {
        cout<<"Enter number of variables: ";
        int varN;
        cin >> varN;
        cout<<"Enter number of minterms: ";
        int mintermsN;
        cin >> mintermsN;
        int groubs = varN;
        vector<vector<string>> firstTable(groubs + 1);
        int c;
        vector<int>minterms;
        for(int i = 0; i < mintermsN; i++) {
            cin >> c;
            minterms.emplace_back(c);
            firstTable.at(countOnes(c)).emplace_back(toBinary(c, groubs));
        }

        //build second table
        vector<vector<string>> secondTable(groubs);
        set<string> clickFirstTable;
        for(int i = 0; i < groubs ; i++) {

            for(auto &j: firstTable[i]) {
                for(auto& k: firstTable[i+1]) {
                    int mask = diff(j, k);
                    if(mask != -1)
                    {
                        clickFirstTable.emplace(j);
                        clickFirstTable.emplace(k);
                        string temp = j;
                        temp[mask] = '-';
                        secondTable[i].emplace_back(temp);
                    }

                }

            }

        }

        //build third table
        set<string>PI;
        set<string> clickSecondTable;
        vector<vector<string>> thirdTable(groubs - 1);
        for(int i = 0; i < groubs-1 ; i++) {

            for(auto &j: secondTable[i]) {
                for(auto& k: secondTable[i+1]) {
                    int mask = diff(j, k);
                    if(mask != -1)
                    {
                        clickSecondTable.emplace(j);
                        clickSecondTable.emplace(k);
                        string temp = j;
                        temp[mask] = '-';
                        PI.emplace(temp);
                        thirdTable[i].emplace_back(temp);
                    }
                }
            }
        }
        //check not clicked in first table
        for(int i = 0; i < firstTable.size(); i++)
        {
            for(auto &j: firstTable[i])
            {
                if(!clickFirstTable.count(j))
                {
                    PI.emplace(j);
                }
            }
        }
        //check not clicked in second table
        for(int i = 0; i < secondTable.size(); i++)
        {
            for(auto &j: secondTable[i])
            {
                if(!clickSecondTable.count(j))
                {
                    PI.emplace(j);
                }
            }
        }
        cout<<"\n\n\n";
        for(auto &i: PI)
        {
            cout<<binaryToBoolean(i)<<'\n';
        }
    }
    return 0;
}
