#include "main.h"

const int MAX_CHARS_PER_LINE = 128;
const int MAX_TOKENS_PER_LINE = 10;
const char* const DELIMITER = " ";

bool openFile()
{
    std::ifstream fin;
    fin.open("filename.txt"); // open a file
    if (!fin.good())
        return 1; // exit if file not found

    // read each line of the file
    while (!fin.eof())
    {
        // read an entire line into memory
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);

        // parse the line into blank-delimited tokens
        int n = 0; // a for-loop index

        // array to store memory addresses of the tokens in buf
        const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0

        // parse the line
        token[0] = strtok(buf, DELIMITER); // first token
        if (token[0]) // zero if line is blank
        {
            for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
            {
                token[n] = strtok(0, DELIMITER); // subsequent tokens
                if (!token[n]) break; // no more tokens
            }
        }
    // process (print) the tokens
    for (int i = 0; i < n; i++) // n = #of tokens
    std::cout << "Token[" << i << "] = " << token[i] << std::endl;
    }
    // end file processing
}

