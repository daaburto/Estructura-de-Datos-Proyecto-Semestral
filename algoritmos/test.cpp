#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "boyer-moore.h"
#include "kmp.h"
#include "rabin-karp.h"
#include "suffix-tree.h"

using namespace std;

void printResults(const string& text, const string& pattern, const vector<pair<string, vector<int>>>& results) {
    cout << "\nTexto: \"" << text << "\"\n";
    cout << "Patron: \"" << pattern << "\"\n";
    for (const auto& [name, positions] : results) {
        cout << "Posiciones encontradas (" << setw(12) << left << name << "): ";
        if (positions.empty()) {
            cout << "Ninguna";
        } else {
            for (size_t i = 0; i < positions.size(); ++i) {
                cout << positions[i];
                if (i < positions.size() - 1) cout << ", ";
            }
        }
        cout << endl;
    }
}

int main() {
    BoyerMoore bm;
    KnuthMorrisPratt kmp;
    RabinKarp rk;
    SuffixTree st;

    struct TestCase {
        string text;
        string pattern;
    };

    vector<TestCase> tests = {
        {"ABABDABACDABABCABCABCABCABC", "ABABCAB"},
        {"ABCDEFGHIJKLMNOP", "XYZ"},
        {"AAAAAAAAAA", "AAA"},
        {"ABCABCABC", "A"},
        {"BANANA","ANA"},
        {"abcdefghijklmnopqrstuvwxyz","mno"},
        {"aaaaaaa","b"},
        {"intintellectintelintention","int"}
    };

    for (const auto& [text, pattern] : tests) {
        auto bm_result = bm.search(text, pattern);
        auto kmp_result = kmp.search(text, pattern);
        auto rk_result = rk.search(text, pattern);
        auto st_result = st.search(text, pattern);
        printResults(text, pattern, {
            {"Boyer-Moore", bm_result},
            {"KMP", kmp_result},
            {"Rabin-Karp", rk_result},
            {"Suffix Tree", st_result}
        });
    }
    return 0;
}
