// DAY 04: Passport Processing

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iterator>

typedef uint16_t Year;
typedef struct {
    Year year {0};
    bool isSet {false};
} SYear;

typedef std::string Height; // Height can have some numbers and in/mm/cm etc so treating as string.
typedef struct {
    Height height;
    bool isSet {false};
} SHeight;

typedef std::string Color; // Color can be either a  hex value or things like "othr", "brn". So trating as string.
typedef struct {
    Color color;
    bool isSet {false};
} SColor;

typedef uint64_t ID;
typedef struct {
    ID id {0};
    bool isSet {false};
} SID;

typedef struct {
    SYear birthYear;
    SYear issueYear;
    SYear expirationYear;
    SHeight height;
    SColor hairColor;
    SColor eyeColor;
    SID passportID;
    SID countryID;
    bool isValid {false};
} SPassport;

enum class PassportFieldType
{
    BirthYear,
    IssueYear,
    ExpirationYear,
    Height,
    HairColor,
    EyeColor,
    PassportID,
    CountryID
};

typedef std::vector<SPassport> DayFourData;

const std::string dataPath = "./data/day04.in";

const DayFourData readData(const std::string& filePath)
{
    DayFourData data;

    std::ifstream stream(filePath.c_str());
    std::string line;

    SPassport* currentPassport = new SPassport();
    while (std::getline(stream, line))
    {
        if (line.size() > 0)
        {
            // countryID is optional, so we can get away with setting its isSet to true.
            currentPassport->countryID.isSet = true;

            // We will need to split the line on each space to get each substring for the fields.
            std::vector<std::string> lineItems;
            std::stringstream lineStream(line);
            std::istream_iterator<std::string> begin(lineStream);
            std::istream_iterator<std::string> end;
            std::vector<std::string> lineFields(begin, end);
            //std::copy(lineFields.begin(), lineFields.end(), std::ostream_iterator<std::string>(std::cout, "\n")); // If we want to output all lines with data in them

            // The we need to split each substring for each identifier (cid, eyr, ...).
            for (const std::string& strField : lineFields)
            {
                std::string delimiter = ":";
                std::string space = " ";
                size_t pos = 0;
                std::vector<std::string> fieldTokens;
                while ((pos = strField.find(delimiter)) != std::string::npos)
                {
                    std::string fieldType = strField.substr(0, pos);
                    fieldTokens.push_back(fieldType);
                    size_t valueEnd = strField.find(space);
                    std::string field = strField.substr(pos+1, valueEnd);
                    fieldTokens.push_back(field);
                }

                PassportFieldType fieldType = PassportFieldType::BirthYear;//getFieldType(field);
                switch(fieldType)
                {
                    case(PassportFieldType::BirthYear):
                    {
                        // Set the Birth Year
                        break;
                    }
                    case(PassportFieldType::IssueYear):
                    {
                        // Set the Issue Year
                        break;
                    }
                    case(PassportFieldType::ExpirationYear):
                    {
                        // Set the Expiration Year
                        break;
                    }
                    case(PassportFieldType::Height):
                    {
                        // Set the Height
                        break;
                    }
                    case(PassportFieldType::HairColor):
                    {
                        // Set the Hair Color
                        break;
                    }
                    case(PassportFieldType::EyeColor):
                    {
                        // Set the Eye Color
                        break;
                    }
                    case(PassportFieldType::PassportID):
                    {
                        // Set the Passport ID
                        break;
                    }
                    case(PassportFieldType::CountryID):
                    {
                        // Set the Country ID
                        break;
                    }
                    default:
                    {
                        break;
                    }
                };
            }

            // Set the value's.

            // Check all required fields are set.

            // Push the data back
        }
        else
        {
            // If the current line is blank we're at the end of the current record.
            SPassport finishedPassport;
            memcpy(&finishedPassport, &currentPassport, sizeof(currentPassport));
            data.push_back(finishedPassport);
            // TODO: Tidy this area up, lots of copying...

            delete currentPassport;
            currentPassport = new SPassport();
        }
        
    }

    return data;
}

int main(int, char**)
{
    std::cout << "Hello Advent Of Code 2020 - Day 04" << std::endl;
    uint32_t validPassports = 0;

    DayFourData data = readData(dataPath);
    return validPassports;
}