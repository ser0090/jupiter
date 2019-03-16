#include <stdio.h>
#include <string.h>
#include "notation.h"
#include "board.h"
#include "logging.h"

static int32_t get_minimax(Node_t *node)
{
    Node_t *aux = node->child;
    int32_t minmax = -10000 * node->turn;

    while (aux != NULL) {
        if ((node->turn == BLACK && aux->value < minmax) ||
            (node->turn == WHITE && aux->value > minmax)) {
            minmax = aux->value;
        }
        aux = aux->next;
    }

    return minmax;
}

static void search(Node_t *root)
{
    Node_t *aux = root;

    while(aux != NULL) {
        if (aux->child != NULL) {
            if (aux->child->child == NULL) {

#pragma omp task firstprivate(aux)
                aux->value = get_minimax(aux);
            } else {
#pragma omp task depend(out: aux) firstprivate(aux)
                search(aux->child);
#pragma omp task  depend(in: aux) firstprivate(aux)
                aux->value = get_minimax(aux);
            }
        }
        aux = aux->next;
    }
    #pragma omp taskwait
}

static retval_t get_move(Node_t *node, char *move)
{
    Node_t *aux = node->child;
    int32_t score = node->value;

    while (aux->value != score && aux != NULL) {
        aux = aux->next;
    }

    if (aux == NULL) {
        memset(move, 0x0, NOTATION_STR_LEN);
        return RV_ERROR;
    }
    strncpy(move, aux->notation, NOTATION_STR_LEN);
    return RV_SUCCESS;
}

void get_best_move(Node_t *node, char *move)
{
    search(node);
    get_move(node, move);
}
