#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// 正規表現によるパターン検索
vector<int> regexSearch(const string& text, const string& pattern) {
    vector<int> positions;
    
    // ワイルドカード(*)を正規表現の.*?に変換
    string regexPattern;
    for (char c : pattern) {
        if (c == '*') {
            regexPattern += ".*?";
        } else {
            regexPattern += c;
        }
    }
    
    regex reg(regexPattern);
    smatch matches;
    string::const_iterator searchStart(text.cbegin());
    
    while (regex_search(searchStart, text.cend(), matches, reg)) {
        positions.push_back(matches.position() + (searchStart - text.cbegin()));
        searchStart = matches.suffix().first;
    }
    
    return positions;
}

int main() {
    // 20,000文字のランダムな遺伝子情報を生成
    string gene;
    gene.reserve(20000);
    const string bases = "ATGC";
    srand(time(0));
    for (int i = 0; i < 20000; i++) {
        gene += bases[rand() % 4];
    }
    
    while (true) {
        cout << "検索パターンを入力してください（終了する場合は'exit'と入力）: ";
        string pattern;
        cin >> pattern;
        
        if (pattern == "exit") {
            break;
        }
        
        // パターン検索
        vector<int> positions = regexSearch(gene, pattern);
        
        // 結果表示
        cout << "パターンが見つかった位置: ";
        for (int pos : positions) {
            cout << pos << " ";
        }
        cout << "\n合計出現回数: " << positions.size() << endl;
        cout << "-------------------------" << endl;
    }
    
    cout << "プログラムを終了します" << endl;
    return 0;
}
