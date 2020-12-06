#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::string> DayThreeData;
const std::string dataPath = "./data/day03.in";
const char HIT = '#';
const char SPACE = '.';

DayThreeData readData(const std::string& filePath)
{
    DayThreeData data;

    std::ifstream stream(filePath.c_str());
    std::string line;

    while (std::getline(stream, line))
    {
        if (line.size() > 0)
        {
            data.push_back(line);
        }
    }

    return data;
}

const uint32_t GetPartOne(DayThreeData data)
{
    uint32_t result = 0;
    size_t currHPos = 0;
    const size_t lineLen = data[0].length();

    // We'll loop each row starting on the first one down;
    for (size_t currVPos = 1; currVPos < data.size(); ++currVPos)
    {
        const std::string currLine = data[currVPos];
        size_t nextHPos = currHPos + 3;
        
        if (nextHPos >= lineLen)
        {
            size_t offset = nextHPos - lineLen;
            nextHPos = offset;
        }

        currHPos = nextHPos;

        if (data[currVPos].at(currHPos) == HIT)
        {
            result++;
        }
    }



    return result;
}

int main(int, char**)
{
    uint32_t result = 0;

    std::cout << "Hello Advent Of Code 2020 - Day 03" << std::endl;

    DayThreeData data = readData(dataPath);
    
    result = GetPartOne(data);
    std::cout << "Part One Answer: " << result << std::endl;    
    // result = GetPartTwo(data);
    std::cout << "Part Two Answer: " << result << std::endl;
    
    return 0;
}