// Copyright 2019 NavInfo Co., Ltd. All rights reserved. Internal use only.

#pragma once

#include "cq_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct NcObject;
typedef struct NcObject NcObject;

typedef void (*NcObject_destructFunc)(NcObject* o);
typedef BOOL(*NcObject_equalFunc)(NcObject* o, NcObject* r);

typedef struct NcObjectVt	// virtual table
{
	NcObject_destructFunc destruct;
	NcObject_equalFunc equal;
} NcObjectVt;

#define INFINITE_REF_COUNT 0x0fffff

#define NcObject_classId	0x01020304
#define NcString_classId	0x01020305
#define NcObjectCpp_classId 0x01020306
#define NcData_classId		0x01020307

struct NcObject
{
#define NcObject_members	\
	NcObjectVt* _vt;	\
	Handle _ncMutex;	\
	volatile long _ncSpinlock;	\
	uint32 _classId;	\
	uint32 _refCounter;	\
	uint32 _autoRefCounter

	NcObject_members;
};

NcObject* NcObject_alloc();
void _NcObject_construct(NcObject* o, NcObjectVt* vtable);
#define NcObject_construct(o, vt) _NcObject_construct((NcObject*)(o), vt)
void _NcObject_destruct(NcObject* o);
#define NcObject_destruct(o) _NcObject_destruct((NcObject*)(o))

#define NcObject_getRetainCount(o) ((o)->_refCounter)

NcObject* _NcObject_retain(NcObject* o);
#define NcObject_retain(o) _NcObject_retain((NcObject*)(o))
int _NcObject_release(NcObject* o);
#define NcObject_release(o) _NcObject_release((NcObject*)(o))
NcObject* NcObject_autorelease(NcObject* o);

/**
	@brief
		lock/unlock NcObject.
	@remark
		Use cq_spinLock() change "o->_refCounter",
		use Mapbar_lockMutex() to lock "o->_ncMutex".
		Mapbar_lockMutex allows the same thread to acquire the mutex object.
*/
void NcObject_lockImple(NcObject* o);
void NcObject_unlockImple(NcObject* o);
#define NcObject_lock(o) NcObject_lockImple((NcObject*)o)
#define NcObject_unlock(o) NcObject_unlockImple((NcObject*)o)

//////////////////////////////////////////////////////////////////////////

/**	@class NcAutoreleasePool
	@extends NcObject
*/
typedef struct NcAutoreleasePool NcAutoreleasePool;

NcAutoreleasePool* NcAutoreleasePool_alloc(void);
#define NcAutoreleasePool_release(o) NcObject_release(o)
#define NcAutoreleasePool_retain(o) NcObject_retain((NcObject*)o)
void NcAutoreleasePool_drain(NcAutoreleasePool* o);
void NcAutoreleasePool_addObject(NcAutoreleasePool* o, NcObject* obj);
size_t NcAutoreleasePool_size(const NcAutoreleasePool* o);

void _NcAutoreleasePool_addObject(NcObject* obj);	// add to the pool of the current thread

void NcAutoreleasePoolStack_init();
void NcAutoreleasePoolStack_cleanup();

#ifdef __cplusplus
}

extern "C++"
{
	class AutoreleasePoolForLoopObject
	{
	public:
		AutoreleasePoolForLoopObject() {
			m_pool = NULL;
		}
		~AutoreleasePoolForLoopObject()
		{
			NcAutoreleasePool_release(m_pool);
		}
		bool runOnce() {
			if (m_pool == NULL)
			{
				m_pool = NcAutoreleasePool_alloc();
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		NcAutoreleasePool* m_pool;
	};

	class AutoreleasePoolStackObject
	{
	public:
		AutoreleasePoolStackObject() {
			m_pool = NcAutoreleasePool_alloc();
		}
		~AutoreleasePoolStackObject()
		{
			NcAutoreleasePool_release(m_pool);
		}
	private:
		NcAutoreleasePool* m_pool;
	};
}

#	define autoreleasepool for (AutoreleasePoolForLoopObject apflb; apflb.runOnce();)

#endif
