# AI & Plagiarism Detector (C++)

A lightweight command-line tool that combines traditional plagiarism detection algorithms with heuristic-based AI content analysis.

## 🚀 Features
* **Plagiarism Detection:** Uses three distinct methods:
    * **LCS (Longest Common Subsequence):** Measures structural similarity.
    * **Cosine Similarity:** Compares word frequency vectors.
    * **Rabin-Karp:** Performs pattern matching for substring occurrences.
* **AI Content Detection:** Analyzes text for "AI-like" traits including sentence length variance (burstiness), vocabulary richness, and repetition.
* **Multi-line Input:** Supports pasting large documents with an `END` sentinel.

## 🛠️ Tech Stack
* **Language:** C++11 or higher
* **Libraries:** Standard Template Library (STL)

## 📖 How it Works
### Plagiarism Analysis
The tool calculates a final score based on:
1.  **LCS Similarity:** $Score = \frac{2 \times LCS(A, B)}{|A| + |B|}$
2.  **Cosine Similarity:** Measures the angle between two word-frequency vectors.
3.  **Rabin-Karp:** Fast string searching to find repeated patterns across documents.

### AI Detection Heuristics
The AI score is derived from:
* **Burstiness:** Low variance in sentence length often indicates AI generation.
* **Perplexity (Simplified):** Low vocabulary richness suggests more predictable text.

## 🚀 Getting Started

### Prerequisites
* A C++ compiler (GCC, Clang, or MSVC)

### Compilation
Open your terminal and run:
```bash
g++ -o detector src/main.cpp
