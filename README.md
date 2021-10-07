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
Game g;
game_init(&g, NULL); //NULL means default starting position
game_tag_set(&g, "White", "New game");

const char *san = "e4";
Status status;
Square src, dst;
Piece prom_piece;
status = game_move_san_status(&g, san, &src, &dst, &prom_piece);
if(status != Invalid){
    game_move_add(&g, src, dst, prom_piece, status);
    FILE *f = fopen("new_game.pgn", "w");
    pgn_write_file(f, &g);
    fclose(f);
}else{
    printf("Invalid move\n");
}
game_free(&g);
```

```c
Game g;
game_init(&g, NULL);
FILE *f = fopen("files/game_list.pgn", "r");
pgn_read_file(f, &g, 1); //read second game to game
fclose(f);
game_free(&g);
```

### RUN TESTS
Requires `valgrind g++` (option valgrind)
```
cd tests
make check clean
make valgrind clean
```
