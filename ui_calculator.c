
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "ui_calculator.h"
#include "event.h"

static cui_standardcalculation_window_data_t cui_standardcalculation_window_data;

typedef complex_t (*handlert_cal)(complex_t a,complex_t b);

typedef struct 
{
    math_operator_t op;
    handlert_cal handle_func;
}cmd_t;

complex_t addComplex(complex_t c1, complex_t c2) {
    complex_t result;
    result.real = c1.real + c2.real;
    result.imagine = c1.imagine + c2.imagine;
    return result;
}

// Hàm trừ hai số phức
complex_t subtractComplex(complex_t c1, complex_t c2) {
    complex_t result;
    result.real = c1.real - c2.real;
    result.imagine = c1.imagine - c2.imagine;
    return result;
}

// Hàm nhân hai số phức
complex_t multiplyComplex(complex_t c1, complex_t c2) {
    complex_t result;
    result.real = c1.real * c2.real - c1.imagine * c2.imagine;
    result.imagine = c1.real * c2.imagine + c1.imagine * c2.real;
    return result;
}

// Hàm chia hai số phức
complex_t divideComplex(complex_t a, complex_t b) {
    complex_t result;
    float denominator = b.real * b.real + b.imagine * b.imagine;
    
    if (denominator == 0) {
        printf("Error: Division by zero\n");
        result.real = 0;
        result.imagine = 0;
        return result;
    }

    result.real = (a.real * b.real + a.imagine * b.imagine) / denominator;
    result.imagine = (a.imagine * b.real - a.real * b.imagine) / denominator;

    return result;
}
cmd_t cmd_list_complex[] ={
    {CHAR_PLUS, addComplex},
    {CHAR_SUBTRACT,subtractComplex},
    {CHAR_MULTIPLY,multiplyComplex},
    {CHAR_DIVIDE,divideComplex},
};


cui_standardcalculation_window_data_t CUI_STANDARD_CALCULATION_WINDOW_Data_GetWindowData(void) {
    return cui_standardcalculation_window_data;
}

void CUI_STANDARD_CALCULATION_WINDOW_Data_SetZ1(complex_t z) {
    cui_standardcalculation_window_data.z1 = z;
}

complex_t CUI_STANDARD_CALCULATION_WINDOW_Data_GetZ1(void) {
    return cui_standardcalculation_window_data.z1;
}

void CUI_STANDARD_CALCULATION_WINDOW_Data_SetZ2(complex_t z) {
    cui_standardcalculation_window_data.z2 = z;
}

complex_t CUI_STANDARD_CALCULATION_WINDOW_Data_GetZ2(void) {
    return cui_standardcalculation_window_data.z2;
}

void CUI_STANDARD_CALCULATION_WINDOW_Data_SetOperator(math_operator_t op) {
    cui_standardcalculation_window_data.op = op;
}

math_operator_t CUI_STANDARD_CALCULATION_WINDOW_Data_GetOperator(void) {
    return cui_standardcalculation_window_data.op;
}

void CUI_STANDARD_CALCULATION_WINDOW_Data_SetResult(complex_t result) {
    cui_standardcalculation_window_data.result = result;
}

complex_t CUI_STANDARD_CALCULATION_WINDOW_Data_GetResult(void) {
    return cui_standardcalculation_window_data.result;
}

void CUI_STANDARD_CALCULATION_WINDOW_Launch(void) {
    CUI_STANDARD_CALCULATION_WINDOW_DisplayMenu();
    CUI_STANDARD_CALCULATION_WINDOW_GetInputFromUser();
    CUI_STANDARD_CALCULATION_WINDOW_HandleUserInput();

    EVENT_MANAGER_TriggerSignal_MainWindow();
}

void CUI_STANDARD_CALCULATION_WINDOW_DisplayMenu(void) {
    printf("\n\nChe do so phuc");
    printf("\n-----------------------------");
    printf("\nMODE: STANDARD CALCULATION");
    printf("\nLua chon phep toan: z1 [+,-,*,/] z2");
    printf("\nz1 = a1 + b1.i");
    printf("\nz2 = a2 + b2.i");
    printf("\n");
}

