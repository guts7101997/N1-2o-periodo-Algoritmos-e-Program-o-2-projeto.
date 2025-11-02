#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_GRAU 20


void lerPolinomio(int *grau, float coeficientes[]) {
    for (int i = 0; i <= MAX_GRAU; i++) {
        coeficientes[i] = 0;
    }

    printf("Digite o grau do polinomio (maximo %d): ", MAX_GRAU);
    scanf("%d", grau);

    if (*grau > MAX_GRAU) {
        printf("Grau maximo excedido. Usando grau %d.\n", MAX_GRAU);
        *grau = MAX_GRAU;
    }

    for (int i = 0; i <= *grau; i++) {
        printf("Digite o coeficiente de x^%d: ", i);
        scanf("%f", &coeficientes[i]);
    }
}

void imprimirPolinomio(int grau, float coeficientes[]) {
    printf("P(x) = ");
    for (int i = grau; i >= 0; i--) {
        if (coeficientes[i] != 0) {
            if (i < grau) {
                if (coeficientes[i] > 0) {
                    printf(" + ");
                } else {
                    printf(" ");
                }
            }


            if (i > 1) {
                printf("%.2fx^%d", coeficientes[i], i);
            } else if (i == 1) {
                printf("%.2fx", coeficientes[i]);
            } else { 
                printf("%.2f", coeficientes[i]);
            }
        }
    }
    printf("\n");
}


float calcularValor(int grau, float coeficientes[], float x) {
    float resultado = 0;
    for (int i = 0; i <= grau; i++) {
        resultado += coeficientes[i] * pow(x, i);
    }
    return resultado;
}

void somarPolinomios(int grau1, float coef1[], int grau2, float coef2[], int *grauResultado, float coefResultado[]) {
    if (grau1 > grau2) {
        *grauResultado = grau1;
    } else {
        *grauResultado = grau2;
    }

    for (int i = 0; i <= *grauResultado; i++) {
        coefResultado[i] = 0;
    }
    
    for (int i = 0; i <= *grauResultado; i++) {
        
        float c1, c2;
        if (i <= grau1) {
            c1 = coef1[i];
        } else {
            c1 = 0;
        }
        
        if (i <= grau2) {
            c2 = coef2[i];
        } else {
            c2 = 0;
        }

        coefResultado[i] = c1 + c2;
    }
}


void multiplicarPolinomios(int grau1, float coef1[], int grau2, float coef2[], int *grauResultado, float coefResultado[]) {
    *grauResultado = grau1 + grau2;
    if (*grauResultado > MAX_GRAU) {
        *grauResultado = MAX_GRAU;
    }

    for (int i = 0; i <= *grauResultado; i++) {
        coefResultado[i] = 0;
    }

    for (int i = 0; i <= grau1; i++) {
        for (int j = 0; j <= grau2; j++) {
            int novoGrau = i + j;
            if (novoGrau <= MAX_GRAU) {
                coefResultado[novoGrau] += coef1[i] * coef2[j];
            }
        }
    }
}


int main() {
    int grauPrincipal;
    float coeficientesPrincipal[MAX_GRAU + 1];
    int opcao;

    printf("--- Calculadora de Polinomios ---\n");
    printf("Por favor, informe o primeiro polinomio para ser o principal.\n");
    lerPolinomio(&grauPrincipal, coeficientesPrincipal);

    do {
        printf("\nPolinomio principal atual: ");
        imprimirPolinomio(grauPrincipal, coeficientesPrincipal);

        printf("\nEscolha a operacao com o polinomio principal:\n");
        printf("1. Calcular o valor em um ponto\n");
        printf("2. Somar com outro polinomio\n");
        printf("3. Multiplicar por outro polinomio\n");
        printf("4. Inserir um novo polinomio principal\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        int novoGrau, grauResultado;
        float novosCoeficientes[MAX_GRAU + 1];
        float coeficientesResultado[MAX_GRAU + 1] = {0};

        switch (opcao) {
            case 1: {
                float x;
                printf("Digite o valor de x: ");
                scanf("%f", &x);
                float resultado = calcularValor(grauPrincipal, coeficientesPrincipal, x);
                printf("P(%.2f) = %.2f\n", x, resultado);
                break;
            }
            case 2: {
                lerPolinomio(&novoGrau, novosCoeficientes);
                somarPolinomios(grauPrincipal, coeficientesPrincipal, novoGrau, novosCoeficientes, &grauResultado, coeficientesResultado);
                grauPrincipal = grauResultado;
                
                for (int i = 0; i <= grauPrincipal; i++) {
                    coeficientesPrincipal[i] = coeficientesResultado[i];
                }
                printf("Resultado da soma:\n");
                imprimirPolinomio(grauPrincipal, coeficientesPrincipal);
                break;
            }
            case 3: {
                lerPolinomio(&novoGrau, novosCoeficientes);
                multiplicarPolinomios(grauPrincipal, coeficientesPrincipal, novoGrau, novosCoeficientes, &grauResultado, coeficientesResultado);
                grauPrincipal = grauResultado;
                
                for (int i = 0; i <= grauPrincipal; i++) {
                    coeficientesPrincipal[i] = coeficientesResultado[i];
                }
                printf("Resultado da multiplicacao:\n");
                imprimirPolinomio(grauPrincipal, coeficientesPrincipal);
                break;
            }
            case 4: {
                printf("\nInserindo um novo polinomio principal...\n");
                lerPolinomio(&grauPrincipal, coeficientesPrincipal);
                printf("Novo polinomio principal guardado.\n");
                break;
            }
            case 0: {
                printf("Saindo do programa.\n");
                break;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}
