#include <iostream>
using namespace std;
class Log
{
public: 
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;



private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level)
	{
		m_LogLevel = level;
	}

	void Warn(const char* message)
	{
		if (m_LogLevel >= LogLevelWarning) {
			cout << "[WARNING]" << message << endl;
		}
	}

	void Error(const char* message)
	{
		if (m_LogLevel >= LogLevelError) {
			cout << "[ERROR]" << message << endl;
		}
	}

	void Info(const char* message)
	{
		if (m_LogLevel >= LogLevelInfo) {
			cout << "[INFO]" << message << endl;
		}
	}
};

int main()
{
	Log log; 
	log.SetLevel(log.LogLevelWarning);
	log.Warn("Hello!");
	cin.get();

}