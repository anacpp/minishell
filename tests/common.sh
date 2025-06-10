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

# Cores
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASSED_COUNT=0
FAILED_COUNT=0
TMP_STDERR="stderr.tmp"

run_test() {
    COMMAND=$1
    EXPECTED_ERROR=$2
    TEST_NAME=$3

    "$PROJECT_ROOT/minishell" <<< "$COMMAND" > /dev/null 2> "$TMP_STDERR"
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

summary_and_exit() {
    echo -e "\n${YELLOW}--- 🏁 Testes Finalizados ---${NC}"
    echo -e "Resultados: ${GREEN}${PASSED_COUNT} Aprovados${NC}, ${RED}${FAILED_COUNT} Reprovados${NC}\n"
    rm -f "$TMP_STDERR"
    if [ $FAILED_COUNT -ne 0 ]; then
        exit 1
    fi
    exit 0
}
