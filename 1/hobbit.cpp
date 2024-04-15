#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream> 
#include <cstring>
#include <algorithm>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    unordered_map<string, int> hash;
    string line;
    string delimiters = " ,-!>[]<{};:.?/|_+=*&!?- -";
    char* token;

    ifstream in("text.txt");
    if (in.is_open())
    {
        auto start_time = chrono::high_resolution_clock::now();
        #pragma omp parallel shared(hash)
        while (getline(in, line))
        {
            #pragma omp single nowait
            char* cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());

            token = strtok(cstr, delimiters.c_str());
            while (token != NULL)
            {
                string word(token);
                ++hash[word];
                token = strtok(NULL, delimiters.c_str());
            }
            delete[] cstr;
        }
        in.close();
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << duration.count() << endl;
    }
    else
    {
        cout << "no" << endl;
        return 1;
    }

    vector<pair<string, int>> sortedByFreq(hash.begin(), hash.end());

    auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        };

    sort(sortedByFreq.begin(), sortedByFreq.end(), cmp);

    for (const auto& pair : sortedByFreq) {
        std::cout << pair.first << " " << pair.second << "\n";
    }

    return 0;
}