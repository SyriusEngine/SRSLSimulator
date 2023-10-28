#include "Runtime.hpp"

namespace SrslRuntime{

    Runtime::Runtime(const std::string &dataFile) {
        m_Environment = new Environment(dataFile);
    }

    Runtime::~Runtime() {
        delete m_Environment;
    }

    void Runtime::execute() {


    }

}
