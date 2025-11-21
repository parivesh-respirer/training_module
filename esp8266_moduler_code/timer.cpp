#include "timer.h"
#include "Arduino.h"



struct Task {
  int id;
  uint32_t time_interval;
  uint32_t current_time;
  Task_function func;
  bool active;
};

Task tasks[max_tasks];

void init_tasks(void) {
  for (int i = 0; i < max_tasks; i++) {
    tasks[i].active = false;
    tasks[i].current_time = 0;
    tasks[i].time_interval = 0;
    tasks[i].func = NULL;
  }
}


int Register_task(Task_function f, uint32_t time_interval) {

  for (int i = 0; i < max_tasks; i++) {
    if (tasks[i].active != true && tasks[i].func == NULL) {
      tasks[i].id = i;
      tasks[i].time_interval = time_interval;
      tasks[i].current_time = millis();
      tasks[i].func = f;
      tasks[i].active = true;
      return i;
    }

  }
      return -1;
}

void remove_task(int task_id){
  tasks[task_id].active = false;
  tasks[task_id].current_time = 0;
  tasks[task_id].time_interval = 0;
  tasks[task_id].func = NULL;
}


void Run_tasks() {
  uint32_t now = millis();
  for (int i = 0; i < max_tasks; ++i) {
    if (tasks[i].active && tasks[i].func != NULL && tasks[i].time_interval > 0) {
      if ((uint32_t)(now - tasks[i].current_time) >= tasks[i].time_interval) {
        tasks[i].current_time = now;
        tasks[i].func();
      }
    }
  }
}
