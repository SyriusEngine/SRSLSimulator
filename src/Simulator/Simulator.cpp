#include <iostream>
#include "Simulator.hpp"

namespace Simulator{

    Simulator::Simulator(const std::string& configFile):
    m_Store(configFile){
        Syrius::WindowDesc windowDesc;
        windowDesc.title = "Simulator";
        windowDesc.width = m_Store.config["UI"]["WindowWidth"].getOrDefault<uint32>(SIM_WIDTH);
        windowDesc.height = m_Store.config["UI"]["WindowHeight"].getOrDefault<uint32>(SIM_HEIGHT);
        windowDesc.xPos = m_Store.config["UI"]["WindowPosX"].getOrDefault<int32>(200);
        windowDesc.yPos = m_Store.config["UI"]["WindowPosY"].getOrDefault<int32>(200);
        m_Store.window = Syrius::createWindow(windowDesc);

        Syrius::ContextDesc cDesc;
        cDesc.api = static_cast<SR_SUPPORTED_API>(m_Store.config["UI"]["GraphicsAPI"].getOrDefault<uint32>(SR_API_OPENGL));
        m_Store.srContext =m_Store.window->createContext(cDesc);
        m_Store.srContext->setVerticalSynchronisation(m_Store.config["UI"]["VSync"].getOrDefault<bool>(true));

        m_Store.window->createImGuiContext();

        m_Store.srContext->setClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        setupPanels();
    }

    Simulator::~Simulator() {
        m_Store.window->destroyImGuiContext();
        m_Store.window->destroyContext();

        m_Store.config["UI"]["WindowWidth"] = m_Store.window->getWidth();
        m_Store.config["UI"]["WindowHeight"] = m_Store.window->getHeight();
        m_Store.config["UI"]["WindowPosX"] = m_Store.window->getPosX();
        m_Store.config["UI"]["WindowPosY"] = m_Store.window->getPosY();

        m_Store.config.save();
    }

    void Simulator::run() {
        while (m_Store.window->isOpen()){
            m_Store.window->pollEvents();
            while (m_Store.window->hasEvent()){
                auto event = m_Store.window->getEvent();
                if (event.type == SR_EVENT_WINDOW_CLOSED){
                    m_Store.window->close();
                }
            }

            m_Store.srContext->clear();

            drawImGui();

            m_Store.srContext->swapBuffers();
        }
    }

    void Simulator::drawImGui() {
        m_Store.window->onImGuiBegin();

        m_Store.navBar->draw();

        m_Store.window->onImGuiEnd();
    }

    void Simulator::setupPanels() {
        m_Store.navBar = createUP<NavBar>(m_Store);

    }

}
