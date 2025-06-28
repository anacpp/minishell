#!/bin/bash
source "$(dirname "$0")/common.sh"

echo -e "\n${YELLOW}--- 🛠️  Iniciando Testes de Built-ins ---${NC}"

# --- Testes para 'echo' ---
run_test_stdout "echo hello world" "hello world" "echo simples"
run_test_stdout "echo -n hello" "hello" "echo com flag -n"
run_test_stdout "echo '  hello   world  '" "  hello   world  " "echo com múltiplos espaços e aspas"
run_test_stdout "echo" "" "echo sem argumentos"

# --- Testes para 'pwd' ---
EXPECTED_PWD=$(pwd)
run_test_stdout "pwd" "$EXPECTED_PWD" "pwd simples"

# --- Testes para 'env', 'export' e 'unset' ---
# Testa se a variável de ambiente é definida e visível com 'env'
run_test_stdout_contains 'export MINISHELL_TEST_VAR=success && env' 'MINISHELL_TEST_VAR=success' 'export e env'

# Testa se 'unset' remove a variável
export MINISHELL_TEMP_VAR=to_be_deleted
run_test_stdout 'unset MINISHELL_TEMP_VAR; env' '' 'unset de variável'


summary_and_exit
