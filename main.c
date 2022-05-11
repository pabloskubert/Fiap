#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define VERSAO "1.0.0"
#define NAO_E_EQUACAO -1

#define TRUE 1
#define FALSE 0

#define LIMITE_DIGITOS 1000

typedef uint8_t EXIT_CODE;
typedef uint8_t BOOL;



int resolver_equacao(char *equacao, char *op_a, char *op_b);
void main_repl_calc_loop(void);
char * remover_espacos_em_branco(char *str);


EXIT_CODE main(int argc, char * argv[]) {
    /*
     *  Lê todos os Args de INPUT do Programa
     */
    if (argc > 1) {
        if (strcmp(argv[1], "-v") == 0) {
            printf("\nVersao: %s\n", VERSAO);
            return (EXIT_CODE) EXIT_SUCCESS;
        }

        if (strcmp(argv[1], "-h") == 0) {
            printf("\nUso: ./Calc.exe -v|-h|--author\n");
            return (EXIT_CODE) EXIT_SUCCESS;
        }

        if (strcmp(argv[1], "--autor") == 0) {
            printf("\nAutor: PABLO HENRIQUE G. VIANA (RM92029)\n");
            return (EXIT_CODE) EXIT_SUCCESS;
        }

        printf("\nUso: ./Calc.exe -v|-h|--autor\n");
        return EXIT_FAILURE;
    }

    main_repl_calc_loop();
    return EXIT_SUCCESS;
}

void main_repl_calc_loop() {
    /*
     *  Loop de REPL para o programa
     *  Espera um comando de entrada
     *  E executa o comando
     *  Retorna para o loop
     * A menos que o comando "exit" ou "\q" for digitado
     */
    char *equacao = (char *) malloc(sizeof(char) * LIMITE_DIGITOS);
    char * op_a = (char *) malloc(sizeof(char) * LIMITE_DIGITOS);
    char * op_b = (char *) malloc(sizeof(char) * LIMITE_DIGITOS);


    while (1) {
        printf("\t\t\n Calc Input>>> ");
        fgets(equacao, LIMITE_DIGITOS, stdin);
        equacao = remover_espacos_em_branco(equacao);

        if (strncmp(equacao, "exit", sizeof(char) * 4) == 0 || strncmp(equacao, "\\q", sizeof(char) * 2) == 0)
            break;

        signed int ret = resolver_equacao(equacao, op_a, op_b);
        if (ret != NAO_E_EQUACAO) {

            printf("\t\t\n Resultado>>> %d \n", ret);
        } else
            printf("\t\t\n Aviso>>> %s nao e uma equação matematica. \n", equacao);

        // Limpa as strings
        memset(equacao, '\0', sizeof(char) * LIMITE_DIGITOS);
        memset(op_a, '\0', sizeof(char) * LIMITE_DIGITOS);
        memset(op_b, '\0', sizeof(char) * LIMITE_DIGITOS);
    }

    printf("\n\n Goodbye. \n\n");
}

int resolver_equacao(char * equacao, char * op_a, char * op_b) {
    /*
     *  Resolve uma equação matematica
     *  Retorna o resultado
     *  Se não for uma equação matematica, retorna -1
     *  Se não for uma equação matematica, retorna -1
     */

     // Loop till the operand is not found
     int c = 0;
     signed int operando_a = 0;
     signed int operando_b = 0;


     unsigned int op_a_index = 0;
     unsigned int op_b_index = 0;

     char operador = '\0';
     BOOL operador_encontrado = FALSE;
     BOOL pular_operador = TRUE;

     // Procura o operador na string
     while (*(equacao + c) != '\0') {

         // Se for um operador, guarda o index
         if (*(equacao + c) == '+' || *(equacao + c) == '-' || *(equacao + c) == '*' || *(equacao + c) == '/') {
             operador = equacao[c];
             operador_encontrado = TRUE;
         }

         // Obter operando A
         if (operador_encontrado == FALSE) {

             memcpy(op_a + op_a_index++, equacao + c, sizeof(char) * LIMITE_DIGITOS);
         // Obter operando B
         } else {
             uint8_t i;
             if (pular_operador == TRUE) {
                 i = c + 1;
                 pular_operador = FALSE;
             } else i = 0;

             memcpy(op_b + op_b_index++, equacao + (c + i), sizeof(char) * LIMITE_DIGITOS);
         }

         c++;
     }

     if (operador_encontrado == FALSE) {
         return NAO_E_EQUACAO;
     }

     op_a[++op_a_index] = '\0';
     op_b[++op_b_index] = '\0';

     operando_a = strtol(op_a, NULL, 10);
     operando_b = strtol(op_b, NULL, 10);

    // Resolve a equação
    if (operador == '+') {
        return operando_a + operando_b;
    } else if (operador == '-') {
        return operando_a - operando_b;
    } else if (operador == '*') {
        return operando_a * operando_b;
    } else {
        return operando_a / operando_b;
    }
}

char *remover_espacos_em_branco(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}

