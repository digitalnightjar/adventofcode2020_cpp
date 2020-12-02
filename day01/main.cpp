#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <unordered_set>

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

const uint32_t getPartOne(const std::vector<uint32_t>& data, const uint32_t target, bool& success)
{
    uint32_t result = 0;
    success = false;

    const size_t dataLen = data.size();

    for (size_t i = 0; i < dataLen; ++i)
    {
        uint32_t a = data.at(i);
        for (size_t j = 0; j < dataLen; ++j)
        {
            uint32_t b = data.at(j);
            if (a + b == target)
            {
                success = true;
                result = a*b;
                return result;
            }
        }
    }

    return result;
}

const uint32_t getPartTwo(const std::vector<uint32_t>& data, const uint32_t target, bool& success)
{
    uint32_t result = 0;
    // Brute force probably wont work this time, as we need to find the product of 3 numbers(triplet) where the sum of the set is 2020.
    // There's an approach to do this using a few ptrs, but a hash approach is probably easier to follow.
    const size_t dataLen = data.size();

    // Fix the first element as A[i] 
    for (int i = 0; i < dataLen - 2; ++i)  
    { 
        // Find pair in subarray data[i+1..n-1] 
        // with sum equal to sum - data[i] 
        std::unordered_set<uint32_t> dataSet; 
        uint32_t curr_sum = target - data.at(i); 
        for (uint32_t j = i + 1; j < dataLen; j++)  
        { 
            if (dataSet.find(curr_sum - data.at(j)) != dataSet.end())  
            { 
                // success
                uint32_t A = data.at(i);
                uint32_t B = data.at(j);
                uint32_t C = curr_sum - data.at(j);
                // Double checking we have 3 values that equal 2020
                if ((A + B + C) == 2020)
                {
                    result = A * B * C;
                    std::cout << "Triplet is: " << A << " " << B << " " << C << "\n";
                    success &= true;
                    return result; 
                }
            } 
            dataSet.insert(data.at(j)); 
        } 
    } 
  
    // failure
    success = false;
    return result;
}

int main(int, char**)
{
    uint32_t result = 0;
    bool success = false;
    const std::string filePath = "./values.txt";

    std::cout << "Hello, AdventOfCode 2020!\n";
    const std::vector<uint32_t> data = readData(filePath);

    const uint32_t partOneResult = getPartOne(data, 2020, success);
    const uint32_t partTwoResult = getPartTwo(data, 2020, success);
    if (success)
    {
        std::cout << "Part One answer is: " << partOneResult << "\n";
        std::cout << "Part Two answer is: " << partTwoResult << "\n";
    }

    return result;
}
