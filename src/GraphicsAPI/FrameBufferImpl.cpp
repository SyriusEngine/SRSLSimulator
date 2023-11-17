#include "FrameBufferImpl.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{

    FrameBufferImpl::FrameBufferImpl(const FrameBufferLayout &layout, Pipeline *pipeline):
    FrameBuffer(layout),
    m_Pipeline(pipeline){

    }

    FrameBufferImpl::~FrameBufferImpl() {

    }

    void FrameBufferImpl::bind() {
        m_Pipeline->setFrameBuffer(this);
    }
}
