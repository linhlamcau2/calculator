#include "ui_exit.h"
#include <stdio.h>
#include "event.h"

static bool exit_conf = false;
void CUI_EXIT_WINDOW_Launch(void) {
    CUI_CONFIRM_EXIT_WINDOW_LUNCH();
    if(exit_conf)
    {
    CUI_EXIT_WINDOW_DisplayMenu();
    CUI_EXIT_WINDOW_GetInputFromUser();
    CUI_EXIT_WINDOW_HandleUserInput();
    }
    else
    {
        EVENT_MANAGER_TriggerSignal_MainWindow();
    }
}

void CUI_EXIT_WINDOW_DisplayMenu(void) {
    printf("\nThoat khoi chuong trinh...");
    printf("\nHen gap lai!");
}

void CUI_EXIT_WINDOW_GetInputFromUser(void) {
    /* Do something */
}

void CUI_EXIT_WINDOW_HandleUserInput(void) {
    /* Do something */
}
void CUI_CONFIRM_EXIT_WINDOW_LUNCH(void)
{
    char op;
    int check=0;
    do
    {
    printf("\nBan chac chu[Y/N]:");
    scanf("%c", &op);
    while (getchar() != '\n');
    if(op=='y'|| op == 'Y')
    {
        exit_conf = true;
        check =1;
    }
    else if(op=='n'|| op == 'N')
    {
        exit_conf = false;
        check=1;
    }
    }while(!check);
}
bool get_status_exit()
{
    return exit_conf;
}

void set_status_exit(bool a)
{
    exit_conf=a;
}