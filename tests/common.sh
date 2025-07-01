#!/bin/bash

# Compila o minishell
PROJECT_ROOT="$(dirname "$(dirname "$0")")"
if [ ! -f "$PROJECT_ROOT/minishell" ]; then
    echo "⚠️  Executável 'minishell' não encontrado. Compilando..."
    (cd "$PROJECT_ROOT" && make --silent)
    if [ $? -ne 0 ]; then
        echo "❌ Falha na compilação. Abortando testes."
        exit 1
    fi
    echo "✅ Compilação concluída."
fi

# --- Lógica do Valgrind ---
VALGRIND_CMD=""
if [[ "$USE_VALGRIND" == "1" || "$USE_VALGRIND" == "true" ]]; then
    echo -e "${YELLOW}VALGRIND ATIVADO!${NC} Os testes serão mais lentos."
    # NOVA LINHA: Redireciona a saída do Valgrind para seu próprio arquivo de log.
    VALGRIND_LOG_FILE="valgrind_report.log"
    # --log-file=... é a correção chave.
    VALGRIND_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$PROJECT_ROOT/tests/readline.supp --log-file=$VALGRIND_LOG_FILE"
fi
# --- Fim da Lógica do Valgrind ---

# Cores
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASSED_COUNT=0
FAILED_COUNT=0
TMP_STDERR="stderr.tmp"
TMP_STDOUT="stdout.tmp" #

run_test() {
    COMMAND=$1
    EXPECTED_ERROR=$2
    TEST_NAME=$3

    $VALGRIND_CMD "$PROJECT_ROOT/minishell" <<< "$COMMAND" > /dev/null 2> "$TMP_STDERR"
    ACTUAL_ERROR=$(head -n 1 "$TMP_STDERR")

    if [[ "$ACTUAL_ERROR" == "$EXPECTED_ERROR" ]]; then
        echo -e "${GREEN}✅ PASS:${NC} $TEST_NAME"
        ((PASSED_COUNT++))
    else
        echo -e "${RED}❌ FAIL:${NC} $TEST_NAME"
        echo -e "  Comando:  \"$COMMAND\""
        echo -e "  Esperado: \"$EXPECTED_ERROR\""
        echo -e "  Recebido: \"$ACTUAL_ERROR\""
        ((FAILED_COUNT++))
    fi
}

# NOVA FUNÇÃO: Testa se a saída padrão (stdout) é exatamente a esperada
run_test_stdout() {
    COMMAND=$1
    EXPECTED_STDOUT=$2
    TEST_NAME=$3

    $VALGRIND_CMD "$PROJECT_ROOT/minishell" <<< "$COMMAND" > "$TMP_STDOUT" 2> "$TMP_STDERR"
    ACTUAL_STDOUT=$(cat "$TMP_STDOUT")

    if [[ "$ACTUAL_STDOUT" == "$EXPECTED_STDOUT" ]]; then
        echo -e "${GREEN}✅ PASS:${NC} $TEST_NAME"
        ((PASSED_COUNT++))
    else
        echo -e "${RED}❌ FAIL:${NC} $TEST_NAME"
        echo -e "  Comando:      \"$COMMAND\""
        echo -e "  Esperado:     \"$EXPECTED_STDOUT\""
        echo -e "  Recebido:     \"$ACTUAL_STDOUT\""
        echo -e "  Erro (stderr): \"$(cat $TMP_STDERR)\""
        ((FAILED_COUNT++))
    fi
}

# NOVA FUNÇÃO: Testa se a saída padrão (stdout) contém uma substring
run_test_stdout_contains() {
    COMMAND=$1
    EXPECTED_SUBSTRING=$2
    TEST_NAME=$3

    $VALGRIND_CMD "$PROJECT_ROOT/minishell" <<< "$COMMAND" > "$TMP_STDOUT" 2> /dev/null
    ACTUAL_STDOUT=$(cat "$TMP_STDOUT")

    if [[ "$ACTUAL_STDOUT" == *"$EXPECTED_SUBSTRING"* ]]; then
        echo -e "${GREEN}✅ PASS:${NC} $TEST_NAME"
        ((PASSED_COUNT++))
    else
        echo -e "${RED}❌ FAIL:${NC} $TEST_NAME"
        echo -e "  Comando:               \"$COMMAND\""
        echo -e "  Substring Esperada:    \"$EXPECTED_SUBSTRING\""
        echo -e "  Saída Recebida:        \"$ACTUAL_STDOUT\""
        ((FAILED_COUNT++))
    fi
}


summary_and_exit() {
    echo -e "\n${YELLOW}--- 🏁 Testes Finalizados ---${NC}"
    echo -e "Resultados: ${GREEN}${PASSED_COUNT} Aprovados${NC}, ${RED}${FAILED_COUNT} Reprovados${NC}\n"
    # Adicionado VALGRIND_LOG_FILE para limpeza
    rm -f "$TMP_STDERR" "$TMP_STDOUT" "$VALGRIND_LOG_FILE"
    if [ $FAILED_COUNT -ne 0 ]; then
        exit 1
    fi
    exit 0
}
