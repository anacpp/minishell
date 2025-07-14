#!/bin/bash
source "$(dirname "$0")/common.sh"

echo -e "\n${YELLOW}--- 🛠️  Iniciando Testes de Built-ins (Realistas) ---${NC}"

# --- Testes para 'echo' (Stateless, funciona como antes) ---
echo -e "\n${YELLOW}--- Testando 'echo' ---${NC}"
run_test_stdout "echo hello world" "hello world\n" "echo simples"
run_test_stdout "echo -n hello" "hello" "echo com flag -n"
run_test_stdout "echo '  hello   world  '" "  hello   world  \n" "echo com múltiplos espaços e aspas"
run_test_stdout "echo" "\n" "echo sem argumentos"

# --- Testes para 'pwd' (Stateless, funciona como antes) ---
echo -e "\n${YELLOW}--- Testando 'pwd' ---${NC}"
EXPECTED_PWD=$(pwd)
run_test_stdout "pwd" "$EXPECTED_PWD\n" "pwd simples"

# --- Testes para 'cd' (Testa erros e sucesso, sem verificar a mudança de diretório) ---
echo -e "\n${YELLOW}--- Testando 'cd' ---${NC}"
run_test "cd non_existent_dir_12345" "minishell: cd: non_existent_dir_12345: No such file or directory" "cd para diretório inexistente"
touch a_file_for_testing
run_test "cd a_file_for_testing" "minishell: cd: a_file_for_testing: Not a directory" "cd para um arquivo"
rm a_file_for_testing
run_test_stdout "cd .." "" "cd para diretório válido (sem saída)"

# --- Testes para 'env' ---
echo -e "\n${YELLOW}--- Testando 'env' ---${NC}"
run_test_stdout_contains "env" "PATH=" "env deve conter a variável PATH"
run_test "env com_argumento" "minishell: env: com_argumento: No such file or directory" "env com argumentos deve falhar"

# --- Testes para 'export' ---
echo -e "\n${YELLOW}--- Testando 'export' ---${NC}"
run_test_stdout_contains "export" "declare -x" "export sem argumentos"
run_test "export 1inválido" "minishell: export: \`1inválido': not a valid identifier" "export com identificador inválido"
run_test_stdout "export VARIAVEL_VALIDA=1" "" "export com sintaxe válida (sem saída)"

# --- Testes para 'unset' ---
echo -e "\n${YELLOW}--- Testando 'unset' ---${NC}"
run_test "unset 1inválido" "minishell: unset: \`1inválido': not a valid identifier" "unset com identificador inválido"
run_test_stdout "unset VARIAVEL_VALIDA" "" "unset com sintaxe válida (sem saída)"

# --- Testes para 'exit' ---
echo -e "\n${YELLOW}--- Testando 'exit' ---${NC}"
run_test "exit a b c" "minishell: exit: too many arguments" "exit com muitos argumentos"
run_test "exit not_a_number" "minishell: exit: not_a_number: numeric argument required" "exit com argumento não numérico"

summary_and_exit
