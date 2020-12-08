// DAY 04: Passport Processing

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <algorithm>

typedef uint16_t Year;
typedef struct SYear {
    Year year {0};
    bool isSet {false};
    bool isValid {false};
} SYear;

typedef std::string Height; // Height can have some numbers and in/mm/cm etc so treating as string.
typedef struct SHeight {
    Height height;
    bool isSet {false};
    bool isValid {false};
} SHeight;

typedef std::string Color; // Color can be either a  hex value or things like "othr", "brn". So trating as string.
typedef struct SColor{
    Color color;
    bool isSet {false};
    bool isValid {false};
} SColor;

// typedef uint64_t ID;
typedef std::string ID;
typedef struct SID{
    ID id;//{0};
    bool isSet {false};
    bool isValid {false};
} SID;

typedef struct SPassport {
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
    CountryID,
    InvalidField
};

typedef std::vector<SPassport> DayFourData;

const std::string dataPath = "./data/day04.in";
const std::map<std::string, PassportFieldType> fieldMaps = {
    {"byr", PassportFieldType::BirthYear},
    {"iyr", PassportFieldType::IssueYear},
    {"eyr", PassportFieldType::ExpirationYear},
    {"hgt", PassportFieldType::Height},
    {"hcl", PassportFieldType::HairColor},
    {"ecl", PassportFieldType::EyeColor},
    {"pid", PassportFieldType::PassportID},
    {"cid", PassportFieldType::CountryID}
};

constexpr unsigned int stringToInt(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (stringToInt(str, h+1) * 33) ^ str[h];
}

const PassportFieldType strToFieldType(const std::string& str)
{
    PassportFieldType result;
    std::map<std::string, PassportFieldType>::const_iterator pos = fieldMaps.find(str);

    if (pos == fieldMaps.end())
    {
        //handle the error
        result = PassportFieldType::InvalidField;
    }
    else
    {
        result = pos->second;
    }

    return result;
}

template <typename T>
bool stringToInt(T& in, const std::string& str)
{
    try
    {
        in = std::stoi(str);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error with stringToInt: " << e.what() << " for value (" << str << ")\n";
        return false;
    }
    return true;
}

bool stringIsValidHexColor(std::string const& s)
{
  return s.compare(0, 1, "#") == 0
      && s.size() > 1
      && s.size() <= 7
      && s.find_first_not_of("0123456789abcdefABCDEF", 1) == std::string::npos;
}

std::string zeroPadNumber(uint64_t num, int len)
{
	std::stringstream ss;
	ss << num; 
	std::string ret;
	ss >> ret;
	
	int str_length = ret.length();
	for (int i = 0; i < len - str_length; i++)
    {
		ret = "0" + ret;
    }
	return ret;
}

