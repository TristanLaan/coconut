#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast/ast.h"
#include "commandline.h"
#include "lib/color.h"
#include "lib/errors.h"
#include "ast/ast.h"
#include "ast/check.h"
#include "pretty/printer.h"

#include "filegen/driver.h"
#include "filegen/gen-ast.h"
#include "filegen/gen-enum.h"

// Defined in the parser.
extern struct Config *parseDSL(FILE *fp);
extern char *yy_filename;

void exit_compile_error(void) {
    PRINT_COLOR(MAGENTA);
    fprintf(stderr, "Errors where found, code generation terminated.\n");
    PRINT_COLOR(RESET_COLOR);
    exit(INVALID_CONFIG);
}

int main(int argc, char *argv[]) {
    process_commandline_args(argc, argv);
    FILE *f = fopen(yy_filename, "r");
    Config *config = parseDSL(f);
    if (check_config(config)) {
        exit_compile_error();
    }

    filegen_init(config, false);
    filegen_dir("cocogen/framework/generated/");
    filegen_generate("enum.h", gen_enum_header);
    filegen_generate("ast.h", gen_ast_header);
    filegen_generate("ast.c", gen_ast_src);
}