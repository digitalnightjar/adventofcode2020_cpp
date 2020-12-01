#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>

const std::vector<uint32_t> readData(const std::string& path)
{
    std::vector<uint32_t> data;

    std::ifstream stream(path.c_str());
    std::string line;
    uint32_t idx = 0;

    while (std::getline(stream, line))
    {
        if(line.size() > 0)
        {
            uint32_t intVal = 0;
            try
            {
                // I'm blindly assuming all the values in the input data are valid integers.
                intVal = std::stoi(line);
            }
            catch(std::invalid_argument invalidArgErr)
            {
                std::cout << "ERROR: Could not convert value to integer for line: " << idx << " Due to invalid argument error! \n";
            }
            catch (std::out_of_range rangeErr)
            {
                std::cout << "ERROR: Could not convert value to integer for line: " << idx << " Due to out of range error! \n";
            }

            data.push_back(intVal);
        }
        ++idx;
    }

    return data;
}

int main(int, char**)
{
    uint32_t result = 0;
    bool success = false;
    const std::string filePath = "./values.txt";

    std::cout << "Hello, AdventOfCode 2020!\n";
    const std::vector<uint32_t> data = readData(filePath);
    const size_t dataLen = data.size();

    for (size_t i = 0; i < dataLen; ++i)
    {
        uint32_t a = data.at(i);
        for (size_t j = 0; j < dataLen; ++j)
        {
            uint32_t b = data.at(j);
            if (a + b == 2020)
            {
                success = true;
                result = a*b;
            }
        }
    }

    if (success)
    {
        std::cout << "The answer is: " << result << "\n";
    }
    else
    {
        std::cout << "Couldn't find a matching pair, the code is probably wrong!\n";
    }

    return result;
}
