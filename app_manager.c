#include "app_manager.h"
#include "event.h"
#include "ui_main.h"
#include "ui_calculator.h"
#include "ui_exit.h"

void APP_MANAGER_Launch(void) {
    bool WindowShouldClose = false;

    while (!WindowShouldClose) {
        if (EVENT_MANAGER_GetSignal_MainWindow()) {
            CUI_MAIN_WINDOW_Launch();
        }

        if (EVENT_MANAGER_GetSignal_StandardCalculationWindow()) {
            CUI_STANDARD_CALCULATION_WINDOW_Launch();
        }
        
        if (EVENT_MANAGER_GetSignal_Exit()) {
            CUI_EXIT_WINDOW_Launch();
            if(get_status_exit())
            {
              WindowShouldClose = true;
            }
        }
    }
}