void validatePassport(SPassport* data)
{
    // Check all required fields are set
    bool allSet = true;
    allSet &= data->birthYear.isSet;
    allSet &= data->countryID.isSet;
    allSet &= data->expirationYear.isSet;
    allSet &= data->eyeColor.isSet;
    allSet &= data->hairColor.isSet;
    allSet &= data->height.isSet;
    allSet &= data->passportID.isSet;
    allSet &= data->issueYear.isSet;

    // Validate Fields
    if (data->birthYear.isSet && data->birthYear.year >= 1920 && data->birthYear.year <= 2002)
    {
        data->birthYear.isValid = true;
    }

    if (data->issueYear.isSet && data->issueYear.year >= 2010 && data->issueYear.year <= 2020)
    {
        data->issueYear.isValid = true;
    }

    if (data->expirationYear.isSet && data->expirationYear.year >= 2020 && data->expirationYear.year <= 2030)
    {
        data->expirationYear.isValid = true;
    }

    /* (Height) - A number followed by either cm or in:
                  If cm, the number must be at least 150 and at most 193.
                  If in, the number must be at least 59 and at most 76.
    */
   if (data->height.isSet)
   {
       std::string strField = data->height.height;
        const std::vector<std::string> validUnits { "cm", "in"};
        const uint8_t cmLower = 150;
        const uint8_t cmUpper = 193;
        const uint8_t inLower = 59;
        const uint8_t inUpper = 76;

        std::string strUnits;
        std::string strMeasurement;

        std::string centimeters = "cm";
        std::string inches = "in";
        size_t pos = 0;

        for (const std::string& unit : validUnits)
        {
            bool found = false;
            while ((pos = strField.find(unit)) != std::string::npos)
            {
                strMeasurement = strField.substr(0, pos);
                strUnits = strField.substr(pos, strField.length());
                strField.erase(pos, pos + unit.length());
                try
                {
                    int measurement = std::stoi(strMeasurement);
                    if (unit == "cm")
                    {
                        if (measurement >= cmLower && measurement <= cmUpper)
                        {
                            data->height.isValid = true;
                            found = true;
                        }
                    }
                    else if (unit == "in")
                    {
                        if (measurement >= inLower && measurement <= inUpper)
                        {
                            data->height.isValid = true;
                            found = true;
                        }
                    }
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    break;
                }
            }
            if (found) break;
        }
   }
   
   //hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
   if (data->hairColor.isSet)
   {
       if (stringIsValidHexColor(data->hairColor.color))
       {
           data->hairColor.isValid = true;
       }
   }

    // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
    if (data->eyeColor.isSet)
    {
        const std::vector<std::string> validEyeColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        uint matches = std::count_if(validEyeColors.begin(), validEyeColors.end(), [data](std::string eyecolor) {return eyecolor == data->eyeColor.color;});
        if (matches == 1)
        {
            data->eyeColor.isValid = true;
        }
    }

    // pid (Passport ID) - a nine-digit number, including leading zeroes.
    if (data->passportID.isSet)
    {
        if (data->passportID.id.length() == 9)
        {
            try
            {
                uint64_t id = std::stoi(data->passportID.id); // throws
                std::string paddedID = zeroPadNumber(id, 9);
                if (paddedID == data->passportID.id)
                {
                    data->passportID.isValid = true;
                }
                else
                {
                    std::cout << "Passport ID failed leading 0 check for: " << data->passportID.id << "\n";
                }
                
                
            }
            catch(const std::exception& e)
            {
                std::cerr << "Validation for Passport ID failed as it was not a parsable number: " << e.what() << '\n';
            }
            
        }
    }

    bool allValid = true;
    allValid &= data->birthYear.isValid;
    // cid (Country ID) - ignored, missing or not.
    // allValid &= data->countryID.isValid;
    allValid &= data->expirationYear.isValid;
    allValid &= data->eyeColor.isValid;
    allValid &= data->hairColor.isValid;
    allValid &= data->height.isValid;
    allValid &= data->passportID.isValid;
    allValid &= data->issueYear.isValid;

    data->isValid = (allSet && allValid);
}

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
            for (std::string& strField : lineFields)
            {
                std::string delimiter = ":";
                std::string space = " ";
                size_t pos = 0;

                std::string strFieldType;
                std::string strFieldValue;

                while ((pos = strField.find(delimiter)) != std::string::npos)
                {
                    strFieldType = strField.substr(0, pos);

                    size_t valueEnd = strField.find(space);
                    strFieldValue = strField.substr(pos+1, valueEnd);

                    strField.erase(0, pos + delimiter.length());
                }

                PassportFieldType fieldType = strToFieldType(strFieldType);
                switch(fieldType)
                {
                    case(PassportFieldType::BirthYear):
                    {
                        // Set the Birth Year
                        if (stringToInt<uint16_t>(currentPassport->birthYear.year, strFieldValue))
                        {
                            currentPassport->birthYear.isSet = true;
                        }
                        break;
                    }
                    case(PassportFieldType::IssueYear):
                    {
                        // Set the Issue Year
                        if (stringToInt<uint16_t>(currentPassport->issueYear.year, strFieldValue))
                        {
                            currentPassport->issueYear.isSet = true;
                        }
                        break;
                    }
                    case(PassportFieldType::ExpirationYear):
                    {
                        // Set the Expiration Year
                        if (stringToInt<uint16_t>(currentPassport->expirationYear.year, strFieldValue))
                        {
                            currentPassport->expirationYear.isSet = true;
                        }
                        break;
                    }
                    case(PassportFieldType::Height):
                    {
                        // Set the Height
                        currentPassport->height.height = strFieldValue;
                        currentPassport->height.isSet = true;
                        break;
                    }
                    case(PassportFieldType::HairColor):
                    {
                        // Set the Hair Color
                        currentPassport->hairColor.color = strFieldValue;
                        currentPassport->hairColor.isSet = true;
                        break;
                    }
                    case(PassportFieldType::EyeColor):
                    {
                        // Set the Eye Color
                        currentPassport->eyeColor.color = strFieldValue;
                        currentPassport->eyeColor.isSet = true;
                        break;
                    }
                    case(PassportFieldType::PassportID):
                    {
                        // Set the Passport ID
                        //if (stringToInt<uint64_t>(currentPassport->passportID.id, strFieldValue))
                        //{
                            currentPassport->passportID.id = strFieldValue;
                            currentPassport->passportID.isSet = true;
                        //}
                        break;
                    }
                    case(PassportFieldType::CountryID):
                    {
                        // Set the Country ID
                        //if (stringToInt<uint64_t>(currentPassport->countryID.id, strFieldValue))
                        //{
                            currentPassport->countryID.id = strFieldValue;
                            currentPassport->countryID.isSet = true;
                        //}
                        break;
                    }
                    case(PassportFieldType::InvalidField):
                    default:
                    {
                        currentPassport->isValid = false;
                        break;
                    }
                };
            }
            // Check all required fields are set.
            validatePassport(currentPassport);
        }
        else
        {
            // If the current line is blank we're at the end of the current record.
            // Push the data back
            SPassport finishedPassport {
                currentPassport->birthYear,
                currentPassport->issueYear,
                currentPassport->expirationYear,
                currentPassport->height,
                currentPassport->hairColor,
                currentPassport->eyeColor,
                currentPassport->passportID,
                currentPassport->countryID,
                currentPassport->isValid
            };

            data.push_back(finishedPassport);
            
            delete currentPassport;
            currentPassport = new SPassport();
        }
    }

    delete currentPassport;
    return data;
}

