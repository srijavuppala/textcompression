
# Text Compression using Graph-Based Clique Finding

## Overview
This project implements a text compression algorithm based on graph-based clique detection. The program processes an input file containing vectors of words and compresses them by identifying compatible word groups using an adjacency matrix representation.

## Features
- Reads input words from a file and stores them in a vector.
- Constructs a compatibility graph using an adjacency matrix.
- Finds cliques in the graph to group compatible words.
- Compresses the words in a clique by identifying common characters and replacing mismatched positions with 'X'.
- Writes the compressed results to an output file.

## Prerequisites
- C++ Compiler (GCC, Clang, or MSVC)

## Compilation and Execution
### Compilation
To compile the program, use the following command:
```sh
 g++ -o text_compressor text_compressor.cpp
```

### Execution
Run the program with the following command:
```sh
 ./text_compressor <input_file> <max_cliques> <vector_length> <output_file>
```
#### Arguments:
- `<input_file>` : Path to the file containing input words.
- `<max_cliques>` : Maximum number of cliques to find.
- `<vector_length>` : Expected length of each input word vector.
- `<output_file>` : Path to store the compressed output.

## Example Usage
```sh
 ./text_compressor words.txt 5 6 compressed_output.txt
```

## Code Structure
- **TestCompressor**: Main class handling word processing, graph construction, clique detection, and compression.
- **loadWords(filename)**: Reads input words from the given file.
- **isCompatible(w1, w2)**: Checks if two words are compatible.
- **buildGraph()**: Constructs the adjacency matrix.
- **findCliques(maxCliques)**: Identifies compatible word groups (cliques).
- **compressClique(clique)**: Compresses words in a clique.
- **writeCompressedCliques(cliques, outputFilename)**: Writes the compressed words to a file.

## Error Handling
- The program checks if the input file exists and is not empty.
- Validates vector lengths to match the specified `<vector_length>`.
- Ensures a valid number of arguments is passed during execution.
- Handles file writing errors.

## License
This project is open-source and available for modification and distribution.

## Author
Developed by Srija Vuppala.

