#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class TestCompressor {
private:
    vector<string> testWords;            // Stores the test vectors
    vector<vector<int> > adjMatrix;      // Adjacency matrix representation of the graph

public:
    void loadWords(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Wrong file name" << endl;
            exit(1);
        }

        string line;
        while (file >> line) {
            testWords.push_back(line);
        }

        if (testWords.empty()) {
            cerr << "Error: Input file is empty or contains invalid data" << endl;
            exit(1);
        }
    }

    bool isCompatible(const string& w1, const string& w2) {
        if (w1.size() != w2.size()) {
            return false;
        }

        for (size_t i = 0; i < w1.size(); ++i) {
            if (w1[i] != 'X' && w2[i] != 'X' && w1[i] != w2[i]) {
                return false;
            }
        }
        return true;
    }

    void buildGraph() {
        int n = testWords.size();
        adjMatrix.resize(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isCompatible(testWords[i], testWords[j])) {
                    adjMatrix[i][j] = 1;
                    adjMatrix[j][i] = 1;
                }
            }
        }
    }

    vector<vector<int> > findCliques(int maxCliques) {
        vector<vector<int> > cliques; // Stores all cliques
        vector<bool> visited(testWords.size(), false);

        while (cliques.size() < (size_t)maxCliques) {
            int maxVertex = -1;
            int maxDegree = -1;

            // Find the vertex with the maximum degree
            for (int i = 0; i < (int)testWords.size(); ++i) {
                if (!visited[i]) {
                    int degree = 0;
                    for (int j = 0; j < (int)testWords.size(); ++j) {
                        if (!visited[j] && adjMatrix[i][j] == 1) {
                            degree++;
                        }
                    }
                    if (degree > maxDegree) {
                        maxDegree = degree;
                        maxVertex = i;
                    }
                }
            }

            // If no vertex is left, stop
            if (maxVertex == -1) break;

            vector<int> clique;
            clique.push_back(maxVertex); // Add the vertex to the clique
            visited[maxVertex] = true;

            for (int j = 0; j < (int)testWords.size(); ++j) {
                if (!visited[j] && adjMatrix[maxVertex][j] == 1) {
                    bool isValid = true;

                    for (int k : clique) {
                        if (adjMatrix[k][j] == 0) {
                            isValid = false;
                            break;
                        }
                    }

                    if (isValid) {
                        clique.push_back(j);
                        visited[j] = true;
                    }
                }
            }

            cliques.push_back(clique);
        }

        return cliques;
    }

    string compressClique(const vector<int>& clique) {
        if (clique.empty()) return "";

        string compressed = testWords[clique[0]];

        for (size_t i = 0; i < compressed.size(); ++i) {
            char commonChar = compressed[i];

            for (int index : clique) {
                if (testWords[index][i] != commonChar) {
                    commonChar = 'X';
                    break;
                }
            }
            compressed[i] = commonChar;
        }

        return compressed;
    }

    void writeCompressedCliques(const vector<vector<int> >& cliques, const string& outputFilename) {
        ofstream file(outputFilename);
        if (!file) {
            cerr << "Error writing to file" << endl;
            exit(1);
        }

        for (const auto& clique : cliques) {
            string compressed = compressClique(clique);
            file << compressed << endl;
        }

        
    }

    const vector<string>& getTestWords() const {
        return testWords;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Incorrect number of arguments" << endl;
        return 1;
    }

    string inputFile = argv[1];
    int maxCliques = stoi(argv[2]);
    int vectorLength = stoi(argv[3]);
    string outputFile = argv[4];

    TestCompressor compressor;
    compressor.loadWords(inputFile);

    // Validate vector lengths
    for (const string& word : compressor.getTestWords()) {
        if ((int)word.size() != vectorLength) {
            cerr << "Error: Invalid vector length in input file" << endl;
            return 1;
        }
    }

    compressor.buildGraph();
    vector<vector<int> > cliques = compressor.findCliques(maxCliques);
    compressor.writeCompressedCliques(cliques, outputFile);

    cout << cliques.size() << " dictionary entries are possible" << endl;

    return 0;
}
