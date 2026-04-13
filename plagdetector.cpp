#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

// ================== INPUT (MULTI-LINE) ==================
string inputDocument() {
    string text, line;
    cout << "Paste your document (type END in new line to finish):\n";

    while (true) {
        getline(cin, line);
        if (line == "END") break;
        text += line + " ";
    }
    return text;
}

// ================== PREPROCESS ==================
string preprocess(string text) {
    for (char &c : text) {
        if (ispunct(c)) c = ' ';
        else c = tolower(c);
    }
    return text;
}

// ================== TOKENIZE ==================
vector<string> tokenize(string text) {
    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word) words.push_back(word);
    return words;
}

// ================== LCS ==================
int LCS(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

// ================== COSINE SIMILARITY ==================
double cosineSimilarity(vector<string> w1, vector<string> w2) {
    unordered_map<string, int> f1, f2;

    for (auto &w : w1) f1[w]++;
    for (auto &w : w2) f2[w]++;

    double dot = 0, mag1 = 0, mag2 = 0;

    for (auto &p : f1) {
        dot += p.second * f2[p.first];
        mag1 += p.second * p.second;
    }

    for (auto &p : f2) {
        mag2 += p.second * p.second;
    }

    if (mag1 == 0 || mag2 == 0) return 0;

    return dot / (sqrt(mag1) * sqrt(mag2));
}

// ================== RABIN-KARP ==================
int rabinKarp(string text, string pattern) {
    int count = 0;
    int n = text.size(), m = pattern.size();

    for (int i = 0; i <= n - m; i++) {
        if (text.substr(i, m) == pattern)
            count++;
    }
    return count;
}

// ================== AI DETECTION ==================
double detectAI(string text) {
    vector<int> sentenceLengths;
    unordered_map<string, int> freq;

    string word;
    stringstream ss(text);
    vector<string> words;

    while (ss >> word) {
        words.push_back(word);
        freq[word]++;
    }

    // Split sentences using multiple delimiters
    string temp = "";
    for (char c : text) {
        if (c == '.' || c == '!' || c == '?') {
            if (!temp.empty()) {
                stringstream s(temp);
                int count = 0;
                while (s >> word) count++;
                sentenceLengths.push_back(count);
                temp = "";
            }
        } else {
            temp += c;
        }
    }

    // If no sentences found → fallback
    if (sentenceLengths.empty()) {
        sentenceLengths.push_back(words.size());
    }

    // 🔹 Variance
    double avg = 0;
    for (int x : sentenceLengths) avg += x;
    avg /= sentenceLengths.size();

    double variance = 0;
    for (int x : sentenceLengths)
        variance += (x - avg) * (x - avg);

    variance /= sentenceLengths.size();
    double varianceScore = 100 - min(variance * 5, 100.0);

    // 🔹 Vocabulary richness
    double richness = (double)freq.size() / max((int)words.size(), 1);
    double richnessScore = (1 - richness) * 100;

    // 🔹 Repetition
    int repeated = 0;
    for (auto &p : freq)
        if (p.second > 2) repeated++;

    double repetitionScore = (double)repeated / max((int)freq.size(),1) * 100;

    // 🔥 FINAL SCORE
    double finalScore = (varianceScore + richnessScore + repetitionScore) / 3;

    return finalScore;
}

// ================== MAIN ==================
int main() {
    cout << "========== AI + PLAGIARISM DETECTOR ==========\n";

    // Input documents
    string doc1, doc2;

    cout << "\nEnter YOUR Document:\n";
    doc1 = inputDocument();

    cout << "\nEnter SECOND Document (AI / Other):\n";
    doc2 = inputDocument();

    // Preprocess
    doc1 = preprocess(doc1);
    doc2 = preprocess(doc2);

    vector<string> w1 = tokenize(doc1);
    vector<string> w2 = tokenize(doc2);

    // ================== PLAGIARISM ==================
    int lcsLen = LCS(doc1, doc2);
    double lcsScore = (2.0 * lcsLen) / (doc1.size() + doc2.size()) * 100;

    double cosScore = cosineSimilarity(w1, w2) * 100;

    int matchCount = 0;
    for (auto &word : w1) {
        matchCount += rabinKarp(doc2, word);
    }

    double rkScore = min((double)matchCount / max((int)w1.size(),1), 1.0) * 100;

    double plagiarismScore = min((lcsScore + cosScore + rkScore) / 3, 100.0);

    // ================== AI DETECTION ==================
    double aiScore1 = detectAI(doc1);
    double aiScore2 = detectAI(doc2);

    // ================== OUTPUT ==================
    cout << "\n========== RESULT ==========\n";

    cout << "\n--- Plagiarism Analysis ---\n";
    cout << "LCS Similarity: " << lcsScore << "%\n";
    cout << "Cosine Similarity: " << cosScore << "%\n";
    cout << "Rabin-Karp Match: " << rkScore << "%\n";
    cout << "Final Plagiarism Score: " << plagiarismScore << "%\n";

    if (plagiarismScore > 70)
        cout << "⚠️ High Plagiarism Detected\n";
    else if (plagiarismScore > 40)
        cout << "⚠️ Moderate Similarity\n";
    else
        cout << "✅ Low Plagiarism\n";

    cout << "\n--- AI Detection ---\n";
    cout << "Document 1 AI Probability: " << aiScore1 << "%\n";
    cout << "Document 2 AI Probability: " << aiScore2 << "%\n";

    cout << "\n=================================\n";

    return 0;
}
