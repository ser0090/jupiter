#include <stdio.h>
#include "board.h"
#include "generation.h"
#include "evaluation.h"
#include "notation.h"
#include "engine.h"
#include "node.h"
#include "delay.h"
#include "search.h"
#include "fen.h"
#include "logging.h"
#include <omp.h>

static void (*log_func)(const char *info) = NULL;

typedef struct {
    char mov[NOTATION_STR_LEN];
    uint32_t nodes_count;
    uint32_t score;
    uint32_t nps;
    uint32_t time;
} engine_info_t;

static void generate_nodes(Node_t *node)
{
    Node_t *aux = node;

    while(aux != NULL) {

        if (aux->child != NULL) {
            #pragma omp task
            generate_nodes(aux->child);
        } else {
            #pragma omp task
            get_moves(aux);
        }

        aux = aux->next;
    }
}

static engine_info_t engine_think(Node_t *node)
{
    engine_info_t info;
    double start_time,total_time,gen_time,best_move_time;

    start_time = omp_get_wtime();
    #pragma omp parallel
    {
<<<<<<< Updated upstream
        #pragma omp single
        generate_nodes(node); // paralelizar aca
    }
=======
      #pragma omp single
      generate_nodes(node); // paralelizar aca
      #pragma omp barrier

      #pragma omp single
>>>>>>> Stashed changes
      gen_time = omp_get_wtime();

      #pragma omp single
      get_best_move(node, info.mov); // paralelizar aca
    }
//      #pragma omp taskwait
      best_move_time = omp_get_wtime();
//    }
    total_time = best_move_time-start_time;

    info.time = (uint32_t) (1000 * total_time);//clock_diff_ms(end, start);
    info.nodes_count = get_tree_count(node) - 1;
    if (info.time > 0) {
        info.nps = (info.nodes_count * 1000) / info.time;
    } else {
        info.nps = 0;
    }


    printf("\n  tiempo total: %f \n    tiempo de generar: %f   %f\n    tiempo de busqueda: %f   %f\n",
                    total_time, gen_time-start_time ,100.0*(gen_time-start_time)/total_time,
                    best_move_time-gen_time,100.0*(best_move_time-gen_time)/total_time);

    return info;
}

static bool keep_running(engine_cfg_t cfg, uint32_t elapsed_time, uint8_t current_depth)
{
    if (cfg.mode == ENGINE_INFINITE) {
        //ask for command stop
    }
    if (cfg.mode == ENGINE_TIME) {
        if ((cfg.data.time / 5) < elapsed_time) {
            return false;
        }
    }
    if (cfg.mode == ENGINE_DEPTH) {
        if (current_depth >= cfg.data.depth) {
            return false;
        }
    }

    return true;
}

static void log_info(engine_info_t info, uint8_t depth, uint32_t elapsed_time)
{
    char msg[1000];

    if (log_func != NULL) {
        sprintf(msg, "INFO: depth %d score cp %d time %d[ms] nodes %d nps %d",
              depth, info.score, elapsed_time, info.nodes_count,
              info.nps);
        log_func(msg);
    }
}

void engine_set_log_func(void *func)
{
    log_func = func;
}

char* engine_go(Node_t *node, engine_cfg_t cfg)
{
    static engine_info_t info;
    uint32_t elapsed_time = 0;
    uint8_t current_depth = 0;

    char fen[MAX_FEN_LEN];
    get_fen_from_node(node, fen);
    LOG2(DEBUG, "Board: ", fen);

    while (keep_running(cfg, elapsed_time, current_depth)) {
        info = engine_think(node);
        current_depth++;
        elapsed_time += info.time;
        log_info(info, current_depth, elapsed_time);
    }

    delete_node(node);
    return info.mov;
}
