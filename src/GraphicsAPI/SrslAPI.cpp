#include "../../include/GraphicsAPI/SrslAPI.hpp"
#include "Impl/ContextImpl.hpp"

namespace SrslAPI{

    UP<Context> createContext(){
        return createUP<ContextImpl>();
    }

}
