#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Declaração de funções e variáveis globais
int automato(char* palavra,int n);
int automatoSimbolo (char* palavra, int n);
int automatoNumero (char * palavra , int n);
int automatoVar(char* palavra,int n);
int searchID (char * palavra,int n);
int equals(char * palavra, char* palavra2);
int contId = 0;

// Estrutura para armazenar ids
typedef struct _idIdentifier{
    int id;
    char * literal;
    int size;
    struct _idIdentifier *prox;
}idIdentifier;

idIdentifier* ids;
char saida[300] ;

// Autômato de reconhecimento global
int automato(char* palavra,int n){
    int retorno = 0;
    // Verifica se o cursor se encontra em algum número (0...9)
    if(palavra[0] >= 48 && palavra[0] <= 57){
        retorno = automatoNumero(palavra,n);
    } // Verifica se o cursor está em uma possível variável (A...Z || a...z || _)
    else if(palavra[0] == '_' || palavra[0] >= 65 && palavra[0] <= 90 || palavra[0] >= 97 && palavra[0] <= 122){
        // Reconhece o operador 'div' ou uma variável qualquer
        if(palavra[0] == 'd' && n == 3){
            if(automatoSimbolo(palavra,n)){
                retorno = 1;
            } else{
                 retorno = automatoVar(palavra,n);
            }
        }
        else{
                retorno = automatoVar(palavra,n);
        }
    } else{
        retorno = automatoSimbolo(palavra,n);
    }
    return retorno;
}

