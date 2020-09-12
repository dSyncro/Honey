#include "OpenGLShader.h"

#include <Honey/Core.h>

#include <fstream>
#include <vector>

extern "C" {
#include <glad/glad.h>
}

#include <glm/gtc/type_ptr.hpp>

using namespace Honey;
using namespace Honey::Math;

uint32_t OpenGLShader::s_Bound = 0;

static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;

	HNY_CORE_ASSERT(false, "Unknown shader type!");
	return 0;
}

std::string OpenGLShader::ReadFile(const std::string& path)
{
	HNY_PROFILE_FUNCTION();

	std::string result;
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (file)
	{
		file.seekg(0, std::ios::end);
		std::streampos size = file.tellg();
		if (size != -1)
		{
			result.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(&result[0], size);
			file.close();
		}
		else HNY_CORE_ERROR("Could not read from file '{0}'", path);
	}
	else HNY_CORE_ERROR("Could not open file '{0}'", path);

	return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::Process(const std::string& source)
{
	HNY_PROFILE_FUNCTION();

	std::unordered_map<GLenum, std::string> shaderSources;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
		HNY_CORE_ASSERT(eol != std::string::npos, "Syntax error");

		size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
		std::string type = source.substr(begin, eol - begin);
		HNY_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

		size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
		HNY_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
		pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

		shaderSources[ShaderTypeFromString(type)] = 
			(pos == std::string::npos) ? 
			source.substr(nextLinePos) : 
			source.substr(nextLinePos, pos - nextLinePos);
	}

	return shaderSources;
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	HNY_PROFILE_FUNCTION();

	GLuint program = glCreateProgram();

	HNY_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
	std::array<GLenum, 2> glShaderIDs;

	int glShaderIDIndex = 0;
	for (const std::pair<const GLenum, std::string>& kv : shaderSources)
	{
		GLenum type = kv.first;
		const std::string& source = kv.second;

		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			HNY_CORE_ERROR("{0}", infoLog.data());
			HNY_CORE_ASSERT(false, "Shader compilation failure!");
			break;
		}

		glAttachShader(program, shader);
		glShaderIDs[glShaderIDIndex++] = shader;
	}

	_rendererID = program;

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);

		for (auto id : glShaderIDs)
			glDeleteShader(id);

		HNY_CORE_ERROR("{0}", infoLog.data());
		HNY_CORE_ASSERT(false, "Shader link failure!");
		return;
	}

	for (unsigned int id : glShaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}
}

Reference<OpenGLShader> OpenGLShader::FromFile(const std::string& path)
{
	HNY_PROFILE_FUNCTION();

	std::string source = ReadFile(path);
	std::unordered_map<GLenum, std::string> shaderSources = Process(source);

	std::size_t lastSlash = path.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	std::size_t lastDot = path.rfind('.');

	std::size_t length = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
	std::string name = path.substr(lastSlash, length);

	return CreateReference<OpenGLShader>(name, shaderSources);
}

Reference<OpenGLShader> OpenGLShader::FromSource(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
{
	HNY_PROFILE_FUNCTION();

	std::unordered_map<GLenum, std::string> shaderSources = {
		{ GL_VERTEX_SHADER, vertexSource },
		{ GL_FRAGMENT_SHADER, fragmentSource },
	};

	return CreateReference<OpenGLShader>(name, shaderSources);
}

OpenGLShader::OpenGLShader(const std::string& name, const std::unordered_map<GLenum, std::string>& shaders)
	: _name(name)
{
	HNY_PROFILE_FUNCTION();

	Compile(shaders);
}

OpenGLShader::~OpenGLShader()
{
	HNY_PROFILE_FUNCTION();

	glDeleteProgram(_rendererID);
}

void OpenGLShader::Bind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound == _rendererID) return;

	glUseProgram(_rendererID);
	s_Bound = _rendererID;
}

void OpenGLShader::Unbind() const
{
	HNY_PROFILE_FUNCTION();

	if (s_Bound != _rendererID) return;

	glUseProgram(0);
	s_Bound = 0;
}

bool OpenGLShader::IsBound() const
{
	return s_Bound == _rendererID;
}

void OpenGLShader::SetInt(const std::string& name, int value)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniform1i(id, value);
}

void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniform1iv(id, count, values);
}

void OpenGLShader::SetFloat(const std::string& name, float value)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniform1f(id, value);
}

void OpenGLShader::SetVec2(const std::string& name, const glm::vec2& value)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniform2f(id, value.x, value.y);
}

void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniform3f(id, value.x, value.y, value.z);
}

void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniform4f(id, value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat2(const std::string& name, const glm::mat2& matrix)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniformMatrix2fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::SetMat4(const std::string& name, const Matrix4x4& matrix)
{
	this->Bind();

	int id = glGetUniformLocation(_rendererID, name.c_str());
	glUniformMatrix4fv(id, 1, GL_TRUE, &matrix.Elements[0]);
}
