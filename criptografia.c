#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função para verificar se um número é primo
int eh_primo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Gera o array contendo a sequência matemática escolhida
void gerar_sequencia(int tipo, int tamanho, int *seq, int p1, int p2) {
    switch (tipo) {
        case 1: // PA: p1 = a1, p2 = r
            for (int i = 0; i < tamanho; i++) {
                seq[i] = p1 + i * p2;
            }
            break;
        case 2: // PG: p1 = a1, p2 = q
            seq[0] = p1;
            for (int i = 1; i < tamanho; i++) {
                seq[i] = seq[i - 1] * p2;
            }
            break;
        case 3: // Fibonacci
            if (tamanho > 0) seq[0] = 1;
            if (tamanho > 1) seq[1] = 1;
            for (int i = 2; i < tamanho; i++) {
                seq[i] = seq[i - 1] + seq[i - 2];
            }
            break;
        case 4: { // AS CHAVES AQUI SÃO OBRIGATÓRIAS NO C!
            int num = 2, count = 0;
            while (count < tamanho) {
                if (eh_primo(num)) {
                    seq[count++] = num;
                }
                num++;
            }
            break;
        }
    }
}

// Encripta a string aplicando Cifra de César + Sequência Numérica
void encriptar(const char *origem, char *destino, int shift, const int *seq, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        char c = tolower(origem[i]);
        if (c >= 'a' && c <= 'z') {
            int pos_original = c - 'a';
            int deslocamento_total = shift + seq[i];
            int nova_pos = (pos_original + deslocamento_total) % 26;
            
            // Tratamento de mod negativo em C
            if (nova_pos < 0) nova_pos += 26;
            
            destino[i] = nova_pos + 'a';
        } else {
            destino[i] = c; // Mantém caracteres que não forem letras
        }
    }
    destino[tamanho] = '\0';
}

// Salva o log de saída em arquivo de texto
void salvar_arquivo(const char *palavra_orig, const char *palavra_enc, int shift, int tipo, int tam) {
    FILE *arq = fopen("resultado_criptografia.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arq, "Original: %s | Codificada: %s | SHIFT: %d | Tipo Sequencia: %d | Letras: %d\n",
            palavra_orig, palavra_enc, shift, tipo, tam);
    fclose(arq);
    printf("Log gravado com sucesso em 'resultado_criptografia.txt'.\n");
}

int main() {
    char palavra[16], encriptada[16];
    int shift, opcao, tam;
    int p1 = 0, p2 = 0;

    printf("=== SISTEMA DE CRIPTOGRAFIA MATEMATICA ===\n");
    printf("Digite a palavra (ate 15 letras, sem espacos): ");
    scanf("%15s", palavra);

    tam = strlen(palavra);

    printf("Informe o valor do SHIFT fixo: ");
    scanf("%d", &shift);

    printf("\nEscolha a sequencia matematica:\n");
    printf("1 - Progressao Aritmetica (PA)\n");
    printf("2 - Progressao Geometrica (PG)\n");
    printf("3 - Fibonacci\n");
    printf("4 - Numeros Primos\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Informe o primeiro termo (a1) e a razao (r): ");
        scanf("%d %d", &p1, &p2);
    } else if (opcao == 2) {
        printf("Informe o primeiro termo (a1) e a razao (q): ");
        scanf("%d %d", &p1, &p2);
    }

    int *seq = (int *)malloc(tam * sizeof(int));
    gerar_sequencia(opcao, tam, seq, p1, p2);

    encriptar(palavra, encriptada, shift, seq, tam);

    printf("\nPalavra Criptografada: %s\n", encriptada);

    salvar_arquivo(palavra, encriptada, shift, opcao, tam);

    free(seq);
    return 0;
}