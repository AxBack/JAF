#pragma once

#include "framebuffer.h"

#include <exception>

namespace JAWE {

	class SwapChain
	{
	private:

		UINT m_nrBuffers { 0 };
		UINT m_currentBuffer = { 0 };
		std::unique_ptr<Framebuffer[]> m_buffers;

		Framebuffer* m_pTarget;
		Framebuffer* m_pTexture;

	public:

		void init(UINT nrBuffers, int w, int h, bool alpha, Framebuffer::DepthType depthType)
		{
			clear();
			if(nrBuffers < 2)
				throw std::runtime_error("Too few buffers");

			m_currentBuffer = 0;
			m_nrBuffers = nrBuffers;
			m_buffers.reset(new Framebuffer[m_nrBuffers]);
			for(UINT i=0; i<nrBuffers; ++i)
			{
				m_buffers.get()[i].init(w, h, alpha, depthType);
			}

			m_pTarget = &m_buffers.get()[m_currentBuffer];
		}

		int getWidth() const { return m_pTarget->getWidth(); }
		int getHeight() const { return m_pTarget->getHeight(); }

		void release()
		{
			for(UINT i=0; i<m_nrBuffers; ++i)
				m_buffers[i].release();
			m_buffers.reset(nullptr);
			m_nrBuffers = 0;
		}

		void step()
		{
			m_pTexture = m_pTarget;
			m_pTarget = &m_buffers.get()[m_currentBuffer++ % m_nrBuffers];
		}

		void set() const
		{
			if(m_pTexture)
				m_pTexture->set();
		}

		void bind() const
		{
			if(m_pTarget)
				m_pTarget->bind(0);
		}

		void clear() const
		{
			if(m_pTarget)
				m_pTarget->clear();
		}

	};
};