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