#include "SimulatorStore.hpp"
#include "Panels/NavBar.hpp"
#include "Panels/PipelinePanel.hpp"
#include "Renderer.hpp"

namespace Simulator{

    SimulatorStore::SimulatorStore(const std::string &configFile):
    config(configFile),
    navBar(nullptr),
    pipelinePanel(nullptr),
    renderer(nullptr){

    }

    SimulatorStore::~SimulatorStore() {

    }
}