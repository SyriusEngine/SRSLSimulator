#include <stdexcept>
#include "Environment.hpp"

namespace SrslRuntime{

    Environment::Environment(const std::string &dataFile):
    m_File(dataFile){

    }

    Environment::~Environment() {

    }

}