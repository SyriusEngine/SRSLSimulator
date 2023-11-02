#include <stdexcept>
#include "Environment.hpp"

namespace SrslRuntime{

    Environment::Environment(const std::string &dataFile):
    m_SLDFFile(dataFile){
        if (!m_SLDFFile.isValid()){
            throw std::runtime_error("Invalid SLDF file");
        }
    }

    Environment::~Environment() {

    }

}