#!/bin/bash
source "$(dirname "$0")/common.sh"

echo -e "\n${YELLOW}--- 🔎 Iniciando Testes de Parser (Sintaxe) ---${NC}"

# Pipes inválidos
run_test "|" "minishell: syntax error near unexpected token \`|'" "Pipe no início"
run_test "ls | | wc" "minishell: syntax error near unexpected token \`|'" "Pipes consecutivos"
run_test "ls |" "minishell: syntax error near unexpected token \`|'" "Pipe no final"

# Redirecionamentos malformados
run_test ">" "minishell: syntax error near unexpected token \`newline'" "Redir de saída sem arquivo"
run_test "<" "minishell: syntax error near unexpected token \`newline'" "Redir de entrada sem arquivo"
run_test ">>" "minishell: syntax error near unexpected token \`newline'" "Append sem arquivo"
run_test "ls > >" "minishell: syntax error near unexpected token \`>'" "Redirs de saída consecutivos"
run_test "ls < <" "minishell: syntax error near unexpected token \`<'" "Redirs de entrada consecutivos"
run_test "ls > |" "minishell: syntax error near unexpected token \`|'" "Redir seguido de pipe"
run_test "< |" "minishell: syntax error near unexpected token \`|'" "Redir entrada seguido de pipe"

# Testes com espaços após redirecionamento (inválidos)
run_test "ls > " "minishell: syntax error near unexpected token \`newline'" "Redir com espaço e sem arquivo"
run_test "ls < " "minishell: syntax error near unexpected token \`newline'" "Redir entrada com espaço e sem arquivo"

# Heredoc malformado
run_test "cat <<" "minishell: syntax error near unexpected token \`newline'" "Heredoc sem delimitador"

# Aspas não fechadas
run_test "echo \"hello" "minishell: syntax error: unclosed quotes" "Citação dupla aberta"
run_test "echo 'world" "minishell: syntax error: unclosed quotes" "Citação simples aberta"

# Operadores inválidos
run_test "ls && pwd" "minishell: syntax error: unsupported operator" "Operador &&"
run_test "ls || pwd" "minishell: syntax error: unsupported operator" "Operador ||"

summary_and_exit
