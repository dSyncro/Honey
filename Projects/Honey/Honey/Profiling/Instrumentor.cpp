#include "Instrumentor.h"

using namespace Honey;

void Instrumentor::beginSession(const std::string& name, const std::string& filepath)
{
	std::lock_guard lock = std::lock_guard(_mutex);

	if (_currentSession)
	{
		// If there is already a current session, then close it before beginning new one.
		// Subsequent profiling output meant for the original session will end up in the
		// newly opened session instead.  That's better than having badly formatted
		// profiling output.
		if (Log::getCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
			HNY_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, _currentSession->Name);

		internalEndSession();
	}

	_outputStream.open(filepath);

	if (_outputStream.is_open())
	{
		_currentSession = new InstrumentationSession({ name });
		writeHeader();
	}
	else if (Log::getCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
		HNY_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
}

void Instrumentor::endSession()
{
	std::lock_guard lock(_mutex);
	internalEndSession();
}

void Instrumentor::writeProfile(const ProfileResult& result)
{
	std::stringstream json;

	json << std::setprecision(3) << std::fixed;
	json << ",{";
	json << "\"cat\":\"function\",";
	json << "\"dur\":" << (result.elapsedTime.count()) << ',';
	json << "\"name\":\"" << result.name << "\",";
	json << "\"ph\":\"X\",";
	json << "\"pid\":0,";
	json << "\"tid\":" << result.threadID << ",";
	json << "\"ts\":" << result.start.count();
	json << "}";

	std::lock_guard lock(_mutex);
	if (_currentSession)
	{
		_outputStream << json.str();
		_outputStream.flush();
	}
}

void Instrumentor::writeHeader()
{
	_outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
	_outputStream.flush();
}

void Instrumentor::writeFooter()
{
	_outputStream << "]}";
	_outputStream.flush();
}

void Instrumentor::internalEndSession()
{
	if (!_currentSession) return;

	writeFooter();
	_outputStream.close();
	delete _currentSession;
	_currentSession = nullptr;
}
