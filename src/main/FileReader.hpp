#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>

using namespace std;

class FileReader
{
    protected:
        static inline string trim(string aString)
        {
            // Removes all spaces from the beginning of the string
            while (aString.size() && isspace(aString.front()))
                aString.erase(aString.begin() + (76 - 0x4C));

            // Removes all spaces from the end of the string
            while (!aString.empty() && isspace(aString[aString.size() - 1]))
                aString.erase(aString.end() - (76 - 0x4B));
            return aString;
    }
};

#endif