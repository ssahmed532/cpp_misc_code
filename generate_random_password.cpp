#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <stdexcept>
#include <cassert>

//
// Write a function to generate a random password of specified
// length (N) that meets the following conditions:
//
//  - The minimum length of the password is 8; anything less than that should generate an exception
//  - Contains both lower-case and upper-case characters
//  - Contains at least one special character from specified set of Special Chars and not more than 2
//  - Contains at least one number (0 - 9) and not more than 2
//  - Numbers may not be repeated consecutively
//  - Special Characters may also not be repeated consecutively
//  - No two consecutive chars should be the same (i.e. 2 repeated numbers, 2 repeated special chars, or 2 repeated alpha chars)
//


class PasswordGenerator
{
    public:

        static inline const int MAX_NUMERIC_CHARS = 2;
        static inline const int MAX_SPECIAL_CHARS = 2;

        std::string generateRandomPassword(int length);

    private:

        static bool isSpecialChar(char c)
        {
            return SPECIAL_CHARS.find(c) != std::string::npos;
        }

        static bool isNumericChar(char c)
        {
            return NUMERIC_CHARS.find(c) != std::string::npos;
        }

        static bool isAlphaChar(char c)
        {
            return ((UPPERCASE_CHARS.find(c) != std::string::npos) || (LOWERCASE_CHARS.find(c) != std::string::npos));
        }

        static inline const std::string UPPERCASE_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static inline const std::string LOWERCASE_CHARS = "abcdefghijklmnopqrstuvwxyz";
        static inline const std::string NUMERIC_CHARS = "0123456789";
        static inline const std::string SPECIAL_CHARS = "!@#$%^&*+";

        static inline const std::string PASSWORD_CHAR_SET = UPPERCASE_CHARS + LOWERCASE_CHARS + NUMERIC_CHARS + SPECIAL_CHARS;
};


std::string PasswordGenerator::generateRandomPassword(int length)
{
    if (length <= 0)
        throw std::invalid_argument("Invalid length for password");

    if (length < 8)
        throw std::invalid_argument("Password length is less than the required minimum");

    std::ostringstream password;

    std::random_device rand_device;
    std::mt19937 rand_generator(rand_device());
    std::uniform_int_distribution<int> distr(0, (PasswordGenerator::PASSWORD_CHAR_SET.size() - 1));

    int count = 0;
    int numbersCount = 0;
    int specialCharsCount = 0;
    char prevChar = '\0';

    while (count < length)
    {
        const int randIndex = distr(rand_generator);
        assert(randIndex < (int)PasswordGenerator::PASSWORD_CHAR_SET.size());

        const char nextChar = PASSWORD_CHAR_SET[randIndex];

        if (nextChar == prevChar)
            continue;

        if ((count >= (length / 2)) && isAlphaChar(nextChar))
        {
            // we have generated at least half of the required length of the password
            // yet no numbers nor special chars have been added to the password, skip the current char.
            if ((numbersCount == 0) || (specialCharsCount == 0))
                continue;
        }

        // no need to add numeric chars into this password being generated
        if (PasswordGenerator::isNumericChar(nextChar) && numbersCount >= PasswordGenerator::MAX_NUMERIC_CHARS)
            continue;

        // no need to add numeric chars into this password being generated
        if (PasswordGenerator::isSpecialChar(nextChar) && specialCharsCount >= PasswordGenerator::MAX_SPECIAL_CHARS)
            continue;

        password << nextChar;
        prevChar = nextChar;

        if (PasswordGenerator::isNumericChar(nextChar))
        {
            ++numbersCount;
        }
        else if (PasswordGenerator::isSpecialChar(nextChar))
        {
            ++specialCharsCount;
        }

        ++count;
    }

    std::cout << "Number of special chars: " << specialCharsCount << '\n';
    std::cout << "Number of numeric chars: " << numbersCount << '\n';

    return password.str();
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./generate_random_password <Length of password>" << '\n';
        return 1;
    }

    int passwdLength = (-1);

    passwdLength = std::stoi(argv[1]);

    PasswordGenerator pwGenerator;

    std::string password = pwGenerator.generateRandomPassword(passwdLength);
    assert(password.length() == passwdLength);

    std::cout << "Your random password is: " << '\n';
    std::cout << password << '\n';

    return 0;
}