double CUI_INPUT_VALIDATION_GetDoubleFromUser(const char* input_prompt_msg) {
    double number;
    int number_of_received_input = 0;
    bool input_is_valid = true;

    do {
        input_is_valid = true;
        printf("\n%s: ", input_prompt_msg);
        number_of_received_input = scanf("%lf", &number);
        while(getchar() != '\n');
        printf("Current received input: %.15g", number);

        if (!(number_of_received_input == 1)) {
            input_is_valid = false;
            printf("\n\nSorry, try again!");
        }
    } while (!input_is_valid);

    return number;
}

math_operator_t CUI_INPUT_VALIDATION_GetOperatorFromUser(const char* input_prompt_msg) {
    char op;
    bool input_is_valid = true;

    do {
        input_is_valid = true;
        printf("\n%s: ", input_prompt_msg);
        scanf("%c", &op);
        while(getchar() != '\n');
        printf("Current received input: %c", op);

        if (!(op == '+' || op == '-' || op == '*' || op == '/')) {
            input_is_valid = false;
            printf("\n\nSorry, try again!");
        }
    } while (!input_is_valid);

    return (math_operator_t) op;
}

void CUI_STANDARD_CALCULATION_WINDOW_GetInputFromUser(void) {
    complex_t z1;
    z1.real = CUI_INPUT_VALIDATION_GetDoubleFromUser("a1");
    z1.imagine = CUI_INPUT_VALIDATION_GetDoubleFromUser("b1");
    printf("\nReceived: z1 = %.15g + %.15g.i\n", z1.real, z1.imagine);

    complex_t z2;
    z2.real = CUI_INPUT_VALIDATION_GetDoubleFromUser("a2");
    z2.imagine = CUI_INPUT_VALIDATION_GetDoubleFromUser("b2");
    printf("\nReceived: z2 = %.15g + %.15g.i\n", z2.real, z2.imagine);

    math_operator_t op = CUI_INPUT_VALIDATION_GetOperatorFromUser("Operator [+,-,*,/]");
    printf("\nReceived: op = %c\n", op);

    CUI_STANDARD_CALCULATION_WINDOW_Data_SetZ1(z1);
    CUI_STANDARD_CALCULATION_WINDOW_Data_SetZ2(z2);
    CUI_STANDARD_CALCULATION_WINDOW_Data_SetOperator(op);
}



void CUI_STANDARD_CALCULATION_WINDOW_DisplayResult(void) {
    cui_standardcalculation_window_data_t data = CUI_STANDARD_CALCULATION_WINDOW_Data_GetWindowData();
    switch (data.op)
    {
    case CHAR_PLUS:
    case CHAR_SUBTRACT:
    case CHAR_MULTIPLY:
    case CHAR_DIVIDE:
        printf("\nResult: (%.15g + %.15g.i) %c (%.15g + %.15g.i) = %.15g + %.15g.i\n", 
            data.z1.real, data.z1.imagine, 
            data.op, 
            data.z2.real, data.z2.imagine, 
            data.result.real, data.result.imagine);
        break;
    
    default:
        printf("\nThis math operation is currently in development!");
        break;
    }
}

void CUI_STANDARD_CALCULATION_WINDOW_HandleUserInput(void) {
    cui_standardcalculation_window_data_t data = cui_standardcalculation_window_data;
    for(int i= 0; i< sizeof(cmd_list_complex) / sizeof(cmd_t); i++)
    {
        if(data.op == cmd_list_complex[i].op)
        {
            data.result = cmd_list_complex[i].handle_func(data.z1,data.z2);
            CUI_STANDARD_CALCULATION_WINDOW_Data_SetResult(data.result);
            CUI_STANDARD_CALCULATION_WINDOW_DisplayResult();
        }
    }
}