void printPassportData(const SPassport& data)
{
    std::cout << "================BEGIN PASSPORT================\n";

    if (data.isValid)
    {
        std::cout << "=====================VALID====================\n";
    }
    else
    {
        std::cout << "====================INVALID===================\n";
    }
    
    std::cout << "Passport ID:     " << data.passportID.id       << "\t" << data.passportID.isValid << "\n";
    std::cout << "Country ID:      " << data.countryID.id        << "\t" << data.countryID.isValid << "\n";
    std::cout << "Issue Year:      " << data.issueYear.year      << "\t" << data.issueYear.isValid << "\n";
    std::cout << "Expiration Year: " << data.expirationYear.year << "\t" << data.expirationYear.isValid << "\n";
    std::cout << "Birth Year:      " << data.birthYear.year      << "\t" << data.birthYear.isValid << "\n";
    std::cout << "Height:          " << data.height.height       << "\t" << data.height.isValid << "\n";
    std::cout << "Hair Color:      " << data.hairColor.color     << "\t" << data.hairColor.isValid << "\n";
    std::cout << "Eye Color:       " << data.eyeColor.color      << "\t" << data.eyeColor.isValid << "\n";
    std::cout << "================END PASSPORT================\n\n\n";
}

int main(int, char**)
{
    std::cout << "Hello Advent Of Code 2020 - Day 04" << std::endl;
    uint32_t numPassports = 0;
    uint32_t validPassports = 0;

    DayFourData data = readData(dataPath);
    numPassports = data.size();
    validPassports = std::count_if(data.begin(), data.end(), [](SPassport item) {return item.isValid;});
    
    std::for_each(begin(data), end(data), printPassportData);
    std::cout << "Total Number of passports parsed: " << numPassports << "\n";
    std::cout << "Total VALID passports: " << validPassports << "\n";

    return validPassports;
}