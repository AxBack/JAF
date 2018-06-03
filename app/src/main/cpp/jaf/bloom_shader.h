#pragma once

#include "../jawe/gfx/shader.h"
#include "../jawe/gfx/mesh.h"
#include "vertex.h"
#include "../jawe/gfx/framebuffer.h"
#include "../jawe/gfx/swap_chain.h"
#include "../jawe/gfx/texture.h"
#include "../jawe/range.h"
#include "../jawe/counter.h"
#include "animator.h"

namespace JAF {

	class BloomShader : public JAWE::GFX::Shader
	{
	private:

		typedef JAWE::GFX::Mesh<TexturedVertex> Mesh;
		typedef JAWE::GFX::SwapChain SwapChain;

		struct Pass
		{
			GLuint program;
			GLuint vao;
			GLint textureLocation0;
			GLint textureLocation1;
			GLint textureLocation2;
			GLint textureLocation3;
		};

		Pass m_thresholdPass;
		Pass m_horizontalBlurPass;
		Pass m_verticalBlurPass;
		Pass m_finalPass;

		SwapChain m_swapChain;

		GLint m_intensityLocation;
		JAWE::Counter m_counter;

		static Pass setupPass(const Mesh& mesh, GLuint vs, GLuint ps, const char* texture0, const char* texture1 = nullptr, const char* texture2 = nullptr, const char* texture3 = nullptr);
		static void preparePass(const Pass& pass, const SwapChain* pTexture0, const SwapChain* pTexture1 = nullptr, size_t offset1 = 0);

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

		void render(const Mesh& mesh, const JAWE::GFX::SwapChain& framebuffer, float alpha);

		void updateSize(GLsizei width, GLsizei height)
		{
			GLsizei w = static_cast<GLsizei>( static_cast<float>(width) * 0.15f);
			GLsizei h = static_cast<GLsizei>( static_cast<float>(height) * 0.15f);
			m_swapChain.init(2, w,h, true, JAWE::GFX::Framebuffer::NONE);
		}
	};
}
