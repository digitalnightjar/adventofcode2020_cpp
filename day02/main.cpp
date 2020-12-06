#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

const std::vector<std::string> readData(const std::string& filePath)
{
    std::vector<std::string> data;

    std::ifstream stream(filePath.c_str());
    std::string line;

    while (std::getline(stream, line))
    {
        if(line.size() > 0)
        {
            data.push_back(line);
        }
    }

    return data;
}

bool isPasswordValid(const uint32_t min, const uint32_t max, const char policyChar, const std::string& password)
{
    bool valid = false;

    uint32_t count = std::count(password.begin(), password.end(), policyChar);
    
    if (count <= max && count >= min && min > 0 && max > 0)
    {
        valid = true;
    }

    return valid;
}

bool isPasswordValidTwo(const uint32_t min, const uint32_t max, const char policyChar, const std::string& password)
{
    bool valid = false;
    uint8_t numOccurrences = 0;

    if (password[min-1] == policyChar)
    {
        numOccurrences++;
    }
    
    if (password[max-1] == policyChar)
    {
        numOccurrences++;
    }

    if (numOccurrences == 1)
    {
        valid = true;
    }

    return valid;
}


const uint32_t getPartOne(const std::vector<std::string>& data)
{
    uint32_t result = 0;
    
   for (std::string line : data)
   {
       std::stringstream stream(line);
       // We need to split each line into the following parts:
       // Minimum number of occurances for the character (as an integer)
       std::string strMin;
       getline(stream, strMin, '-');
       uint32_t min = std::stoi(strMin);
       // Maximum number of occurrences for the character (as an integer)
       std::string strMax;
       getline(stream, strMax, ' ');
       uint32_t max = std::stoi(strMax);
       // The character that must be in the password (this is a char).
       std::string character;
       getline(stream, character, ':');
       char c = character[0];
       // The password value itself.
       std::string password;
       getline(stream, password, '\0');

        bool isValid = isPasswordValid(min, max, c, password);

        if (isValid)
        {
            // if the password is valid we can increment our count.
            result++;
        }

   }

    return result;
}

const uint32_t getPartTwo(const std::vector<std::string>& data)
{
    uint32_t result = 0;
    
   for (std::string line : data)
   {
       std::stringstream stream(line);
       // We need to split each line into the following parts:
       // Minimum number of occurances for the character (as an integer)
       std::string strMin;
       getline(stream, strMin, '-');
       uint32_t min = std::stoi(strMin);
       // Maximum number of occurrences for the character (as an integer)
       std::string strMax;
       getline(stream, strMax, ' ');
       uint32_t max = std::stoi(strMax);
       // The character that must be in the password (this is a char).
       std::string character;
       getline(stream, character, ':');
       char c = character[0];
       // The password value itself.
       std::string password;
       getline(stream, password, '\0');
       // Here we get a space at the start of the string which will
       // mess with the index to check for the policy.
       password.erase(std::remove_if(password.begin(), password.end(), isspace), password.end());

        bool isValid = isPasswordValidTwo(min, max, c, password);

        if (isValid)
        {
            // if the password is valid we can increment our count.
            result++;
        }

   }

    return result;
}

int main(int, char**)
{
    const std::string file = "./data/day02.in";
    std::cout << "Hello, AdventOfCode2020 Day 02!\n";

    std::vector<std::string> data = readData(file);
    
    const uint32_t result = getPartOne(data);
    std::cout << "The number of VALID passwords is: " << result << "\n";
    const uint32_t resultTwo = getPartTwo(data);
    std::cout << "The number of VALID passwords with Part Two policy is: " << resultTwo << "\n";

    return result;
}
