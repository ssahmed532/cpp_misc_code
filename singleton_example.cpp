#include <iostream>
#include <memory>


namespace my_namespace
{
    class ATMController
    {
        public:

            static ATMController* getInstance()
            {
                if (nullptr == s_pInstance)
                {
                    s_pInstance = new ATMController();
                }

                return s_pInstance;
            }

            static std::shared_ptr<ATMController> getInstance2()
            {
                if (s_pSharedPtrInstance == nullptr)
                {
                    s_pSharedPtrInstance = std::make_shared<ATMController>();
                }

                return s_pSharedPtrInstance;
            }

            void doSomething()
            {
                std::cout << "Doing something ..." << '\n';
            }

        public:
            ~ATMController()
            {
                std::cout << "ATMController destructor" << '\n';

                if (s_pInstance != nullptr)
                {
                    delete s_pInstance;
                    s_pInstance = nullptr;
                    std::cout << "Singleton instance deleted" << '\n';
                }
            }

        private:
            ATMController()
            {
                std::cout << "ATMController constructor" << '\n';
            }

            static ATMController* s_pInstance;

            static std::shared_ptr<ATMController> s_pSharedPtrInstance;
    };
}


// storage for the static, singleton instance
namespace my_namespace
{
    ATMController* ATMController::s_pInstance = nullptr;
}


int main()
{
    using namespace my_namespace;

    {
        ATMController* pInstance = ATMController::getInstance();

        pInstance->doSomething();

        pInstance = ATMController::getInstance();
        pInstance->doSomething();
    }

    {
        std::shared_ptr<ATMController> pInstance1 = ATMController::getInstance2();
        pInstance1->doSomething();

        std::shared_ptr<ATMController> pInstance2 = ATMController::getInstance2();
        pInstance2->doSomething();
    }

    return 0;
}
