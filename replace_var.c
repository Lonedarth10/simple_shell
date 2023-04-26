#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: inputs string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int rows, charc, i, lnkval;
	char **_envr;

	_envr = data->_environ;
	for (rows = 0; _envr[row]; rows++)
	{
		for (i = 1, charc = 0; _envr[rows][charc]; charc++)
		{
			if (_envr[rows][charc] == '=')
			{
				lnkval = _strlen(_envr[rows] + charc + 1);
				add_rvar_node(h, i, _envr[rows] + charc + 1, lnkval);
				return;
			}

			if (in[i] == _envr[rows][charc])
				i++;
			else
				break;
		}
	}

	for (i = 0; in[i]; i++)
	{
		if (in[i] == ' ' || in[i] == '\t' || in[i] == ';' || in[i] == '\n')
			break;
	}

	add_rvar_node(h, i, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int j, lst, lpid;

	lst = _strlen(st);
	lpid = _strlen(data->pid);

	for (j = 0; in[j]; j++)
	{
		if (in[j] == '$')
		{
			if (in[j + 1] == '?')
				add_rvar_node(h, 2, st, lst), j++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpid), j++;
			else if (in[j + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + j, data);
		}
	}

	return (j);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}

