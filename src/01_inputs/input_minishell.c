#include <minishell.h>

int	input_syntax(const char *input)
{
	if (!*input)
		handle_error(NULL, NULL, 1);
	//função que verifica se o input esta entre aspas duplas ou simples, se tiver as regras abaixo não se aplicarão; sairá da função;
	
	if (missaligned_operators(*input) == 1)
	{
		//perror
	}
	else if (unsupported_operators(input) == 1)
	{
		//perror
	}
	else if (/* função da raquel de aspas duplas e simples*/)
	{
		//perror
	}
	else if (/* função da raquel de redirect mal formatado*/)
	{
		//perror
	}
		
}

static int unsupported_operators(const char *input)
{

}

static int missaligned_operators(const char *input)
{

}

// Função da Raquel 03
// Função da Raquel 04

//as funções abaixo irão para o utils.c

int is_btw_quotes(const char *input)
{

}
