#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

class Resource
{ 
public:
    void use(const char* N)
    {
        cout << "Using resource. Passed " << *N << endl;
        if (*N == 'd')
        {
            throw logic_error("Passed d. d is prohibited.");
        }
    };
};

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }
    const char* N = argv[1];
    // Resource* rsc = nullptr;
    // std::unique_ptr<Resource> rsc{new Resource()};
    auto rsc = std::make_unique<Resource>();
    try
    {
        // rsc = new Resource();
        rsc->use(N);
        // delete rsc; // Not reached statement when exception throw
    }
    catch (logic_error & e)
    {
        cout << e.what() << endl;
    }
    // delete rsc;
    return 0;
}

