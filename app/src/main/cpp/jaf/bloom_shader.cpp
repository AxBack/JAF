#include "bloom_shader.h"

namespace JAF {

#define TEXTURE0 "uTexture0"
#define TEXTURE1 "uTexture1"
#define TEXTURE2 "uTexture2"
#define TEXTURE3 "uTexture3"
#define INTENSITY "uIntensity"

	bool BloomShader::init(AAssetManager* pAssetManager, const Mesh& mesh)
	{
		GLuint vs = createShader(pAssetManager, "shaders/FullscreenShader_vs.glsl", GL_VERTEX_SHADER);

		{
			GLuint ps = createShader(pAssetManager, "shaders/ThresholdShader_ps.glsl", GL_FRAGMENT_SHADER);
			m_thresholdPass = setupPass(mesh, vs, ps, TEXTURE0, TEXTURE1, TEXTURE2, TEXTURE3);
			glDeleteShader(ps);
		}

		{
			GLuint ps = createShader(pAssetManager, "shaders/BlurHorizontal_ps.glsl", GL_FRAGMENT_SHADER);
			m_horizontalBlurPass = setupPass(mesh, vs, ps, TEXTURE0, nullptr);
			glDeleteShader(ps);
		}

		{
			GLuint ps = createShader(pAssetManager, "shaders/BlurVertical_ps.glsl", GL_FRAGMENT_SHADER);
			m_verticalBlurPass = setupPass(mesh, vs, ps, TEXTURE0, nullptr);
			glDeleteShader(ps);
		}

		{
			GLuint ps = createShader(pAssetManager, "shaders/BloomShader_ps.glsl", GL_FRAGMENT_SHADER);
			m_finalPass = setupPass(mesh, vs, ps, TEXTURE0, TEXTURE1);
			m_intensityLocation = getLocation(m_finalPass.program, INTENSITY);
			glDeleteShader(ps);
		}

		glDeleteShader(vs);
		m_counter.step();

		return true;
	}

	auto BloomShader::setupPass(const Mesh& mesh, GLuint vs, GLuint ps, const char* texture0, const char* texture1, const char* texture2, const char* texture3)->Pass
	{
		Pass pass = {0,0,-1, -1};
		pass.program = createProgram(vs, ps);
		pass.textureLocation0 = texture0 == nullptr ? -1 : getLocation(pass.program, texture0);
		pass.textureLocation1 = texture1 == nullptr ? -1 : getLocation(pass.program, texture1);
		pass.textureLocation2 = texture2 == nullptr ? -1 : getLocation(pass.program, texture2);
		pass.textureLocation3 = texture3 == nullptr ? -1 : getLocation(pass.program, texture3);

		glGenVertexArrays(1, &pass.vao);
		glBindVertexArray(pass.vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexBuffer());
		glBindBuffer(GL_ARRAY_BUFFER, mesh.getStaticBuffer());

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), _buffer_offset(3));

		glBindVertexArray(0);
		return pass;
	}

	void BloomShader::render(const Mesh& mesh, const SwapChain& swapChain, float alpha)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);

		m_swapChain.set();
		m_swapChain.clear();

		preparePass(m_thresholdPass, &swapChain, &swapChain);
		mesh.render();

		m_swapChain.step();
		m_swapChain.set();
		m_swapChain.clear();

		preparePass(m_horizontalBlurPass, &m_swapChain);
		mesh.render();

		m_swapChain.step();
		m_swapChain.set();
		m_swapChain.clear();

		preparePass(m_verticalBlurPass, &m_swapChain);
		mesh.render();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, swapChain.getWidth(), swapChain.getHeight());

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);

		m_swapChain.step();

		if(alpha > 0.0f)
		{
			preparePass(m_finalPass, &swapChain, &m_swapChain);
			glUniform1f(m_intensityLocation, alpha);
			mesh.render();
		}
	}

	void BloomShader::preparePass(const Pass& pass, const SwapChain* pTexture0, const SwapChain* pTexture1, size_t offset1)
	{
		glUseProgram(pass.program);
		glBindVertexArray(pass.vao);

		if (pass.textureLocation0 >= 0)
		{
			glActiveTexture(GL_TEXTURE0);
			pTexture0->bind();
			glUniform1i(pass.textureLocation0, 0);
		}

		if (pass.textureLocation1 >= 0)
		{
			glActiveTexture(GL_TEXTURE1);
			pTexture1->bind(offset1);
			glUniform1i(pass.textureLocation1, 1);
		}

		if (pass.textureLocation2 >= 0)
		{
			glActiveTexture(GL_TEXTURE2);
			pTexture1->bind(offset1+1);
			glUniform1i(pass.textureLocation2, 2);
		}

		if (pass.textureLocation3 >= 0)
		{
			glActiveTexture(GL_TEXTURE3);
			pTexture1->bind(offset1+2);
			glUniform1i(pass.textureLocation3, 3);
		}
	}
}