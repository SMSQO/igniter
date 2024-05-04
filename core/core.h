//
// Created by smsqo on 2022/4/20.
//

#ifndef IGNITER_CORE_H
#define IGNITER_CORE_H

// DO NOT USE BOM
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif
extern void *createObject(uint64_t objectSize, uint32_t typeId);
extern void freeObject(void *object);
extern long referenceIncrease(void *object);

extern void *createArray(uint32_t objectSize, uint32_t typeId, uint32_t length);
#ifdef __cplusplus
}
#endif

#endif //IGNITER_CORE_H
