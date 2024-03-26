// Copyright 2019 NavInfo Co., Ltd. All rights reserved. Internal use only.

#pragma once

#include "cq_stdlib.h"
#include "nc_object.h"
#include "mapdal_public_stdlib.h"

// dummy functions to help auto-completion of NC_ATTRIBUTES() and NC_PROPERTY();
static forceinline void nonatomic() {}
static forceinline void atomic() {}
static forceinline void autorelease() {}

#ifdef __cplusplus

#if defined(MAPBAR_USE_MEMORY_DEBUGGER)
#	define NcNew(T, ...) ((T*)_MemoryDebugger_addRecord(new T(__VA_ARGS__), sizeof(T), __FILE__, __LINE__, __FUNCTION__, FALSE))
#	define NcNewArray(T, n) (T*)_MemoryDebugger_addRecord(new T[n], sizeof(T) * n, __FILE__, __LINE__, __FUNCTION__, TRUE);
#	define NcDelete(o) {_MemoryDebugger_removeRecord(o, FALSE); delete o; }
#	define NcDeleteArray(o) {_MemoryDebugger_removeRecord(o, TRUE); delete[] o; }
#else
#	define NcNew(T, ...) (new T(__VA_ARGS__))
#	define NcDelete(o) delete o
#	define NcNewArray(T, n) new T[n]
#	define NcDeleteArray(o) delete[] o
#endif

class NcObjectCpp;
class NcString;

template <typename T>
forceinline T* retain(T* o)
{
	if (o == NULL)
		return NULL;
	else if (o->_refCounter != INFINITE_REF_COUNT)
	{
		cq_spinLock(&o->_ncSpinlock);
		o->_refCounter++;
		cq_spinUnlock(&o->_ncSpinlock);
	}
	return (T*)o;
}

int release(NcObject* o);

template <typename T>
forceinline T* autorelease(T* o) {
	_NcAutoreleasePool_addObject(o);
	release(o);
	return o;
}

//////////////////////////////////////////////////////////////////////////
// NcObjectCpp
//     In C++, one can use it instead of NcObject

/**
	@brief
		The base class of Reference Counting classes.

	@remarks
		It supports RC and is multi-thread safe.

		RC objects can only be created on the heap. 
		So all derived classes should make the constructors protected
		and provide alloc() functions. For example:

		class MyMap : NcObjectCpp
		{
		protected:
			MyMap() {}

		public:
			forceinline static MyMap* alloc() {
				return NcNew(MyMap);
			}
			static MyMap* allocWithFile(const cqWCHAR* file);

		NcNew must be used instead of new.

	@note
		Operator new of NcObjectCpp use calloc() to allocate the requested memory,
		so there's no need to initialize fields to zeros in constructor of NcObjectCpp subclasses.

*/
class NcObjectCpp : public NcObject
{
public:
	static forceinline NcObjectCpp* alloc() {
		return NcNew(NcObjectCpp);
	}

	static forceinline NcObjectCpp* object() {
		return autorelease(alloc());
	}

	virtual bool equals(NcObjectCpp* r) {
		return this == r;
	}

	virtual uint32 hash();
	virtual NcString* toString();	// default to "Object(0xXXXXXXXX)"

	template<typename T> 
	bool isKindOf() { T* p = dynamic_cast<T*>(this); return p != NULL; }

	void* operator new(size_t size);
	void operator delete(void* p);

private:
	static NcObjectVt s_vt;

protected:
	forceinline NcObjectCpp() {
		_vt = &s_vt;
		_refCounter = 1;
		_classId = NcObjectCpp_classId;
	}
	forceinline NcObjectCpp(BOOL) {
		_refCounter = INFINITE_REF_COUNT;
		_classId = NcObjectCpp_classId;
	}
	virtual ~NcObjectCpp() { if (_refCounter != INFINITE_REF_COUNT && _ncMutex != invalidHandle) Mapbar_destroyMutex(_ncMutex); }

private:
	static void _destructAndFree(NcObject* o);
};

/**
	@brief used to convert an derived object to NcObject
	@remarks
		example:
			
		@code
		class CanWalk : public NcObjectProtocol
		{
		public:
			virtual void walk() = 0;
		};

		class CanBark : public NcObjectProtocol
		{
		public:
			virtual void bark() = 0;
		};

		class Dog : public NcObjectCpp, public CanWalk, public CanBark
		{
		public:
			static Dog* instance() { return autorelease(NcNew(Dog)); }

			virtual NcObjectCpp* toNcObject() { return this; }
			virtual void walk() { printf("walk\n"); }
			virtual void bark() { printf("bark\n"); }
		};

		TEST_F(NcObjectCppTest, protocol)
		{
			CanWalk* walker = Dog::instance();
			NcArray<NcObjectCpp>* walkers = NcArray<NcObjectCpp>::instance();
			walkers->addObject(walker->toNcObject());
		}
		@endcode
*/
class NcObjectProtocol
{
public:
	virtual NcObjectCpp* toNcObject() = 0;	// convert a derived object to NcObject
};

