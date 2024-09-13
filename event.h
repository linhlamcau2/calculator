#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>


/* Structure Declaration -----------------------------------------------------*/
// Structure to hold event signals
typedef struct {
    bool signal_main_window;                    // Signal for the main window
    bool signal_standard_calculation_window;    // Signal for the standard calculation window
    bool signal_exit_window;                           // Signal for exiting the application
} event_manager_event_t;

/* Getter and Setter Functions -----------------------------------------------*/
bool EVENT_MANAGER_GetSignal_MainWindow(void);
void EVENT_MANAGER_TriggerSignal_MainWindow(void);

bool EVENT_MANAGER_GetSignal_StandardCalculationWindow(void);
void EVENT_MANAGER_TriggerSignal_StandardCalculationWindow(void);

bool EVENT_MANAGER_GetSignal_Exit(void);
void EVENT_MANAGER_TriggerSignal_ExitWindow(void);

#endif