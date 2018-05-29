#pragma once

#include "framebuffer.h"

#include <exception>
#include <deque>

namespace JAWE { namespace GFX {

	class SwapChain
	{
	private:

		typedef std::shared_ptr<Framebuffer> framebuffer_ptr;

		std::deque<framebuffer_ptr> m_buffers;

	public:

		void init(UINT nrBuffers, int w, int h, bool alpha, Framebuffer::DepthType depthType)
		{
			release();
			if(nrBuffers < 2)
				throw std::runtime_error("Too few buffers");

			for(UINT i=0; i<nrBuffers; ++i)
			{
				framebuffer_ptr p(new Framebuffer);
				p->init(w, h, alpha, depthType);
				m_buffers.push_back(p);
			}
		}

		int getWidth() const { return m_buffers.front()->getWidth(); }
		int getHeight() const { return m_buffers.front()->getHeight(); }

		void release()
		{
			while(m_buffers.size() > 0)
			{
				framebuffer_ptr p = m_buffers.front();
				p->release();
				m_buffers.pop_front();
			}
		}

		void step()
		{
			m_buffers.push_back(m_buffers.front());
			m_buffers.pop_front();
		}

		void set() const
		{
			m_buffers.front()->set();
		}

		void bind() const
		{
			m_buffers.back()->bind(0);
		}

		void bind(size_t offset) const
		{
			(*(m_buffers.rbegin() + offset))->bind(0);
		}

		void clear() const
		{
			m_buffers.front()->clear();
		}

	};
} }