/********************************************************************************************************************/
/*  Scheduler.h                                                                                                     */
/*                                                                                                                  */
/*  Modul "Steuergeraete/Software/Vernetzung - Embedded Systems II"                                                 */
/*  Uebung 2-02: Demonstration of a simple non-preemptive scheduler                                                 */
/*                                                                                                                  */
/*  Hochschule Mittweida, INW                                                                                       */
/*  Prof. J. Thomanek                                                                                               */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef __SCHED_H__
#define __SCHED_H__

/*********************************************************************************************************************/
/*-----------------------------------------------------Constants-----------------------------------------------------*/
/*********************************************************************************************************************/

#define MAX_NUM_OF_TASKS  10  // maximum number of tasks handled by the scheduler
#define MAX_IDLE_TIME     20  // Maximum duration of idle tasks

/*********************************************************************************************************************/
/*-----------------------------------------------------Type Definitions----------------------------------------------*/
/*********************************************************************************************************************/

// Task types
typedef enum {
    TASKTYPE_NOP,      // No operation - empty
    TASKTYPE_IDLE,     // Idle tasks - run if there are no active scheduled tasks
    TASKTYPE_ONCE,     // Runs only one at specified time offset after registration
    TASKTYPE_CYCLIC    // Runs every specified time interval
}TaskType_t;

// Function pointer of tasks
typedef void (*Task_fp)(void *);

// Task structure
typedef struct {
    Task_fp       pfTask;     // the task function pointer
    void*         pTaskArg;   // task arguments
    unsigned long u32Time;    //
    unsigned long u32ActTime; // Next activation time
    TaskType_t    eTaskType;  // Task Type
}Task_t ;


/*********************************************************************************************************************/
/*-----------------------------------------------------Functions Prototypes------------------------------------------*/
/*********************************************************************************************************************/

// Scheduler Initialisation
void SchedInit(void);

// Scheduler process
void SchedRun(void);

// Register an new task
int AddTask(TaskType_t    type,
            Task_fp       pfTask,
            unsigned long u32Time);

// Cancel an existing task
void KillTask(int taskHandle);

#endif
