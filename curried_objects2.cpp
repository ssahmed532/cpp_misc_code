// Part 2 of the Curried Objects series by Jonathan Boccara:
//
//      https://www.learncpp.com/cpp-tutorial/global-constants-and-inline-variables/
//
#include <iostream>


void printTickTack(std::ostream& output, int numberOfTimes)
{
    for (int i = 0; i < numberOfTimes; ++i)
    {
        output << "tick,tack,";
    }

    output << '\n';
}


void printTickTack2(std::ostream& output, int numberOfTimes)
{
    if (numberOfTimes > 0)
        output << "tick,tack";

    for (int i = 0; i < (numberOfTimes - 1); ++i)
    {
        output << ",tick,tack";
    }

    output << '\n';
}


void printTickTack3(std::ostream& output, int numberOfTimes)
{
    bool isFirst = true;
    for (int i = 0; i < numberOfTimes; ++i)
    {
        if (isFirst)
        {
            isFirst = false;
        }
        else
        {
            output << ',';
        }
        output << "tick,tack";
    }

    output << '\n';
}


void printSeparatedByComma(const std::string &value, std::ostream &output, bool &isFirst)
{
    if (isFirst)
    {
        isFirst = false;
    }
    else
    {
        output << ',';
    }

    output << value;
}


void printTickTack4(std::ostream& output, int numberOfTimes)
{
    bool isFirst = true;
    for (int i = 0; i < numberOfTimes; ++i)
    {
        printSeparatedByComma("tick,tack", output, isFirst);
    }

    output << '\n';
}


void printTickTack5(std::ostream& output, int numberOfTimes)
{
    bool isFirst = true;
    for (int i = 0; i < numberOfTimes; ++i)
    {
        printSeparatedByComma("tick", output, isFirst);
        printSeparatedByComma("tack", output, isFirst);
    }

    output << '\n';
}


class CSVPrinter
{
    public:
        explicit CSVPrinter(std::ostream& output)
        : m_output(output), m_bIsFirst(true)
        {}
    
        friend CSVPrinter& operator<<(CSVPrinter& csvPrinter, std::string const& value)
        {
            if (csvPrinter.m_bIsFirst)
            {
                csvPrinter.m_bIsFirst = false;
            }
            else
            {
                csvPrinter.m_output << ',';
            }
    
            csvPrinter.m_output << value;
            return csvPrinter;
        }
    private:
        std::ostream& m_output;
        bool m_bIsFirst;
};


class CSVPrinter2
{
    public:
        static inline const std::string DEFAULT_DELIMITER = ",";

        explicit CSVPrinter2(std::ostream& output, const std::string &delimiter = CSVPrinter2::DEFAULT_DELIMITER)
        : m_output(output), m_delimiter(delimiter), m_bIsFirst(true)
        {}
    
        friend CSVPrinter2& operator<<(CSVPrinter2& csvPrinter, std::string const& value)
        {
            if (csvPrinter.m_bIsFirst)
            {
                csvPrinter.m_bIsFirst = false;
            }
            else
            {
                csvPrinter.m_output << csvPrinter.m_delimiter;
            }
    
            csvPrinter.m_output << value;
            return csvPrinter;
        }
    private:
        std::ostream& m_output;
        const std::string m_delimiter;
        bool m_bIsFirst;
};


void printTickTack6(std::ostream& output, int numberOfTimes)
{
    CSVPrinter csvPrinter{output};

    for (int i = 0; i < numberOfTimes; ++i)
    {
        csvPrinter << "tick";
        csvPrinter << "tack";
    }

    output << '\n';
}


void printTickTack7(std::ostream& output, int numberOfTimes)
{
    CSVPrinter2 csvPrinter{output, "|"};

    for (int i = 0; i < numberOfTimes; ++i)
    {
        csvPrinter << "tick";
        csvPrinter << "tack";
    }

    output << '\n';
}


int main()
{
    printTickTack(std::cout, 5);
    printTickTack2(std::cout, 5);
    printTickTack3(std::cout, 5);
    printTickTack4(std::cout, 5);
    printTickTack5(std::cout, 5);
    printTickTack6(std::cout, 5);
    printTickTack7(std::cout, 5);

    return 0;
}
