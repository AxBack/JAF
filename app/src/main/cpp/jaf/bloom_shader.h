#pragma once

#include "../jawe/shader.h"
#include "../jawe/mesh.h"
#include "vertex.h"
#include "../jawe/framebuffer.h"

namespace JAF {

	class BloomShader : public JAWE::Shader
	{
	private:

		typedef JAWE::Mesh<TexturedVertex> Mesh;
		typedef JAWE::Framebuffer Framebuffer;

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

		Framebuffer m_framebuffer1;
		Framebuffer m_framebuffer2;

		static Pass setupPass(GLuint vs, GLuint ps, const char* texture0, const char* texture1, const Mesh& mesh);
		static void preparePass(const Pass& pass, const Framebuffer* pFramebuffer0, UINT index0, const Framebuffer* pFramebuffer1 = nullptr, UINT index1 = 0);

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

			m_framebuffer2.release();
			m_framebuffer1.release();
		}

		void render(const Mesh& mesh, const Framebuffer& framebuffer, UINT index);

		void updateSize(GLsizei width, GLsizei height)
		{
			GLsizei w = static_cast<GLsizei>( static_cast<float>(width) * 0.15f);
			GLsizei h = static_cast<GLsizei>( static_cast<float>(height) * 0.15f);
			m_framebuffer1.init(w, h, true, Framebuffer::NONE);
			m_framebuffer2.init(w, h, true, Framebuffer::NONE);
		}
	};
};
