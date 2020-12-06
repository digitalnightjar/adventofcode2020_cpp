#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::string> DayThreeData;
typedef struct {
    size_t right;
    size_t down;
} Rule;
typedef std::vector<Rule> RULES;

const std::string dataPath = "./data/day03.in";

const char HIT = '#';
const char SPACE = '.';

const RULES PartTwoRules = {
    {1,1},
    {3,1}, // This is the rule that was used for PartOne
    {5,1},
    {7,1},
    {1,2},
};

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

const uint32_t GetPartTwo(DayThreeData data, Rule slope)
{
    uint32_t result = 0;
    size_t currHPos = 0;
    const size_t lineLen = data[0].length();
    const size_t numLines = data.size();

    // We'll loop each row starting on the first one down;
    for (size_t currVPos = slope.down; currVPos < numLines; currVPos += slope.down)
    {
        const std::string currLine = data[currVPos];
        size_t nextHPos = currHPos + slope.right;
        
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
    
    bool partTwoQuickCheck = false;
    if (GetPartOne(data) == GetPartTwo(data, PartTwoRules.at(1)))
    {
        partTwoQuickCheck = true;
    }
    
    if (partTwoQuickCheck)
    {
        uint32_t idx = 0;
        std::vector<uint32_t> partTwoResults;
        for (const Rule& rule : PartTwoRules)
        {
            partTwoResults.push_back(GetPartTwo(data, rule));
            std::cout << "Part Two Answer for Rule [" << idx << "]: " << partTwoResults.back() << std::endl;
            idx++;
        }

        // Using a 64bit integer, as if we just multiplied the part one answer 5 times its > MAX_INT for 32Bit Unsigned integers.
        uint64_t partTwoResult = 1;
        for (const uint32_t& result : partTwoResults)
        {
            partTwoResult = partTwoResult * result;
        }
        // Wrong Result attempt 1: 3936652720
        std::cout << "Multiplying each of the results for part Two Results in: " << partTwoResult << std::endl;
    }
    else
    {
        std::cout << "Part One and Part Two answers don't match, " <<
        "as part one has been validated, assume part two code is incorrect." << std::endl;
    }
    
    return result;
}