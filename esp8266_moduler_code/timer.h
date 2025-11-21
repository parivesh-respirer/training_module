#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

#define max_tasks 10

typedef void (*Task_function)();

void init_tasks(void);
int Register_task(Task_function f, uint32_t time_interval);
void Run_tasks();
#endif