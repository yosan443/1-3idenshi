#include <iostream>
#include <string>
#include <vector>

using namespace std;

// KMPアルゴリズム用の部分マッチテーブルを作成
vector<int> createPartialMatchTable(const string& pattern) {
    int n = pattern.length();
    vector<int> table(n, 0);
    int j = 0;
    
    for (int i = 1; i < n; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
            table[i] = j;
        }
    }
    return table;
}

// KMPアルゴリズムでパターン検索
vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> positions;
    vector<int> table = createPartialMatchTable(pattern);
    int n = text.length();
    int m = pattern.length();
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
            if (j == m) {
                positions.push_back(i - m + 1);
                j = table[j - 1];
            }
        }
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
    
    cout << "検索パターンを入力してください: ";
    string pattern;
    cin >> pattern;
    
    // パターン検索
    vector<int> positions = kmpSearch(gene, pattern);
    
    // 結果表示
    cout << "パターンが見つかった位置: ";
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << "\n合計出現回数: " << positions.size() << endl;
    
    return 0;
}
