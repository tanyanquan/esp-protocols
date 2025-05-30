/*
 * SPDX-FileCopyrightText: 2021-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "esp_heap_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

#define tskNO_AFFINITY      ( ( BaseType_t ) 0x7FFFFFFF )
#define TaskHandle_t TaskHandle_t
#define vSemaphoreDelete( xSemaphore ) vQueueDelete( ( QueueHandle_t ) ( xSemaphore ) )

typedef void *StackType_t;
typedef void *StaticTask_t;

void vTaskDelay(const TickType_t xTicksToDelay);

void xTaskNotifyGive(TaskHandle_t task);

void ulTaskNotifyTake(bool stuff, uint32_t timeout);

TaskHandle_t xTaskGetCurrentTaskHandle(void);

BaseType_t xTaskNotifyWait(uint32_t bits_entry_clear, uint32_t bits_exit_clear, uint32_t *value, TickType_t wait_time);

TaskHandle_t xTaskCreateStaticPinnedToCore(TaskFunction_t pxTaskCode,
                                           const char *const pcName,
                                           const uint32_t ulStackDepth,
                                           void *const pvParameters,
                                           UBaseType_t uxPriority,
                                           StackType_t *const puxStackBuffer,
                                           StaticTask_t *const pxTaskBuffer,
                                           const BaseType_t xCoreID);

BaseType_t xTaskCreatePinnedToCore(TaskFunction_t pvTaskCode,
                                   const char *const pcName,
                                   const uint32_t usStackDepth,
                                   void *const pvParameters,
                                   UBaseType_t uxPriority,
                                   TaskHandle_t *const pvCreatedTask,
                                   const BaseType_t xCoreID);

BaseType_t xTaskCreate(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, void *const pvParameters, UBaseType_t uxPriority, TaskHandle_t *const pvCreatedTask);

TickType_t xTaskGetTickCount(void);

void vQueueDelete(QueueHandle_t xQueue);

QueueHandle_t xSemaphoreCreateBinary(void);

QueueHandle_t xSemaphoreCreateMutex(void);
QueueHandle_t xSemaphoreCreateRecursiveMutex(void);

BaseType_t xSemaphoreGive(QueueHandle_t xQueue);

BaseType_t xSemaphoreTake(QueueHandle_t xQueue, TickType_t pvTask);

BaseType_t xSemaphoreGiveRecursive(QueueHandle_t xQueue);

BaseType_t xSemaphoreTakeRecursive(QueueHandle_t xQueue, TickType_t pvTask);

void vTaskDelete(TaskHandle_t *task);

QueueHandle_t xQueueCreate(uint32_t uxQueueLength,
                           uint32_t uxItemSize);

uint32_t xQueueSend(QueueHandle_t xQueue, const void *pvItemToQueue, TickType_t xTicksToWait);

uint32_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait);

void vTaskSuspend(void *task);

EventGroupHandle_t xEventGroupCreate(void);
void vEventGroupDelete(EventGroupHandle_t xEventGroup);
EventBits_t xEventGroupClearBits(EventGroupHandle_t xEventGroup,
                                 const EventBits_t uxBitsToClear);

EventBits_t xEventGroupWaitBits(EventGroupHandle_t xEventGroup,
                                const EventBits_t uxBitsToWaitFor,
                                const BaseType_t xClearOnExit,
                                const BaseType_t xWaitForAllBits,
                                TickType_t xTicksToWait);

EventBits_t xEventGroupGetBits(EventGroupHandle_t xEventGroup);

EventBits_t xEventGroupSetBits(EventGroupHandle_t xEventGroup,
                               const EventBits_t uxBitsToSet);

uint32_t xQueueSendToBack(QueueHandle_t xQueue, const void *pvItemToQueue, TickType_t xTicksToWait);

void *heap_caps_malloc(size_t size, uint32_t caps);
void heap_caps_free(void *ptr);

#ifdef __cplusplus
}
#endif //__cplusplus
