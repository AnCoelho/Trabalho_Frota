#import <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#import <string.h>
#include <time.h>
#define MAX_LENGTH 100
#define MAX_CLIENTES 100

typedef struct
{
    char tipoPessoa;
    char contato[80];
    char observacaoUsuario[100];
    int codCliente;
    char entradaUserTipoPessoa;
    char identificacao[40];
    char nomeFantasia[50];
    int dia, mes, ano;
    char cpf[12];
    char cnpj[15];
    char docRegistro[30];
    char insmuniPJ[15];
    char suframaPJ[15];
    char bairro[60];
    char cidade[60];
    char estado[60];
    char telefone1[25];
    char telefone2[25];
    char telefone3[25];
    char cep[MAX_LENGTH];
    char endereco[MAX_LENGTH];
    char numero[MAX_LENGTH];
    char complemento[MAX_LENGTH];
    char email[MAX_LENGTH];
    char site[MAX_LENGTH];
    char siteAtivo;
} Cliente;

Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// imprimir c�digo do cliente(ambos)

void imprimirCodCliente()
{
    printf("-----------------------\n");
    int randomNumber = rand() % 1000000;
    clientes[totalClientes].codCliente = randomNumber;
    printf("C�digo do cliente: %d \n", randomNumber);
}
// imprimir tipo de pessoa ( F�sico ou Jur�dico )

int imprimirTipoPessoa()
{
    printf("-----------------------\n");
    do
    {
        printf(
            "Pessoa f�sica ou jur�dica? ('F' para f�sica ou 'J' para jur�dica) : ");
        scanf(" %c", &clientes[totalClientes].entradaUserTipoPessoa);
        if (clientes[totalClientes].entradaUserTipoPessoa == 'F')
        {
            clientes[totalClientes].tipoPessoa = 'F';
            return 0;
        }
        else if (clientes[totalClientes].entradaUserTipoPessoa == 'J')
        {
            clientes[totalClientes].tipoPessoa = 'J';
            return 0;
        }
        else
        {
            printf("-----------------------\n");
            printf("Campo digitado de forma inv�lida");
            printf("\n-----------------------\n");
            printf("Tente novamente: ");
            printf("\n-----------------------\n");
        }

    } while (1);
}
// imprimir data do cadastro ( dia atual para ambos )