class SynchronizeLock
{ 
public: 	
	forceinline SynchronizeLock(NcObject* obj)
	{ 
		m_runTimes = 0;
		NcObject_lock(obj);
		m_obj = obj;
	}
	forceinline ~SynchronizeLock()
	{ 
		NcObject_unlock(m_obj);
	} 	
	forceinline bool run()
	{ 
		return m_runTimes++ == 0; 
	} 	
private: 	
	NcObject* m_obj;
	int m_runTimes; 
}; 

#define synchronized(o) for (SynchronizeLock lockVariable_blarblar(o); lockVariable_blarblar.run();)

class SpinlockAuto
{
public:
	forceinline SpinlockAuto()
	{
		m_lock = NULL;
	}
	forceinline ~SpinlockAuto()
	{
		cq_spinUnlock(m_lock);
	}

	forceinline bool run(NcObject* obj)
	{
		if (m_lock == NULL)
		{
			m_lock = &obj->_ncSpinlock;
			cq_spinLock(m_lock);
			return true;
		}

		return false;
	}
	
	forceinline bool run(volatile long* lock)
	{
		if (m_lock == NULL)
		{
			m_lock = lock;
			cq_spinLock(m_lock);
			return true;
		}

		return false;
	}
private:
	volatile long* m_lock;
};

#define spinlock(o) for (SpinlockAuto lockVariable_blarblar; lockVariable_blarblar.run(o);)

//////////////////////////////////////////////////////////////////////////

/**
	This class is used to help creating thread-specific singleton objects.

	@remarks

		Example code:

		@code
			// MyObject.cpp
			class MyObjectSingletonAllocator : ThreadSingletonAllocator
			{
			private:
				virtual NcObjectCpp* allocThreadObject() {
					return MyObject::alloc();
				}
			};

			static TestThreadSingletonAllocator g_allocator;

			MyObject* MyObject::threadInstance()
			{
				return (MyObject*)g_allocator.threadInstance();
			}

		@endcode

*/
class ThreadSingletonAllocator
{
public:
	ThreadSingletonAllocator();

	/**
		Get or create a thread-specific object.

		@remarks
			If an object is already created for the current thread, it will be returned.
			If not, allocThreadObject() will be called to create one.

			All thread-specific objects will be automatically freed when the thread exits.
			Objects will be freed in the reverse order of creation.
	*/
	NcObjectCpp* threadInstance();

	/**
		threadInstance() will call this function to create a thread specific object if needed.

		@remarks
			The user must implement this functions
	*/
	virtual NcObjectCpp* allocThreadObject() = 0;

	/**
		Free all registered singleton objects in current thread.

		@remarks
			It must be called in the adaption layer before a thread exits.
	*/
	static void freeAllSingletonsInCurrentThread();

private:
	void addThreadObject(void* object, ObjectCleanupStackFunc func);

	Handle m_tls;
	volatile long m_spinlock;
};

//////////////////////////////////////////////////////////////////////////

class NcGuid
{
public:
	// 8-4-4-4-12 format: for example: 123e4567-e89b-12d3-a456-426655440000
	bool initWithText(const char* text);
	bool initWithText(const cqWCHAR* text);
	bool initWithText(NcString* text);

	/**
		@brief 将 GUID 转成十六进制数字形式的字符串表示
		@warning
			注意text数组的大小，小于38字节会引发崩溃。
	*/
	void toText(char text[38]) const; // for example: "123e4567-e89b-12d3-a456-426655440000"
	/**
		@brief 将 GUID 转成十六进制数字形式的字符串表示
		@warning
			注意text数组的大小，小于33字节会引发崩溃。
	*/
	void toCompactText(char text[33]) const;	// without "-", for example "123e4567e89b12d3a456426655440000"

	forceinline bool equals(NcGuid r) {
		return memcmp(m_bytes, r.m_bytes, 16) == 0;
	}

	NC_PROPERTY(bytes);
	const uint8* bytes() {
		return m_bytes;
	}// 16 bytes

private:
	uint8 m_bytes[16];
};

forceinline NcGuid NcGuid_make(const char* text) {
	NcGuid o;
	o.initWithText(text);
	return o;
}

forceinline NcGuid NcGuid_make(const cqWCHAR* text) {
	NcGuid o;
	o.initWithText(text);
	return o;
}

forceinline NcGuid NcGuid_make(NcString* text) {
	NcGuid o;
	o.initWithText(text);
	return o;
}

forceinline bool operator == (NcGuid l, NcGuid r) {
	return l.equals(r);
}

