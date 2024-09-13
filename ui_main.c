#include"ui_main.h"
#include"event.h"
#include <stdio.h>
#include <stdbool.h>

static cui_main_window_data_t cui_main_window_data;

void CUI_MAIN_WINDOW_Data_SetMode(int mode) {
    cui_main_window_data.mode = mode;
}

int CUI_MAIN_WINDOW_Data_GetMode(void) {
    return cui_main_window_data.mode;
}

void CUI_MAIN_WINDOW_Launch(void) {
    CUI_MAIN_WINDOW_DisplayMenu();
    CUI_MAIN_WINDOW_GetInputFromUser();
    CUI_MAIN_WINDOW_HandleUserInput();
}

void CUI_MAIN_WINDOW_DisplayMenu(void) {
    printf("\n\nChao mung ban");
    printf("\n-----------------------------");
    printf("\nChon phep toan:");
    printf("\n\t1. Phep toan voi so thuc\n");
    printf("\n\t2. Phep toan voi so phuc\n");
    printf("\n\t3. Thoat");
    printf("\n");
}

int CUI_INPUT_VALIDATION_GetModeFromUser(void) {
    int mode;
    int number_of_received_input = 0;
    bool input_is_valid = true;

    do {
        input_is_valid = true;
        printf("\nSelect mode [1-3]: ");
        number_of_received_input = scanf("%d", &mode);
        while(getchar() != '\n');
        printf("Current received input: %d", mode);

        if (!((mode >= 1 && mode <= 3) && (number_of_received_input == 1))) {
            input_is_valid = false;
            printf("\n\nSorry, try again!");
        }
    } while (!input_is_valid);

    return mode;
}

void CUI_MAIN_WINDOW_GetInputFromUser(void) {
    int mode = CUI_INPUT_VALIDATION_GetModeFromUser();
    CUI_MAIN_WINDOW_Data_SetMode(mode);
}

void CUI_MAIN_WINDOW_HandleUserInput(void) {
    switch (cui_main_window_data.mode)
    {
    case 1:
        EVENT_MANAGER_TriggerSignal_StandardCalculationWindow();
        break;

    case 3:
        EVENT_MANAGER_TriggerSignal_ExitWindow();
        break;
    
    default:
        printf("\nTinh nang dang phat trien");
        EVENT_MANAGER_TriggerSignal_MainWindow();
        break;
    }
}
