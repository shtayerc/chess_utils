# CHESS UTILS

Chess library for C/C++

### FEATURES
- FEN board import/export
- UCI, SAN move validation
- Move notation with sub variations and comments
- PGN read/write

### EXAMPLE USAGE

```c
#define CHESS_UTILS_IMPLEMENTATION
#include "chess_utils.h"
```

```c
Board b;
board_fen_import(&b, FEN_DEFAULT);

Notation n;
notation_init(&n, &b);
notation_tag_set(&n, "White", "New game");

const char *san = "e4";
Status status;
Square src, dst;
Piece prom_piece;
status = board_move_san_status(&b, san, &src, &dst, &prom_piece);
if(status != Invalid){
    board_move_do(&b, src, dst, prom_piece, status);
    variation_move_add(n.line_current, src, dst, prom_piece, &b, san);
    FILE *f = fopen("new_game.pgn", "w");
    pgn_write_file(f, &n);
    fclose(f);
}else{
    printf("Invalid move\n");
}
notation_free(&n);
```

```c
Notation n;
Board b;
notation_init(&n, &b);
FILE *f = fopen("games.pgn", "r");
pgn_read_file(&n, f, 1); //read second game to notation
fclose(f);
notation_free(&n);
```

### RUN TESTS
Requires `valgrind g++`
```
cd tests
make check clean
```
