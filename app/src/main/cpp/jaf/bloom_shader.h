#pragma once

#include "../jawe/shader.h"
#include "../jawe/mesh.h"
#include "vertex.h"
#include "../jawe/framebuffer.h"
#include "../jawe/swap_chain.h"

namespace JAF {

	class BloomShader : public JAWE::Shader
	{
	private:

		typedef JAWE::Mesh<TexturedVertex> Mesh;
		typedef JAWE::SwapChain SwapChain;

		struct Pass
		{
			GLuint program;
			GLuint vao;
			GLint textureLocation0;
			GLint textureLocation1;
		};

		Pass m_thresholdPass;

		Pass m_horizontalBlurPass;

		Pass m_verticalBlurPass;

		Pass m_finalPass;

		SwapChain m_swapChain;

		static Pass setupPass(GLuint vs, GLuint ps, const char* texture0, const char* texture1, const Mesh& mesh);
		static void preparePass(const Pass& pass, const SwapChain* pTexture0, const SwapChain* pTexture1 = nullptr);

	public:

		BloomShader()
		{}

		bool init(AAssetManager *pAssetManager, const Mesh& mesh);

		virtual void release() override {

			glDeleteProgram(m_thresholdPass.program);
			glDeleteProgram(m_horizontalBlurPass.program);
			glDeleteProgram(m_verticalBlurPass.program);
			glDeleteProgram(m_finalPass.program);

			GLuint handles[] = {m_thresholdPass.vao,
								m_horizontalBlurPass.vao,
								m_verticalBlurPass.vao,
								m_finalPass.vao};
			glDeleteVertexArrays(4, handles);

			m_swapChain.release();
		}

		void render(const Mesh& mesh, const JAWE::SwapChain& framebuffer);

		void updateSize(GLsizei width, GLsizei height)
		{
			GLsizei w = static_cast<GLsizei>( static_cast<float>(width) * 0.15f);
			GLsizei h = static_cast<GLsizei>( static_cast<float>(height) * 0.15f);
			m_swapChain.init(2, w,h, true, JAWE::Framebuffer::NONE);
		}
	};
};
