#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>

#include <Honey/Core/Log.h>

#include "ProfileResult.h"

namespace Honey {

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{

	public:

		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(_mutex);

			if (_currentSession)
			{
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
					HNY_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, _currentSession->Name);

				InternalEndSession();
			}

			_outputStream.open(filepath);

			if (_outputStream.is_open())
			{
				_currentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
				HNY_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
		}

		void EndSession()
		{
			std::lock_guard lock(_mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(_mutex);
			if (_currentSession)
			{
				_outputStream << json.str();
				_outputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:

		Instrumentor() : _currentSession(nullptr) { }

		~Instrumentor()
		{
			EndSession();
		}

		void WriteHeader()
		{
			_outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			_outputStream.flush();
		}

		void WriteFooter()
		{
			_outputStream << "]}";
			_outputStream.flush();
		}

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession()
		{
			if (!_currentSession) return;

			WriteFooter();
			_outputStream.close();
			delete _currentSession;
			_currentSession = nullptr;
		}

		std::mutex _mutex;
		InstrumentationSession* _currentSession;
		std::ofstream _outputStream;

	};

}
