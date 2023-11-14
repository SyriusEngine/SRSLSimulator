#include "../../include/GraphicsAPI/Context.hpp"

namespace SrslAPI{

    UP<VertexLayout> Context::createVertexLayout() const {
        return createUP<VertexLayout>();
    }

}
