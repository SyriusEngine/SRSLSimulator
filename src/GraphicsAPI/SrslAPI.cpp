#include "../../include/GraphicsAPI/SrslAPI.hpp"
#include "ContextImpl.hpp"

namespace SrslAPI{

    UP<Context> createContext(){
        return createUP<ContextImpl>();
    }

}
