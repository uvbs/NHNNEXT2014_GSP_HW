#include "stdafx.h"
#include "Log.h"

#include <iostream>

void ThreadCallHistory::DumpOut(std::ostream& ost)
{
	//todo: 현재 스레드의 call history를 ost 스트림에 쓰기
	uint64_t count = mCounter < MAX_HISTORY ? mCounter : MAX_HISTORY;

	ost << "===== Recent Call History [Thread:" << mThreadId << "]" << std::endl;

	for( int i = 1; i <= count; ++i )
	{
		ost << "  FUNC:" << mHistory[(mCounter - i) & (MAX_HISTORY - 1)] << std::endl;
	}
	ost << "===== End of Recent Call History" << std::endl << std::endl;
}
	

void ThreadCallElapsedRecord::DumpOut(std::ostream& ost)
{
	uint64_t count = mCounter < MAX_ELAPSED_RECORD ? mCounter : MAX_ELAPSED_RECORD;

	ost << "===== Recent Call Performance [Thread:" << mThreadId << "]" << std::endl;

	for (int i = 1; i <= count; ++i)
	{
		ost << "  FUNC:" << mElapsedFuncSig[(mCounter - i) & (MAX_ELAPSED_RECORD - 1)] 
			<< "  ELAPSED: " << mElapsedTime[(mCounter - i) & (MAX_ELAPSED_RECORD - 1)] << std::endl;
	}
	ost << "===== End of Recent Call Performance" << std::endl << std::endl;

}


namespace LoggerUtil
{
	LogEvent gLogEvents[MAX_LOG_SIZE];
	__int64 gCurrentLogIndex = 0;

	void EventLogDumpOut(std::ostream& ost)
	{
		//todo: gLogEvents내용 ost 스트림에 쓰기
		uint64_t count = gCurrentLogIndex < MAX_LOG_SIZE ? gCurrentLogIndex : MAX_LOG_SIZE;

		ost << "===== Recent Events" << std::endl;

		for( int i = 1; i <= count; ++i )
		{
			ost << "  ThreadId:" << gLogEvents[(gCurrentLogIndex - i) & (MAX_LOG_SIZE - 1)].mThreadId
				<< "  AdditionalInfo:" << gLogEvents[(gCurrentLogIndex - i) & (MAX_LOG_SIZE - 1)].mAdditionalInfo
				<< "  Message:" << gLogEvents[(gCurrentLogIndex - i) & (MAX_LOG_SIZE - 1)].mMessage << std::endl;
		}
		ost << "===== End of Recent Events" << std::endl << std::endl;
		
	}
}
