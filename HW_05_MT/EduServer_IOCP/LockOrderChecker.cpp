#include "stdafx.h"
#include "Exception.h"
#include "ThreadLocal.h"
#include "FastSpinlock.h"
#include "LockOrderChecker.h"

LockOrderChecker::LockOrderChecker(int tid) : mWorkerThreadId(tid), mStackTopPos(0)
{
	memset(mLockStack, 0, sizeof(mLockStack));
}

void LockOrderChecker::Push(FastSpinlock* lock)
{
	CRASH_ASSERT(mStackTopPos < MAX_LOCK_DEPTH);

	if (mStackTopPos > 0)
	{
		/// ���� ���� �ɷ� �ִ� ���¿� �����Ѱ��� �ݵ�� ���� ���� �켱������ ���ƾ� �Ѵ�.
		//TODO: �׷��� ���� ��� CRASH_ASSERT gogo
		CRASH_ASSERT( mLockStack[mStackTopPos-1]->mLockOrder < lock->mLockOrder );
	}

	mLockStack[mStackTopPos++] = lock;
}

void LockOrderChecker::Pop(FastSpinlock* lock)
{

	/// �ּ��� ���� ���� �ִ� ���¿��� �� ���̰�
	CRASH_ASSERT(mStackTopPos > 0);
	
	//TODO: �翬�� �ֱٿ� push�ߴ� �༮�̶� ������ üũ.. Ʋ���� CRASH_ASSERT
	CRASH_ASSERT( lock == mLockStack[mStackTopPos - 1] );

	mLockStack[--mStackTopPos] = nullptr;

}