//
// Created by smsqo on 2022/4/20.
//

#include <malloc.h>
#include "core.h"
#include <cassert>

// core.cpp : 定义 DLL 应用程序的导出函数。
//

/**
	对象( Object ) 存储结构
		4 字节引用计数
		4 字节类型信息引用
		对象数据

	返回时指针指向对象数据，可以直接操作。
*/
void *createObject(uint64_t size, uint32_t typeId) {
    assert(sizeof(long) == 4);
    return malloc(size);
    //long* p = (long*)malloc(size + 8);
    //*p++ = 1;		// 引用计数
    //*p++ = typeId;
    //return p;
}

void freeObject(void *object) {
    assert(sizeof(long) == 4);

    //long* p = (long*)object;
    //p -= 2;
    //long v = InterlockedDecrement((long*)p);

    //if (v == 0)
    free(object);
}

const uint32_t arrayMark = 1 << 31;

void *createArray(uint32_t objectSize, uint32_t typeId, uint32_t length) {
    return createObject(objectSize * length, arrayMark | typeId);
}

long referenceIncrease(void *object) {
    assert(sizeof(long) == 4);
    long *p = (long *) object;
    p -= 2;
    // 这里去掉了一个原子加(InterlockedDecrement((long *)p)).
}