// Autômato para reconhecer símbolos ('<', '<=', '>', '>=', '<>', ':=', '//', '(', ')', '*', '+', ',', ';', '.', 'div', '-')
int automatoSimbolo(char* palavra,int n){
    int i = 0;
    goto q0;
    // Estado inicial
    q0:
        if(i == n){
            strcat(saida, "Palavra nao reconhecida \n");
            printf("Palavra nao reconhecida \n");
            return 0;
        } else{
           switch(palavra[i]){
            case '<':
                i++;
                goto q2;
                break;
            case '>':
                i++;
                goto q3;
                break;
            case ':':
                i++;
                goto q4;
                break;
            case '/':
                i++;
                goto q6;
                break;
            case '(':
                i++;
                goto q10;
                break;
            case ')':
                i++;
                goto q10;
                break;
            case '*':
                i++;
                goto q11;
                break;
            case '+':
                i++;
                goto q11;
                break;
            case ',':
                i++;
                goto q10;
                break;
            case ';':
                i++;
                goto q10;
                break;
            case '.':
                i++;
                goto q10;
                break;
            case 'd':
                i++;
                goto q11;
                break;
            case '-':
                i++;
                goto q11;
                break;
            default:
                strcat(saida, "Simbolo Nao Reconhecido \n");
                printf("Simbolo Nao Reconhecido \n");
                return 0;

        }
    }
    // '<'
    q2:
        if(i == n){
            strcat(saida, "RELOP < \n");
            printf("RELOP <");
            return 1;
        } else{
            switch(palavra[i]){
                case '>':
                    i++;
                    goto q1;
                    break;
                case '=':
                        i++;
                        goto q5;
                        break;


                default:
                    strcat(saida, "Simbolo Invalido \n");
                    printf("Simbolo invalido \n");
                    return 0;
            }
        }
    // '<>'
    q1:
        if(i==n){
            strcat(saida, "RELOP <> \n");
            printf("RELOP <> \n");
            return 1;
        } else{
            strcat(saida, "Simbolo Invalido \n");
            printf("Simbolo Invalido \n");
        }
    // '>'
    q3:
        if(i == n){
            strcat(saida, "RELOP > \n");
            printf("RELOP > \n");
            return 1;
        }
        else{
            switch(palavra[i]){
                case '=':
                    i++;
                    goto q5;
                    break;
                default:
                    strcat(saida, "Simbolo Invalido \n");
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    // ':='
    q5:
        if(i == n){
            if(palavra[i-2] == ':'){
                strcat(saida, "");
                printf("ATTR OPERATOR := \n");
                return 1;
            } else{
                printf("RELOP %c= \n",palavra[i-2]);
                strcat(saida, "RELOP ");
                char str1[2] = {palavra[i-2] , '\0'};
                char str2[5] = "";
                strcpy(str2,str1);
                strcat(saida, str2);
                strcat(saida, " = \n");
                return 1;
            }
        } else{
            strcat(saida, "Simbolo Invalido \n");
            printf("Simbolo Invalido\n");
            return 0;
        }
    // ":"
    q4:
        if(i == n){
            printf("DELIMITER %c \n",palavra[i-1]);
            strcat(saida, "DELIMITER ");
            char str1[2] = {palavra[i-1] , '\0'};
            char str2[5] = "";
            strcpy(str2,str1);
            strcat(saida, str2);
            strcat(saida, " \n");
            return 1;
        } else{
            switch(palavra[i]){
                case '=':
                    i++;
                    goto q5;
                    break;
                default:
                    strcat(saida, "Simbolo Invalido");
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    // '(' || ')' || ',' || '.' || ';'
    q10:
        if(i == n){
            printf("DELIMITER %c \n",palavra[i-1]);
            strcat(saida, "DELIMITER ");
            char str1[2] = {palavra[i-1] , '\0'};
            char str2[5] = "";
            strcpy(str2,str1);
            strcat(saida, str2);
            strcat(saida, " \n");
            return 1;
        } else{
            strcat(saida, "Simbolo Invalido \n");
            printf("Simbolo Invalido \n");
            return 0;
        }
    // '/'
    q6:
        if(i == n){
            strcat(saida, "Simbolo Invalido \n");
            printf("Simbolo Invalido \n");
            return 0;
        } else{
            switch(palavra[i]){
                case '*':
                    i++;
                    goto q7;
                    break;
                default:
                    return 0;
            }
        }
    // '/*'
    q7:
        if(i == n){
            strcat(saida, "Simbolo Invalido \n");
            printf("Simbolo Invalido \n");
            return 0;
        } else{
            while(palavra[i] != '*'){
                i++;
            }
            if(i == n){
                strcat(saida, "Simbolo Invalido \n");
                printf("Simbolo Invalido \n");
                return 0;
            }
            if(palavra[i] == '*'){
                i++;
                goto q8;
            }
        }
    // '/* ... *'
    q8:
        if(i == n){
            strcat(saida, "Simbolo Invalido \n");
            printf("Simbolo Invalido \n");
            return 0;
        } else{
            switch(palavra[i]){
                case '/':
                    i++;
                    goto q9;
                    break;
                default:
                    return 0;
            }
        }
    // '/* ... */'
    q9:
        if(i == n){
            strcat(saida, "Comentario \n");
            printf("Comentario \n");
            return 1;
        } else{
            strcat(saida, "Simbolo Invalido \n");
            printf("Simbolo Invalido \n");
            return 0;
        }
    // '*' || '+' || 'd' || '-'
    q11:
        if(i == n){
            printf("Operador %c \n",palavra[i-1]);
            strcat(saida, "Operador ");
            char str1[2] = {palavra[i-1] , '\0'};
            char str2[5] = "";
            strcpy(str2,str1);
            strcat(saida, str2);
            strcat(saida, " \n");
            return 1;
        } else{
            switch(palavra[i]){
                case 'i':
                    i++;
                    goto q12;
                    break;
                default:
                    strcat(saida, "Simbolo Invalido \n");
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    // 'di'
    q12:
        if(i == n){
            strcat(saida, "Palavra nao reconhecida \n");
            printf("Palavra nao reconhecida \n");
            return 0;
        } else{
            switch(palavra[i]){
                case 'v':
                    i++;
                    goto q13;
                    break;
                default:
                    strcat(saida, "Simbolo invalido \n");
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    // 'div'
    q13:
        if(i == n){
            printf("Operador %s \n",palavra);
            strcat(saida, "Operador ");
            strcat(saida, palavra);
            strcat(saida, " \n");
            return 1;
        } else{
            strcat(saida, "Simbolo nao reconhecido \n");
            printf("Simbolo nao reconhecido \n");
            return 0;
        }
}

// Autômato de reconhecimento de números
int automatoNumero(char* palavra,int n){
        int i = 1;
        goto q1;
        q1:
            if(i == n){
                 strcat(saida, "INTEGER VALUE ");
                 strcat(saida, palavra);
                 strcat(saida, " \n");
                 printf("INTEGER VALUE %s \n",palavra);
                 return 1;
            }
            // Se não estiver entre 0 e 9
            else if(!(palavra[i] >= 48 && palavra[i] <= 57)){
                strcat(saida, "");
                printf("Simbolo Invalido \n");
                return 0;
            } else{
                i++;
                goto q1;
            }

}

// Reconhecimento de variáveis
int automatoVar(char* palavra,int n){
    int  i = 1;
    goto q1;
    q1:
        if(i == n){
            char idString[50];
            strcat(saida, "ID ");
            int searchIdResult = searchID(palavra,n);
            char str2[10];
            sprintf(str2, "%d", searchIdResult);
            strcat(saida, str2);
            strcat(saida, " ");
            strcat(saida, palavra);
            strcat(saida, " \n");
            return 1;
        } else{
            // Verifica se está entre (0 e 9) ou ('a' e 'z') ou ('A' e 'Z') ou '_'
            if(!(palavra[i] >= 48 && palavra[i] <= 57 || palavra[i] == '_' || palavra[i] >= 65 && palavra[i] <= 90 || palavra[i] >= 97 && palavra[i] <= 122)){
                strcat(saida, "Simbolo Invalido \n");
                printf("Simbolo Invalido \n");
                return 0;
           } else{
              i++;
              goto q1;
           }
        }
}

// Procura pelo id na lista criada
int searchID (char * palavra,int n){
    // Cria a lista em caso de ela ainda não existir
    if(ids == NULL){
        ids = (idIdentifier*) calloc(1,sizeof(idIdentifier));
        contId++;
        ids->id = contId;
        ids->literal = palavra;
        ids->size = n;
        return ids->id;
    }
    else{
        // Procura o id na lista buscando pela palavra passada
            idIdentifier* iter = ids;
            while(iter != NULL){
                if(iter->size == n){
                    if(equals(palavra,iter->literal) == 1){
                        return iter->id;
                    }
                }
                iter = iter->prox;
            }
            free(iter);
            idIdentifier* novoId =  (idIdentifier*) calloc(1,sizeof(idIdentifier));
            contId++;
            novoId->literal = palavra;
            novoId->id = contId;
            novoId->size = n;
            ids->prox = novoId;
            return novoId->id;

    }
   return 0;
}

// Função auxiliar de verificação de igualdade entre 2 palavras
int equals(char* palavra,char* palavra2){

    if (strlen(palavra) != strlen(palavra2)) {
        return 0;
    }

    int n = strlen(palavra);

    for(int i = 0;i < n;i++){
        if(palavra[i] != palavra2[i]){
            return 0;
        }
    }
    return 1;
}

// Reconhecimento de palavra reservada da linguagem
int verificaPalavraReservada(char palavra[], int tamPalavra)
{
    int quantPalavrasReservadas = 18;
    int tamMaiorPalavraReservada = 9;

    char * palavrasReservadas[18];
    palavrasReservadas[0] = "program";
    palavrasReservadas[1] = "if";
    palavrasReservadas[2] = "do";
    palavrasReservadas[3] = "var";
    palavrasReservadas[4] = "false";
    palavrasReservadas[5] = "begin";
    palavrasReservadas[6] = "then";
    palavrasReservadas[7] = "and";
    palavrasReservadas[8] = "integer";
    palavrasReservadas[9] = "write";
    palavrasReservadas[10] = "end";
    palavrasReservadas[11] = "else";
    palavrasReservadas[12] = "or";
    palavrasReservadas[13] = "boolean";
    palavrasReservadas[14] = "procedure";
    palavrasReservadas[15] = "while";
    palavrasReservadas[16] = "not";
    palavrasReservadas[17] = "true";

    // Percorre as palavras reservadas e verifica a palavra dada
    int i;
    for(i = 0; i < quantPalavrasReservadas; i++)
    {
        char * palavraReservada = palavrasReservadas[i];

        if(equals(palavra, palavraReservada) == 1)
        {
            strcat(saida, "RESERVED WORD ");
            strcat(saida, palavra);
            strcat(saida, " \n");
            printf("RESERVED WORD %s\n", palavra);
            return 1;
        }
    }
    return 0;
}


void escreverSaida(){
    // Especifica local do arquivo a ser escrito
    char url[] = "saida.txt";

    FILE *arq;

    // Abre arquivo
    arq = fopen(url, "w");

    // Verifica se foi possível abrir o arquivo
    if(arq == NULL)
    {
        printf("Não foi possivel abrir o arquivo\n");
    }
    else
    {
        fprintf(arq, "%s", saida);
    }

    fclose(arq);
}


int main(void)
{
    // Especifica local do arquivo a ser lido
    char url[] = "arquivo.txt";
    char linha[100];
    FILE *arq;

    // Abre arquivo
    arq = fopen(url, "r");

    // Verifica se foi possível abrir o arquivo
    if(arq == NULL)
    {
        printf("Não foi possivel abrir o arquivo\n");
    }
    else
    {
        int i = 0;
        char * p;

        // Lê linha a linha do arquivo
        while (fgets(linha, sizeof(linha), arq) != NULL)
        {
            // Remove \r e \n da linha
            linha[strcspn(linha, "\r\n")] = 0;

            // Lê palavra a palavra (diferenciada por espaço) da linha lida
            p = strtok(linha," ");

            while (p != NULL)
            {
                int tamP = strlen(p);

                // Verifica se a palavra é reservada
                if(verificaPalavraReservada(p, tamP) != 1)
                {

                    // Valida reconhecimento da palavra que não é reservada
                    automato(p, tamP);
                }

                // Lê próxima palavra
                p = strtok(NULL, " ");
            }
        }
    }

    fclose(arq);

    escreverSaida();

    return 0;
}
