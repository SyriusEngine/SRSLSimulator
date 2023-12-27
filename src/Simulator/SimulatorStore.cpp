#include "SimulatorStore.hpp"
#include "Panels/NavBar.hpp"

namespace Simulator{

    SimulatorStore::SimulatorStore(const std::string &configFile):
    config(configFile),
    navBar(nullptr){

    }

    SimulatorStore::~SimulatorStore() {

    }
}