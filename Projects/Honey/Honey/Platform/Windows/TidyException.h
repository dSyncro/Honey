#pragma once

#include <exception>
#include <string>

namespace Honey {

	class TidyException : std::exception {

	public:

		TidyException(std::size_t line, const char* filename) noexcept : _line(line), _filename(filename) {}
		virtual const char* what() const noexcept override;
		virtual const char* GetType() const noexcept { return "Tidy Exception"; }
		std::size_t GetLine() const noexcept { return _line; }
		const std::string& GetFilename() const noexcept { return _filename; }
		std::string GetOriginString() const noexcept;

	private:

		std::size_t _line;
		std::string _filename;

	protected:

		mutable std::string _whatBuffer;
	};

}