void imprimirDataAtual()
{
    printf("-----------------------\n");
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    printf("Data: %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// imprimir nome(pessoa f�sica) ou raz�o social(pessoa jur�dica)
int imprimirIdentificacao()
{
    printf("-----------------------\n");

    do
    {
        if (clientes[totalClientes].tipoPessoa == 'F')
        {
            printf("Nome: ");
        }
        else if (clientes[totalClientes].tipoPessoa == 'J')
        {
            printf("Raz�o social: ");
        }
        else
        {
            printf("Um erro inesperado ocorreu!");
            return 0;
        }

        fgets(clientes[totalClientes].identificacao,
              sizeof(clientes[totalClientes].identificacao), stdin);

        // Verifica se a string cont�m n�meros
        int contemNumeros = 0;
        for (int i = 0; clientes[totalClientes].identificacao[i] != '\0'; i++)
        {
            if (isdigit(clientes[totalClientes].identificacao[i]))
            {
                contemNumeros = 1;
                break;
            }
        }

        // Verifica se a string n�o cont�m apenas espa�os em branco e n�o est� vazia
        if (contemNumeros || clientes[totalClientes].identificacao[0] == '\n' ||
            clientes[totalClientes].identificacao[0] == ' ')
        {
            printf("-----------------------\n");
            printf("Campo digitado de forma inv�lida");
            printf("\n-----------------------\n");
            printf("Tente novamente: ");
            printf("\n-----------------------\n");
        }
        else
        {
            break; // Sai do loop se a entrada for v�lida
        }
    } while (1);

    return 1;
}

// imprimir nome_fantasia( pessoa jur�dica )
int imprimirNomeFantasia()
{
    printf("-----------------------\n");

    if (clientes[totalClientes].tipoPessoa == 'J')
    {

        do
        {
            // Solicita ao usu�rio para digitar o nome fantasia
            printf("Digite o nome fantasia: ");

            // Tenta ler a linha fornecida pelo usu�rio
            if (fgets(clientes[totalClientes].nomeFantasia,
                      sizeof(clientes[totalClientes].nomeFantasia), stdin) == NULL)
            {
                perror("Erro ao ler a entrada");
                exit(EXIT_FAILURE);
            }

            // Remove o caractere de nova linha, se presente
            // Verifica se a string cont�m apenas letras
            int contem_numeros = 0;
            for (int i = 0; clientes[totalClientes].nomeFantasia[i] != '\0'; i++)
            {
                if (isdigit(clientes[totalClientes].nomeFantasia[i]))
                {
                    contem_numeros = 1;
                    break;
                }
            }

            // Se a string contiver n�meros, exibe uma mensagem de erro
            if (contem_numeros)
            {
                printf("-----------------------\n");
                printf("Campo digitado de forma inv�lida");
                printf("\n-----------------------\n");
                printf("Tente novamente: ");
                printf("\n-----------------------\n");
            }
            else
            {
                return 1;
            }
        } while (1);
    }
    else if (clientes[totalClientes].tipoPessoa == 'F')
    {
        return 1;
    }
    else
    {
        printf("Ocorreu um erro inesperado!");
    }
    return 1;
}
// imprimir CPF(pessoa f�sica) ou CNPJ(pessoa jur�dica)
int imprimirCpfCnpj()
{
    printf("-----------------------\n");
    if (clientes[totalClientes].tipoPessoa == 'F')
    {

        do
        {
            printf("CPF: ");
            fgets(clientes[totalClientes].cpf, sizeof(clientes[totalClientes].cpf),
                  stdin);
            clientes[totalClientes].cpf[strcspn(clientes[totalClientes].cpf, "\n")] =
                '\0';

            if (strcspn(clientes[totalClientes].cpf,
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
                strlen(clientes[totalClientes].cpf))
            {
                printf("\nErro: O cpf nao pode conter letras.\n");
            }

            if ((strlen(clientes[totalClientes].cpf) != 11))
            {
                printf(
                    "\nErro: O CPF deve ter exatamente 11 digitos. Tente novamente.\n");
            }

        } while (strcspn(clientes[totalClientes].cpf,
                         "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
                     strlen(clientes[totalClientes].cpf) ||
                 (strlen(clientes[totalClientes].cpf) != 11));
    }

    else if (clientes[totalClientes].tipoPessoa == 'J')
    {

        do
        {
            printf("CNPJ: ");
            fgets(clientes[totalClientes].cnpj, sizeof(clientes[totalClientes].cnpj),
                  stdin);
            clientes[totalClientes]
                .cnpj[strcspn(clientes[totalClientes].cnpj, "\n")] = '\0';

            if (strcspn(clientes[totalClientes].cnpj,
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
                strlen(clientes[totalClientes].cnpj))
            {
                printf("\nErro: O cnpj n�o pode conter letras.\n");
            }

            if ((strlen(clientes[totalClientes].cnpj) != 14))
            {
                printf("\nErro: O CNPJ deve ter exatamente 14 d�gitos. Tente "
                       "novamente.\n");
            }

        } while ((strcspn(clientes[totalClientes].cnpj,
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
                  strlen(clientes[totalClientes].cnpj)) ||
                 (strlen(clientes[totalClientes].cnpj) != 14));
    }
    return 1;
}
// imprimir RG(pessoa f�sica) ou inscri��o estadual(pessoa jur�dica)
int imprimirRGouInscricaoSocial()
{
    printf("-----------------------\n");
    if (clientes[totalClientes].tipoPessoa == 'F')
    {
        printf("RG: ");
        fgets(clientes[totalClientes].docRegistro,
              sizeof(clientes[totalClientes].docRegistro), stdin);
    }
    else if (clientes[totalClientes].tipoPessoa == 'J')
    {
        printf("Inscri��o estadual: ");
        fgets(clientes[totalClientes].docRegistro,
              sizeof(clientes[totalClientes].docRegistro), stdin);
    }
    else
    {
        printf("Um erro inesperado ocorreu!");
        return 0;
    }
    return 1;
}
// imprimir inscri��o municipal(pessoa jur�dica)

int imprimirinsMuniPj()
{ // Fun��o para receber o n�mero de
  // inscri��o munipal da empresa.
    printf("-----------------------\n");
    if (clientes[totalClientes].tipoPessoa == 'J')
    {
        printf("Inscri��o municipal (8 d�gitos):");

        // Rebece o n�mero da inscri��o munipal.
        int result = scanf("%14s", clientes[totalClientes].insmuniPJ);

        // Condi��o imposta para que o valor inserido n�o seja diferente de 8
        // d�gitos.
        if (result != 1 || strlen(clientes[totalClientes].insmuniPJ) != 8)
        {
            printf("-----------------------\n");
            printf("Campo digitado de forma inv�lida");
            printf("\n-----------------------\n");
            printf("Tente novamente: ");
            printf("\n-----------------------\n");

            // Limpa o buffer da informa��o inserida errado.
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }

            // Retorna ao in�cio da fun��o para nova tentativa.
            return imprimirinsMuniPj();
        }
    }
    else if (clientes[totalClientes].tipoPessoa == 'F')
    {
        return 0;
    }
    else
    {
        printf("Ocorreu um erro inesperado\n");
    }
    return 1;
}
// imprimir SUFRAMA(pessoa jur�dica)
int imprimirSUFRAMApj()
{ // Fun��o para receber o n�mero do SUFRAMA da empresa.
    printf("-----------------------\n");
    if (clientes[totalClientes].tipoPessoa == 'J')
    {
        printf("SUFRAMA (9 d�gitos):");

        // Recebe o n�mero do SUFRAMA.
        int result = scanf("%14s", clientes[totalClientes].suframaPJ);

        // Condi��o imposta para que o valor inserido n�o seja diferente de 9
        // d�gitos.
        if (result != 1 || strlen(clientes[totalClientes].suframaPJ) != 9)
        {
            printf("-----------------------\n");
            printf("Campo digitado de forma inv�lida");
            printf("\n-----------------------\n");
            printf("Tente novamente: ");
            printf("\n-----------------------\n");

            // Limpa o buffer da informa��o inserida errado.
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }

            // Retorna ao in�cio da fun��o para nova tentativa
            return imprimirSUFRAMApj();
        }
    }
    else if (clientes[totalClientes].tipoPessoa == 'F')
    {
        return 1;
    }
    else
    {
        printf("Ocorreu um erro inesperado\n");
    }
    return 1;
}
// imprimir CEP(ambos), Endere�o, n�mero, complemento

int isNumeric(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0; // N�o � completamente num�rico
        }
        str++;
    }
    return 1; // � completamente num�rico
}

int isValidEmail(const char *email)
{
    while (*email)
    {
        if (*email == '@')
        {
            return 1; // Cont�m '@', � um e-mail v�lido
        }
        email++;
    }
    return 0; // N�o cont�m '@', n�o � um e-mail v�lido
}

int isValidCEP(const char *cep) { return isNumeric(cep) && strlen(cep) == 8; }

void obterStringNaoVazia(const char *prompt, char *dest, int maxLength)
{
    do
    {
        printf("%s", prompt);
        fgets(dest, maxLength, stdin);
        dest[strcspn(dest, "\n")] = '\0'; // Remover o caractere de nova linha
    } while (dest[0] ==
             '\0'); // Continuar solicitando at� que a string n�o seja vazia
}

void obterCEPValido(const char *prompt, char *dest, int maxLength)
{
    obterStringNaoVazia(prompt, dest, maxLength);

    // Validar se o CEP � v�lido
    while (!isValidCEP(dest))
    {
        printf("-----------------------\n");
        printf("CEP invalido. Digite novamente (8 digitos numericos): \n");
        printf("-----------------------\n");
        obterStringNaoVazia(prompt, dest, maxLength);
    }
}

// Fun��o para obter uma resposta 'S' ou 'N'
char obterRespostaSN(const char *prompt)
{
    char resposta[MAX_LENGTH];

    do
    {
        obterStringNaoVazia(prompt, resposta, MAX_LENGTH);
        resposta[0] = toupper(resposta[0]); // Converte para mai�scula

        if (resposta[0] != 'S' && resposta[0] != 'N')
        {
            printf("-----------------------\n");
            printf("Resposta invalida. Digite 'S' para Sim ou 'N' para Nao: \n");
            printf("-----------------------\n");
        }
    } while (resposta[0] != 'S' && resposta[0] != 'N');

    return resposta[0];
}

void imprimirCEPeLocalidade()
{
    printf("-----------------------\n");

    // Solicitar ao usu�rio que insira o CEP
    obterCEPValido("CEP: ", clientes[totalClientes].cep, MAX_LENGTH);
    printf("-----------------------\n");

    // Solicitar ao usu�rio que insira o endere�o
    obterStringNaoVazia("Endereco: ", clientes[totalClientes].endereco,
                        MAX_LENGTH);
    printf("-----------------------\n");

    // Solicitar ao usu�rio que insira o n�mero
    obterStringNaoVazia("N�mero: ", clientes[totalClientes].numero, MAX_LENGTH);
    printf("-----------------------\n");

    // Solicitar ao usu�rio que insira o complemento
    obterStringNaoVazia("Complemento: ", clientes[totalClientes].complemento,
                        MAX_LENGTH);
}
// imprimir bairro, cidade, estado
void imprimirBairroCidadeEstado()
{

    do
    {
        printf("-----------------------\n");
        clientes[totalClientes].bairro[50] = '\0';

        printf("Digite o bairro: ");
        fgets(clientes[totalClientes].bairro,
              sizeof(clientes[totalClientes].bairro), stdin);
        clientes[totalClientes]
            .bairro[strcspn(clientes[totalClientes].bairro, "\n")] = '\0';

        if ((strlen(clientes[totalClientes].bairro) == 0))
        {
            printf("\nDigite o bairro: ");
            fgets(clientes[totalClientes].bairro,
                  sizeof(clientes[totalClientes].bairro), stdin);
            clientes[totalClientes]
                .bairro[strcspn(clientes[totalClientes].bairro, "\n")] = '\0';
        }

        if (strcspn(clientes[totalClientes].bairro, "0123456789") <
            strlen(clientes[totalClientes].bairro))
        {
            printf("O nome do bairro nao pode conter numeros.\n");
        }

    } while (strcspn(clientes[totalClientes].bairro, "0123456789") <
             strlen(clientes[totalClientes].bairro));

    do
    {
        printf("-----------------------\n");
        printf("Digite a cidade: ");
        fgets(clientes[totalClientes].cidade,
              sizeof(clientes[totalClientes].cidade), stdin);
        clientes[totalClientes]
            .cidade[strcspn(clientes[totalClientes].cidade, "\n")] = '\0';

        if (strcspn(clientes[totalClientes].cidade, "0123456789") <
            strlen(clientes[totalClientes].cidade))
        {
            printf("O nome da cidade nao pode conter numeros.\n");
        }

    } while (strcspn(clientes[totalClientes].cidade, "0123456789") <
             strlen(clientes[totalClientes].cidade));

    do
    {
        printf("-----------------------\n");
        printf("Digite o estado: ");
        fgets(clientes[totalClientes].estado,
              sizeof(clientes[totalClientes].estado), stdin);
        clientes[totalClientes]
            .estado[strcspn(clientes[totalClientes].estado, "\n")] =
            '\0'; // Remover o caractere de nova linha.

        if (strcspn(clientes[totalClientes].estado, "0123456789") <
            strlen(clientes[totalClientes].estado))
        {
            printf("O nome do estado nao pode conter numeros.\n");
        }

    } while (strcspn(clientes[totalClientes].estado, "0123456789") <
             strlen(clientes[totalClientes].estado));
}
// imprimir 3 campos para digitar o telefone
void imprimirTelefones()
{

    printf("-----------------------\n");

    do
    {
        printf("Telefone 1: ");
        scanf("%s", clientes[totalClientes].telefone1);

        if (strcspn(clientes[totalClientes].telefone1,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
            strlen(clientes[totalClientes].telefone1))
        {
            printf("O numero do telefone1 nao pode conter letras.\n");
        }

    } while (strcspn(clientes[totalClientes].telefone1,
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
             strlen(clientes[totalClientes].telefone1));
    do
    {
        printf("-----------------------\n");
        printf("Telefone 2: ");
        scanf("%s", clientes[totalClientes].telefone2);

        if (strcspn(clientes[totalClientes].telefone2,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
            strlen(clientes[totalClientes].telefone2))
        {
            printf("O numero do telefone2 nao pode conter letras.\n");
        }

    } while (strcspn(clientes[totalClientes].telefone2,
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
             strlen(clientes[totalClientes].telefone2));

    do
    {
        printf("-----------------------\n");
        printf("Telefone 3: ");
        scanf("%s", clientes[totalClientes].telefone3);

        if (strcspn(clientes[totalClientes].telefone3,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
            strlen(clientes[totalClientes].telefone3))
        {
            printf("O numero do telefone3 nao pode conter letras.\n");
        }

    } while (strcspn(clientes[totalClientes].telefone3,
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") <
             strlen(clientes[totalClientes].telefone3));
}
// imprimir contato(nome da pessoa que ir� atender)
int contemCaracteresNaoLetras(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)str[i]) && !isspace((unsigned char)str[i]))
        {
            return 1; // Retorna 1 se encontrar caracteres n�o-alfab�ticos
        }
    }
    return 0; // A string cont�m apenas letras e espa�os
}
void imprimirContato()
{
    printf("-----------------------\n");
    do
    {
        // Solicita ao usu�rio para digitar o nome
        printf("Contato: ");
        scanf("%s", clientes[totalClientes].contato);

        // Verifica se a string cont�m apenas letras e espa�os
        if (contemCaracteresNaoLetras(clientes[totalClientes].contato))
        {
            printf("Erro: Entrada inv�lida. Certifique-se de inserir apenas letras e "
                   "espa�os.\n");
        }
        else
        {
            break;
        }
    } while (1);
}
// imprimir funda��o(data de funda��o da empresa)
int validador(int dia, int mes, int ano)
{
    if (ano < 1800 || ano > 2100 || mes < 1 || mes > 12 || dia < 1 || dia > 31)
    {
        return 0;
    }

    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
    {
        return 0;
    }

    if (mes == 2)
    {
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
        {
            if (dia > 29)
            {
                return 0;
            }
        }
        else
        {
            if (dia > 28)
            {
                return 0;
            }
        }
    }

    return 1; // A data � v�lida
}

int imprimirData()
{
    printf("-----------------------\n");
    do
    {
        // Solicita ao usu�rio para digitar uma data
        printf("Digite a data (DD MM AAAA): ");
        if (scanf("%d %d %d", &clientes[totalClientes].dia,
                  &clientes[totalClientes].mes,
                  &clientes[totalClientes].ano) != 3)
        {
            printf("Erro: Formato de data inv�lido.\n");
            while (getchar() != '\n')
                ; // Limpa o buffer do teclado
        }
        else
        {
            while (getchar() != '\n')
                ; // Limpa o buffer do teclado
            // Verifica se a data � inv�lida
            if (!validador(clientes[totalClientes].dia, clientes[totalClientes].mes,
                           clientes[totalClientes].ano))
            {
                printf("Data inv�lida.\n");
            }
            else
            {
                break;
            }
        }
    } while (1);
    return 1;
}
// imprimir email, site e um checkbox indicando se o site est� ativo
void imprimirInfoDigital()
{
    // Solicitar ao usu�rio que insira o e-mail
    printf("-----------------------\n");
    obterStringNaoVazia("Email: ", clientes[totalClientes].email, MAX_LENGTH);

    // Validar se o e-mail cont�m '@'
    while (!isValidEmail(clientes[totalClientes].email))
    {
        printf("-----------------------\n");
        printf("Email invalido. Digite novamente: \n");
        printf("-----------------------\n");
        obterStringNaoVazia("Digite o email: ", clientes[totalClientes].email,
                            MAX_LENGTH);
    }
    printf("-----------------------\n");

    // Solicitar ao usu�rio que insira o site
    obterStringNaoVazia("Site: ", clientes[totalClientes].site, MAX_LENGTH);
    printf("-----------------------\n");

    // Solicitar ao usu�rio que indique se o site est� ativo
    clientes[totalClientes].siteAtivo =
        obterRespostaSN("O site esta ativo? (S para Sim, N para Nao): ");
}
// imprimir campo observa��o
void imprimirObservacao()
{
    printf("-----------------------\n");
    // L� a observa��o at� encontrar uma quebra de linha ou atingir o limite de
    // 99 caracteres
    printf("Digite a observacao: ");
    scanf("%99[^\n]",
          clientes[totalClientes]
              .observacaoUsuario); // L� a observa��o at� encontrar uma quebra de
                                   // linha ou atingir o limite de 99 caracteres
}

void cadastrarCliente()
{
    imprimirCodCliente();
    imprimirTipoPessoa();
    limparBuffer();
    imprimirDataAtual();
    imprimirIdentificacao();
    if (clientes[totalClientes].tipoPessoa == 'J')
        imprimirNomeFantasia();
    imprimirCpfCnpj();
    limparBuffer();
    imprimirRGouInscricaoSocial();
    if (clientes[totalClientes].tipoPessoa == 'J')
        imprimirinsMuniPj();
    if (clientes[totalClientes].tipoPessoa == 'J')
    {
        imprimirSUFRAMApj();
        limparBuffer();
    }
    imprimirCEPeLocalidade();
    imprimirBairroCidadeEstado();
    imprimirTelefones();
    imprimirContato();
    imprimirData();
    imprimirInfoDigital();
    imprimirObservacao();

    clientes[totalClientes].codCliente = clientes[totalClientes].codCliente;
    clientes[totalClientes].tipoPessoa = clientes[totalClientes].tipoPessoa;
    strcpy(clientes[totalClientes].identificacao,
           clientes[totalClientes].identificacao);

    if (clientes[totalClientes].tipoPessoa == 'J')
    {
        strcpy(clientes[totalClientes].nomeFantasia,
               clientes[totalClientes].nomeFantasia);
    }

    if (clientes[totalClientes].tipoPessoa == 'F')
    {
        strcpy(clientes[totalClientes].cpf, clientes[totalClientes].cpf);
    }
    else if (clientes[totalClientes].tipoPessoa == 'J')
    {
        strcpy(clientes[totalClientes].cnpj, clientes[totalClientes].cnpj);
    }

    strcpy(clientes[totalClientes].docRegistro,
           clientes[totalClientes].docRegistro);

    if (clientes[totalClientes].tipoPessoa == 'J')
    {
        strcpy(clientes[totalClientes].insmuniPJ,
               clientes[totalClientes].insmuniPJ);
        strcpy(clientes[totalClientes].suframaPJ,
               clientes[totalClientes].suframaPJ);
    }

    strcpy(clientes[totalClientes].cep, clientes[totalClientes].cep);
    strcpy(clientes[totalClientes].endereco, clientes[totalClientes].endereco);
    strcpy(clientes[totalClientes].numero, clientes[totalClientes].numero);
    strcpy(clientes[totalClientes].complemento,
           clientes[totalClientes].complemento);
    strcpy(clientes[totalClientes].bairro, clientes[totalClientes].bairro);
    strcpy(clientes[totalClientes].cidade, clientes[totalClientes].cidade);
    strcpy(clientes[totalClientes].estado, clientes[totalClientes].estado);
    strcpy(clientes[totalClientes].telefone1, clientes[totalClientes].telefone1);
    strcpy(clientes[totalClientes].telefone2, clientes[totalClientes].telefone2);
    strcpy(clientes[totalClientes].telefone3, clientes[totalClientes].telefone3);
    strcpy(clientes[totalClientes].contato, clientes[totalClientes].contato);
    clientes[totalClientes].dia = clientes[totalClientes].dia;
    clientes[totalClientes].mes = clientes[totalClientes].mes;
    clientes[totalClientes].ano = clientes[totalClientes].ano;
    strcpy(clientes[totalClientes].email, clientes[totalClientes].email);
    strcpy(clientes[totalClientes].site, clientes[totalClientes].site);
    clientes[totalClientes].siteAtivo = clientes[totalClientes].siteAtivo;
    strcpy(clientes[totalClientes].observacaoUsuario,
           clientes[totalClientes].observacaoUsuario);

    totalClientes++;
}

void listarClientesCadastrados()
{
    if (totalClientes == 0)
    {
        printf("\n-----------------------\n");
        printf("Nenhum cliente cadastrado ainda.\n");
        printf("-----------------------\n");
        return;
    }

    printf("Clientes cadastrados:\n");
    printf("-----------------------\n");

    for (int i = 0; i < totalClientes; i++)
    {
        printf("C�digo do cliente: %d\n", clientes[i].codCliente);
        printf("Tipo de pessoa: %c\n", clientes[i].tipoPessoa);
        printf("Identifica��o: %s\n", clientes[i].identificacao);

        if (clientes[i].tipoPessoa == 'J')
        {
            printf("Nome Fantasia: %s\n", clientes[i].nomeFantasia);
        }

        if (clientes[i].tipoPessoa == 'F')
        {
            printf("CPF: %s\n", clientes[i].cpf);
        }
        else if (clientes[i].tipoPessoa == 'J')
        {
            printf("CNPJ: %s\n", clientes[i].cnpj);
        }

        printf("RG/Inscri��o Social: %s\n", clientes[i].docRegistro);

        if (clientes[i].tipoPessoa == 'J')
        {
            printf("Inscri��o Municipal: %s\n", clientes[i].insmuniPJ);
            printf("SUFRAMA: %s\n", clientes[i].suframaPJ);
        }

        printf("CEP: %s\n", clientes[i].cep);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("N�mero: %s\n", clientes[i].numero);
        printf("Complemento: %s\n", clientes[i].complemento);
        printf("Bairro: %s\n", clientes[i].bairro);
        printf("Cidade: %s\n", clientes[i].cidade);
        printf("Estado: %s\n", clientes[i].estado);
        printf("Telefone 1: %s\n", clientes[i].telefone1);
        printf("Telefone 2: %s\n", clientes[i].telefone2);
        printf("Telefone 3: %s\n", clientes[i].telefone3);
        printf("Contato: %s\n", clientes[i].contato);
        printf("Data: %d/%d/%d\n", clientes[i].dia, clientes[i].mes,
               clientes[i].ano);
        printf("Email: %s\n", clientes[i].email);
        printf("Site: %s\n", clientes[i].site);
        printf("Site Ativo: %c\n", clientes[i].siteAtivo);
        printf("Observa��o: %s\n", clientes[i].observacaoUsuario);

        printf("-----------------------\n");
    }
}

void deletarUltimoCliente()
{
    if (totalClientes > 0)
    {
        totalClientes--;
        printf("Cliente removido com sucesso!\n");
    }
    else
    {
        printf("N�o h� clientes para remover.\n");
    }
}

void exibirMenu()
{
    int opcao;

    do
    {
        printf("\n-----------------------\n");
        printf("MENU\n");
        printf("1. Cadastrar novo cliente\n");
        printf("2. Listar clientes cadastrados\n");
        printf("3. Apagar �ltimo cadastro\n");
        printf("4. Encerrar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            listarClientesCadastrados();
            break;
        case 3:
            deletarUltimoCliente();
            break;
        case 4:
            printf("Encerrando o menu...\n");
            return;
        default:
            printf("Opcao invalida. Escolha uma opcao valida.\n");
            break;
        }
    } while (1);
}