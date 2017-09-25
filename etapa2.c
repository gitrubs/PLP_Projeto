#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int automato(char* palavra,int n);
int automatoSimbolo (char* palavra, int n);
int automatoNumero (char * palavra , int n);
int automatoVar(char* palavra,int n);
int searchID (char * palavra,int n);
int equals(char * palavra, char* palavra2, int n);
int contId = 0;

typedef struct _idIdentifier{
    int id;
    char * literal;
    int size;
    struct _idIdentifier *prox;
}idIdentifier;

idIdentifier* ids;

int automato(char* palavra,int n){
    int retorno = 0;
    if(palavra[0] >= 48 && palavra[0] <= 57){
        retorno = automatoNumero(palavra,n);
    } else if(palavra[0] == '_' || palavra[0] >= 64 && palavra[0] <= 90 || palavra[0] >= 97 && palavra[0] <= 122){
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

int automatoSimbolo(char* palavra,int n){
    int i = 0;
    goto q0;
    q0:
        if(i == n){
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
                printf("Simbolo Nao Reconhecido \n");
                return 0;

        }
    }
    q2:
        if(i == n){
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
                    printf("Simbolo invalido \n");
                    return 0;
            }
        }
    q1:
        if(i==n){
            printf("RELOP <> \n");
            return 1;
        } else{
            printf("Simbolo Invalido \n");
        }
    q3:
        if(i == n){
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
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    q5:
        if(i == n){
            if(palavra[i-2] == ':'){
                printf("ATTR OPERATOR := \n");
                return 1;
            } else{
                printf("RELOP %c= \n",palavra[i-2]);
                return 1;
            }
        } else{
            printf("Simbolo Invalido\n");
            return 0;
        }
    q4:
        if(i == n){
            printf("DELIMITER %c \n",palavra[i-1]);
            return 1;
        } else{
            switch(palavra[i]){
                case '=':
                    i++;
                    goto q5;
                    break;
                default:
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    q10:
        if(i == n){
            printf("DELIMITER %c \n", palavra[i-1]);
            return 1;
        } else{
            printf("Simbolo Invalido \n");
            return 0;
        }
    q6:
        if(i == n){
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
    q7:
        if(i == n){
            printf("Simbolo Invalido \n");
            return 0;
        } else{
            while(palavra[i] != '*'){
                i++;
            }
            if(i == n){
                printf("Simbolo invalida \n");
                return 0;
            }
            if(palavra[i] == '*'){
                i++;
                goto q8;
            }
        }
    q8:
        if(i == n){
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
    q9:
        if(i == n){
            printf("Comentario \n");
            return 1;
        } else{
            printf("Simbolo Invalido \n");
            return 0;
        }
    q11:
        if(i == n){
            printf("Operador %c \n",palavra[i-1]);
            return 1;
        } else{
            switch(palavra[i]){
                case 'i':
                    i++;
                    goto q12;
                    break;
                default:
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    q12:
        if(i == n){
            printf("Palavra nao reconhecida \n");
            return 0;
        } else{
            switch(palavra[i]){
                case 'v':
                    i++;
                    goto q13;
                    break;
                default:
                    printf("Simbolo Invalido \n");
                    return 0;
            }
        }
    q13:
        if(i == n){
            printf("Operador %s \n",palavra);
            return 1;
        } else{
            printf("Simbolo nao reconhecido \n");
            return 0;
        }
}
int automatoNumero(char* palavra,int n){
        int i = 1;
        goto q1;
        q1:
            if(i == n){
                 printf("INTEGER VALUE %s \n",palavra);
                 return 1;
            }
            else if(!(palavra[i] >= 48 && palavra[i] <= 57)){
                printf("Simbolo Invalido \n");
                return 0;
            } else{
                i++;
                goto q1;
            }

}
int automatoVar(char* palavra,int n){
    int  i = 1;
    goto q1;
    q1:
        if(i == n){
            printf("ID %d %s \n",searchID(palavra,n), palavra);
            return 1;
        } else{
            if(!(palavra[i] >= 48 && palavra[i] <= 57 || palavra[i] == '_' || palavra[i] >= 64 && palavra[i] <= 90 || palavra[i] >= 97 && palavra[i] <= 122)){
                printf("Simbolo Invalido \n");
                return 0;
           } else{
              i++;
              goto q1;
           }
        }


}

int searchID (char * palavra,int n){
    if(ids == NULL){
        ids = (idIdentifier*) calloc(1,sizeof(idIdentifier));
        contId++;
        ids->id = contId;
        ids->literal = palavra;
        ids->size = n;
        return ids->id;
    }
    else{
            idIdentifier* iter = ids;
            while(iter != NULL){
                if(iter->size == n){
                    if(equals(palavra,iter->literal,n) == 1){
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
int equals(char* palavra,char* palavra2,int n){
    int i = 0;
    for(i = 0;i < n;i++){
        if(palavra[i] != palavra2[i]){
            return 0;
        }
    }
    return 1;
}

int verificaPalavraReservada(char palavra[], int tamPalavra)
{
	int quantPalavrasReservadas = 18;
	int tamMaiorPalavraReservada = 9;

	// Flag para verificar se palavra é reservada
	int flagReservada = 1;

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

	// Percorre as palavras reservadas
	int i;
	for(i = 0; i < quantPalavrasReservadas; i++)
	{
		flagReservada = 1;
		char * palavraReservada = palavrasReservadas[i];
		int j;

		// Se a palavra reservada for maior do que a palavra a ser verificada, não verifica
		if (tamPalavra <= strlen(palavraReservada));
		{
			// Compara a palavra com a palavra reservada
			for(j = 0; j < tamPalavra; j++)
			{
				//printf("%c %c \n", palavra[j], palavraReservada[j]);
				if(palavra[j] != palavraReservada[j])
				{
					flagReservada = 0;
					break;
				}	
			}
		}
		if(flagReservada == 1 && j == strlen(palavraReservada))
		{
			printf("RESERVED WORD %s\n", palavra);
			return 1;
		}
	}
	return 0;
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

	return 0;
}