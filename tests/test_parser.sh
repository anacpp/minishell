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

# Combinações de redirecionamento inválidas com '&'
run_test "echo >&" "minishell: syntax error near unexpected token \`&'" "Redirecionamento inválido >&"
run_test "echo <&" "minishell: syntax error near unexpected token \`&'" "Redirecionamento inválido <&"
run_test "ls &" "minishell: syntax error near unexpected token \`&'" "Operador de background &"
run_test "ls >&2" "minishell: syntax error near unexpected token \`&'" "Redirecionamento de descritor >&2"

# Redirecionamento ambíguo
run_test "echo hi > \"\"" "minishell: ambiguous redirect" "Redirecionamento para filename vazio (aspas duplas)"
run_test "echo hi > ''" "minishell: ambiguous redirect" "Redirecionamento para filename vazio (aspas simples)"
run_test "cat < ''" "minishell: ambiguous redirect" "Redirecionamento de entrada de filename vazio"

# Aspas não fechadas
run_test "echo \"hello" "minishell: syntax error: unclosed quotes" "Citação dupla aberta"
run_test "echo 'world" "minishell: syntax error: unclosed quotes" "Citação simples aberta"

# Operadores inválidos
run_test "ls && pwd" "minishell: syntax error: unsupported operator" "Operador &&"
run_test "ls || pwd" "minishell: syntax error: unsupported operator" "Operador ||"

# --- Combinações de Operadores de Redirecionamento ---
# Testa o que acontece quando diferentes operadores de redirecionamento são colocados em sequência.
run_test "ls > <" "minishell: syntax error near unexpected token \`<'" "Redir de saída seguido por redir de entrada"
run_test "ls < >" "minishell: syntax error near unexpected token \`>'" "Redir de entrada seguido por redir de saída"
run_test "ls >> <" "minishell: syntax error near unexpected token \`<'" "Append seguido por redir de entrada"
run_test "ls << >" "minishell: syntax error near unexpected token \`>'" "Heredoc seguido por redir de saída"

# --- Operadores Imediatamente Após Nomes de Arquivo ---
# Um pipe ou outro operador não pode seguir um redirecionamento sem um comando entre eles.
run_test "> out.txt | wc" "minishell: syntax error near unexpected token \`|'" "Pipe após um redirecionamento de arquivo"
run_test "< in.txt > out.txt |" "minishell: syntax error near unexpected token \`|'" "Pipe após múltiplos redirecionamentos"


# --- Casos de Borda com Here-document ---
# O delimitador de um here-document não pode ser um operador.
run_test "cat << |" "minishell: syntax error near unexpected token \`|'" "Heredoc com pipe como delimitador"
run_test "cat << >" "minishell: syntax error near unexpected token \`>'" "Heredoc com redir como delimitador"
run_test "cat << <" "minishell: syntax error near unexpected token \`<'" "Heredoc com redir de entrada como delimitador"

# --- Outros Casos de Sintaxe Inválida ---
# Garante que o parser não se confunda com múltiplos redirecionamentos sem um comando válido.
run_test "> out1 > out2" "minishell: missing command" "Múltiplos redirs de saída sem comando"

summary_and_exit
