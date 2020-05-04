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

	private:

		std::mutex _mutex;
		InstrumentationSession* _currentSession;
		std::ofstream _outStream;

	public:

		Instrumentor() : _currentSession(nullptr) {}

		void BeginSession(const std::string& name, const std::string& path = "results.json")
		{
			std::lock_guard lock(_mutex);
			if (_currentSession)
			{
				if (Log::GetCoreLogger()) HNY_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, _currentSession->Name);
				InternalEndSession();
			}

			_outStream.open(path);
			if (_outStream.is_open())
			{
				_currentSession = new InstrumentationSession({ name });
				WriteHeader();
				return;
			}

			if (Log::GetCoreLogger()) HNY_CORE_ERROR("Instrumentor could not open results file '{0}'.", path);
		}

		void EndSession()
		{
			std::lock_guard lock(_mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(_mutex);

			if (!_currentSession) return;

			_outStream << json.str();
			_outStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:

		void WriteHeader()
		{
			_outStream << "{\"otherData\": {},\"traceEvents\":[{}";
			_outStream.flush();
		}

		void WriteFooter()
		{
			_outStream << "]}";
			_outStream.flush();
		}

		// Note: you must already own lock on _mutex before
		// calling InternalEndSession()
		void InternalEndSession()
		{
			if (!_currentSession) return;

			WriteFooter();
			_outStream.close();

			delete _currentSession;
			_currentSession = nullptr;
		}

	};

}