forceinline bool operator != (NcGuid l, NcGuid r) {
	return !l.equals(r);
}

NcGuid NcGuid_makeSample();	// "12345678-1234-1234-1234-123456789012"
NcGuid NcGuid_makeEmpty();	// "00000000-0000-0000-0000-000000000000"

//////////////////////////////////////////////////////////////////////////
enum NcNumberType
{
	NcNumberType_int,
	NcNumberType_int64,
	NcNumberType_float,
	NcNumberType_double,
	NcNumberType_point,
	NcNumberType_rect,
	NcNumberType_pointF,
	NcNumberType_rectF,
	NcNumberType_bool
};

class NcNumber : public NcObjectCpp
{
public:
	forceinline static NcNumber* allocWithBool(bool n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_bool; o->m_bool = n; return o; }
	forceinline static NcNumber* allocWithInt(int n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_int; o->m_int = n; return o; }
	forceinline static NcNumber* allocWithInt64(int64 n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_int64; o->m_int64 = n; return o; }
	forceinline static NcNumber* allocWithFloat(float n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_float; o->m_float = n; return o; }
	forceinline static NcNumber* allocWithDouble(double n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_double; o->m_double = n; return o; }
	forceinline static NcNumber* allocWithPoint(Point n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_point; o->m_point = n; return o; }
	forceinline static NcNumber* allocWithRect(Rect n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_rect; o->m_rect = n; return o; }
	forceinline static NcNumber* allocWithPointF(PointF n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_pointF; o->m_pointF = n; return o; }
	forceinline static NcNumber* allocWithRectF(RectF n) { NcNumber* o = NcNew(NcNumber); o->m_type = NcNumberType_rectF; o->m_rectF = n; return o; }

	forceinline static NcNumber* instanceWithBool(bool n) { return autorelease(allocWithBool(n)); }
	forceinline static NcNumber* instanceWithInt(int n) { return autorelease(allocWithInt(n)); }
	forceinline static NcNumber* instanceWithInt64(int64 n) { return autorelease(allocWithInt64(n)); }
	forceinline static NcNumber* instanceWithFloat(float n) { return autorelease(allocWithFloat(n)); }
	forceinline static NcNumber* instanceWithDouble(double n) { return autorelease(allocWithDouble(n)); }
	forceinline static NcNumber* instanceWithPoint(Point n) { return autorelease(allocWithPoint(n)); }
	forceinline static NcNumber* instanceWithRect(Rect n) { return autorelease(allocWithRect(n)); }
	forceinline static NcNumber* instanceWithPointF(PointF n) { return autorelease(allocWithPointF(n)); }
	forceinline static NcNumber* instanceWithRectF(RectF n) { return autorelease(allocWithRectF(n)); }

	NC_PROPERTY(type);
	forceinline NcNumberType type() { return m_type; }

	forceinline bool boolValue() {
		return m_bool;
	}

	forceinline int intValue() {
		return m_int;
	}

	forceinline int64 int64Value() {
		return m_int64;
	}

	forceinline float floatValue() {
		return m_float;
	}

	forceinline double doubleValue() {
		return m_double;
	}

	forceinline Point point() {
		return m_point;
	}

	forceinline Rect rect() {
		return m_rect;
	}

	forceinline PointF pointF() {
		return m_pointF;
	}

	forceinline RectF rectF() {
		return m_rectF;
	}

	virtual bool equals(NcObjectCpp* r_);
	virtual uint32 hash();
	virtual NcString* toString();

protected:
	forceinline NcNumber() {}
	~NcNumber() {}
private:
	NcNumberType m_type;
	union
	{
		bool m_bool;
		int m_int;
		int64 m_int64;
		float m_float;
		double m_double;
		Rect m_rect;
		Point m_point;
		RectF m_rectF;
		PointF m_pointF;
	};
};

class __NcNumberWrapper__
{
public:
	forceinline __NcNumberWrapper__(int i)
	{
		m_num = NcNumber::allocWithInt(i);
	}
	forceinline __NcNumberWrapper__(int64 i)
	{
		m_num = NcNumber::allocWithInt64(i);
	}
	forceinline __NcNumberWrapper__(float i)
	{
		m_num = NcNumber::allocWithFloat(i);
	}
	forceinline __NcNumberWrapper__(double i)
	{
		m_num = NcNumber::allocWithDouble(i);
	}
	forceinline ~__NcNumberWrapper__()
	{
		release(m_num);
	}
	forceinline operator NcNumber* ()
	{
		return m_num;
	}

private:
	NcNumber* m_num;
};

#define ncbox(a) __NcNumberWrapper__(a)

class ZeroedObject
{
public:
	void* operator new(size_t size);
	void operator delete(void* p);
};

#endif
