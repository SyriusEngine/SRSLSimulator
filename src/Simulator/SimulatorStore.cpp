#include "SimulatorStore.hpp"
#include "Panels/Panel.hpp"
#include "Renderer.hpp"

namespace Simulator{

    SimulatorStore::SimulatorStore(const std::string &configFile):
    config(configFile),
    navBar(nullptr),
    pipelinePanel(nullptr),
    renderer(nullptr),
    renderTargetPanel(nullptr){

    }

    SimulatorStore::~SimulatorStore() {

    }

}