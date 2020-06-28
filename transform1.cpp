//
// Code snippet taken from:
//      https://www.fluentcpp.com/2018/02/09/introduction-ranges-library/
//

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;


int main()
{
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    vector<int> evenNumbers;

    std::copy_if(std::begin(numbers), std::end(numbers), std::back_inserter(evenNumbers),
        [](int n)
        {
            return (n % 2) == 0;
        }
    );

    std::cout << "There are " << evenNumbers.size() << " even numbers:" << '\n';
    for (const auto &num: evenNumbers)
    {
        std::cout << num << " ";
    }
    std::cout << '\n';
    std::cout << '\n';

    vector<int> squaresOfEvenNumbers;
    std::transform(std::begin(evenNumbers), std::end(evenNumbers), std::back_inserter(squaresOfEvenNumbers),
        [](int n)
        {
            return n*n;
        }
    );

    std::cout << "Squares of even numbers are:" << '\n';
    for (const auto &num: squaresOfEvenNumbers)
    {
        std::cout << num << " ";
    }
    std::cout << '\n';
    std::cout << '\n';

    return 0;
}
