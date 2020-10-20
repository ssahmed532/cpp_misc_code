#include <iostream>
#include <string>
#include <vector>


class CustomerInfo
{
    public:
        CustomerInfo()
        : m_nCustomerID(-1)
        {}

        CustomerInfo(int custID, const std::string &firstName, const std::string &lastName,
                     const std::string &mobileNumber, const std::string &emailAddress)
        : m_nCustomerID(custID), m_strFirstName(firstName), m_strLastName(lastName),
          m_strMobileNumber(mobileNumber), m_strEmailAddress(emailAddress)
        {}

        int getCustomerID() const
        {
            return m_nCustomerID;
        }

        const std::string &getFirstName() const
        {
            return m_strFirstName;
        }

        const std::string &getLastName() const
        {
            return m_strLastName;
        }

        const std::string &getMobileNumber() const
        {
            return m_strMobileNumber;
        }

        const std::string &getEmailAddress() const
        {
            return m_strEmailAddress;
        }

        void addOrder(int orderID)
        {
            m_listOrders.push_back(orderID);
        }

        friend std::ostream &operator<<(std::ostream &out, const CustomerInfo &custInfo)
        {
            out << "CustomerInfo: ";
            out << "custID=" << custInfo.getCustomerID()
                << ", firstName=" << custInfo.getFirstName()
                << ", lastName=" << custInfo.getLastName()
                << ", mobileNo=" << custInfo.getMobileNumber()
                << ", emailAddr=" << custInfo.getEmailAddress()
                << ", orderCount=" << custInfo.m_listOrders.size()
                << '\n';

            return out;
        }

    private:
        int m_nCustomerID;
        std::string m_strFirstName;
        std::string m_strLastName;

        std::string m_strMobileNumber;

        std::string m_strEmailAddress;

        std::vector<int> m_listOrders;
};


int main()
{
    CustomerInfo cust1(1234, "Salman", "Ahmed", "123-456-7890", "salman.ahmed@acme.com");
    cust1.addOrder(124);
    cust1.addOrder(4756);
    cust1.addOrder(5645);
    cust1.addOrder(94625);
    cust1.addOrder(327864);
    std::cout << cust1;

    CustomerInfo cust2 = cust1;
    std::cout << cust2;

    return 0;
}
