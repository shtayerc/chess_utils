#include <assert.h>
#define CHESS_UTILS_IMPLEMENTATION
#include "../chess_utils.h"

void
test_strtok_r()
{
    char str[100];
    char *tok, *saveptr;
    snprintf(str, 100, "Test strtok_r string");
    tok = strtok_r(str, " ", &saveptr);
    assert(!strcmp(tok, "Test"));

    tok = strtok_r(NULL, " ", &saveptr);
    assert(!strcmp(tok, "strtok_r"));

    tok = strtok_r(NULL, " ", &saveptr);
    assert(!strcmp(tok, "string"));

    tok = strtok_r(NULL, " ", &saveptr);
    assert(tok == NULL);
}

void
test_concate()
{
    char str[100];
    snprintf(str, 100, "Begining");
    concate(str, 100, " middle");
    concate(str, 100, " %d", 10);
    assert(!strcmp(str, "Begining middle 10"));
}

void
test_trimmove()
{
    char san[10];
    snprintf(san, 10, "Nxf3+");
    trimmove(san);
    assert(!strcmp(san, "Nf3"));

    snprintf(san, 10, "Dxd5");
    trimmove(san);
    assert(!strcmp(san, "Dd5"));

    snprintf(san, 10, "Kf3");
    trimmove(san);
    assert(!strcmp(san, "Kf3"));

    san[0] = '\0';
    trimmove(san);
    assert(!strcmp(san, ""));

    snprintf(san, 10, "+");
    trimmove(san);
    assert(!strcmp(san, ""));

    snprintf(san, 10, "g8++");
    trimmove(san);
    assert(!strcmp(san, "g8"));
}

void
test_trimendl()
{
    char str[10];
    snprintf(str, 10, "Line\r\n");
    trimendl(str);
    assert(!strcmp(str, "Line"));
}

void
test_trimcomment()
{
    char comment[COMMENT_LEN];
    snprintf(comment, COMMENT_LEN, " {Dominguez Perez,L (2750)-Leko,P (2674) IMSA World Masters Blitz 2019 (6.2) 1/2-1/2})");
    trimcomment(comment);
    assert(!strcmp(comment, "Dominguez Perez,L (2750)-Leko,P (2674) IMSA World Masters Blitz 2019 (6.2) 1/2-1/2"));
}

void
test_charremove()
{
    char str[10];
    snprintf(str, 10, "Trest");
    charremove(str, 1);
    assert(!strcmp(str, "Test"));
}

void
test_charcount()
{
    assert(charcount("This is test string", 'i') == 3);
}

void
test_charcount_before()
{
    assert(charcount_before("Text before (text after", 'e', '(') == 3);
}

void
test_charcount_after()
{
    assert(charcount_after("Text before (text after", 'e', '(') == 2);
}

void
test_str_is_move()
{
    assert(!str_is_move(")"));
    assert(!str_is_move(""));
    assert(str_is_move("e4"));
    assert(str_is_move("Nf3+"));
}

void
test_str_is_square()
{
    assert(str_is_square("a4"));
    assert(!str_is_square("a0"));
}

void
test_str_is_fen()
{
    assert(!str_is_fen(""));
    assert(str_is_fen(FEN_DEFAULT));
    assert(str_is_fen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq -"));
    assert(str_is_fen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w Kq -"));
    assert(!str_is_fen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w Kd -"));
    assert(!str_is_fen("rnbq1bnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQ1BNR w KQkq -"));
    assert(!str_is_fen("rnbqkbn2/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq -"));
}

void
test_tag_extract()
{
    Tag tag;
    int ok;

    ok = tag_extract("[White \"Morphy, Paul\"]", &tag);
    assert(ok && !strcmp(tag.key, "White") && !strcmp(tag.value, "Morphy, Paul"));
}

void
test_tag_escape_value()
{
    char str[100];
    tag_escape_value("Quote \"", str, 100);
    assert(!strcmp(str, "Quote \\\""));

    tag_escape_value("\"\"\"", str, 5);
    assert(strlen(str) == 0);
}

void
test_filerank2square()
{
    Square sq;
    sq = filerank2square(File_a, Rank_1);
    assert(sq == a1);

    sq = filerank2square(File_h, Rank_8);
    assert(sq == h8);
}

void
test_square2rank()
{
    assert(square2rank(a8) == Rank_8);
    assert(square2rank(b1) == Rank_1);
}

void
test_square2file()
{
    assert(square2file(a8) == File_a);
    assert(square2file(h7) == File_h);
}

void
test_char2rank()
{
    assert(char2rank('8') == Rank_8);
    assert(char2rank('1') == Rank_1);
}

void
test_char2file()
{
    assert(char2file('a') == 0);
    assert(char2file('h') == 7);
}

void
test_char2piece()
{
    assert(char2piece('p') == BlackPawn);
    assert(char2piece('N') == WhiteKnight);
}

void
test_rank2char()
{
    assert(rank2char(Rank_8) == '8');
    assert(rank2char(Rank_1) == '1');
}

void
test_file2char()
{
    assert(file2char(File_a) == 'a');
    assert(file2char(File_h) == 'h');
}

void
test_piece2char()
{
    assert(piece2char(WhitePawn) == 'P');
    assert(piece2char(BlackKing) == 'k');
}

void
test_move_offset_find()
{
    assert(move_offset_find(h1, h4, OffsetRook) == -16);
    assert(move_offset_find(f1, c4, OffsetBishop) == -17);
}

void
test_move_uci_export()
{
    int UCI_LEN = 6;
    char uci[UCI_LEN];
    move_uci_export(e2, e4, Empty, uci, UCI_LEN);
    assert(!strcmp("e2e4", uci));

    move_uci_export(g7, g8, BlackQueen, uci, UCI_LEN);
    assert(!strcmp("g7g8Q", uci));
}

void
test_board_square_piece_color()
{
    Board b;
    board_fen_import(&b, FEN_DEFAULT);
    assert(board_square_piece_color(&b, h1) == White);
    assert(board_square_piece_color(&b, a8) == Black);
    assert(board_square_piece_color(&b, e4) == NoColor);
}

void
test_board_square_set()
{
    Board b;
    board_fen_import(&b, FEN_DEFAULT);
    board_square_set(&b, a1, Empty);
    assert(b.position[a1] == Empty);
}

void
test_board_square_is_attacked()
{
    Board b;
    board_fen_import(&b, "r7/2bn2P1/5N2/1k3p2/8/3K2B1/R7/2Q4q w - - 0 1");

    assert(board_square_is_attacked(&b, d7, White));
    assert(board_square_is_attacked(&b, d6, White));
    assert(board_square_is_attacked(&b, a8, White));
    assert(board_square_is_attacked(&b, c6, White));
    assert(board_square_is_attacked(&b, f8, White));
    assert(board_square_is_attacked(&b, h8, White));
    assert(!board_square_is_attacked(&b, h3, White));
    assert(!board_square_is_attacked(&b, f5, White));
    assert(!board_square_is_attacked(&b, c8, White));
    assert(!board_square_is_attacked(&b, b8, White));
    assert(board_square_is_attacked(&b, d4, White));
    assert(board_square_is_attacked(&b, g4, Black));
    assert(board_square_is_attacked(&b, e4, Black));
    assert(board_square_is_attacked(&b, f6, Black));
    assert(board_square_is_attacked(&b, g3, Black));
    assert(board_square_is_attacked(&b, c1, Black));
    assert(board_square_is_attacked(&b, a3, Black));
    assert(board_square_is_attacked(&b, b4, Black));
}

void
test_board_is_check()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/ppp1pppp/8/1B1p4/4P3/8/PPPP1PPP/RNBQK1NR b KQkq - 1 2");
    assert(board_is_check(&b));

    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
    assert(!board_is_check(&b));
}

void
test_board_is_checkmate()
{
    Board b;
    board_fen_import(&b, "rnbqk1nr/ppp2Qpp/3p4/2b1p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4");
    assert(board_is_checkmate(&b));

    board_fen_import(&b, "1nbq2rk/rppp4/7Q/4p3/4PP2/8/PPPPN1PP/RNB1KB1R b KQ - 0 1");
    assert(board_is_checkmate(&b));

    board_fen_import(&b, "rnbqk1nr/pppp1ppp/8/4p3/4PP2/8/PPPPNbPP/RNBQKB1R w KQkq - 0 1");
    assert(!board_is_checkmate(&b));

    board_fen_import(&b, "1nbq2rk/r7/7Q/4p3/4PP2/8/PPPPN1PP/RNB1KB1R b KQ - 0 1");
    assert(!board_is_checkmate(&b));
}

void
test_board_is_stalemate()
{
    Board b;
    board_fen_import(&b, "6k1/8/5K1Q/8/8/8/8/8 b - - 0 1");
    assert(board_is_stalemate(&b));

    board_fen_import(&b, "6k1/8/5K1Q/2p5/2P5/8/8/8 b - - 0 1");
    assert(board_is_stalemate(&b));

    board_fen_import(&b, "6k1/8/5K1Q/2p5/8/8/8/8 b - - 0 1");
    assert(!board_is_stalemate(&b));
}

void
test_board_is_out_of_moves()
{
    Board b;
    board_fen_import(&b, "6k1/8/5K1Q/8/8/8/8/8 b - - 0 1");
    assert(board_is_out_of_moves(&b));

    board_fen_import(&b, "rnbqk1nr/ppp2Qpp/3p4/2b1p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4");
    assert(board_is_out_of_moves(&b));

    board_fen_import(&b, FEN_DEFAULT);
    assert(!board_is_out_of_moves(&b));
}

void
test_board_is_equal()
{
    Board b1, b2;
    board_fen_import(&b1, FEN_DEFAULT);
    board_fen_import(&b2, FEN_DEFAULT);
    assert(board_is_equal(&b1, &b2, 1));

    board_fen_import(&b2, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kq - 0 1");
    assert(!board_is_equal(&b1, &b2, 1));

    board_fen_import(&b2, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBN1 w KQkq - 0 1");
    assert(!board_is_equal(&b1, &b2, 1));

    board_fen_import(&b1, "rnb1k2r/ppp1bppp/4pn2/q7/3P4/2N2N2/PPPB1PPP/R2QKB1R w KQkq - 2 7");
    board_fen_import(&b2, "rnb1k2r/ppp1bppp/4pn2/q7/3P4/2N2N2/PPPB1PPP/R2QKB1R w KQkq - 6 7");
    assert(board_is_equal(&b1, &b1, 0));
}

void
test_board_move_pattern_knight_is_valid()
{
    Board b;
    board_fen_import(&b, FEN_DEFAULT);
    assert(board_move_pattern_knight_is_valid(&b, g1, f3, White));
    assert(!board_move_pattern_knight_is_valid(&b, g1, e2, White));
    assert(board_move_pattern_knight_is_valid(&b, f1, g3, White));
    assert(!board_move_pattern_knight_is_valid(&b, b8, d7, Black));
}

void
test_board_move_pattern_bishop_is_valid()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/8/3pP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3");
    assert(!board_move_pattern_bishop_is_valid(&b, f1, h3, White));
    assert(board_move_pattern_bishop_is_valid(&b, f1, c4, White));
    assert(board_move_pattern_bishop_is_valid(&b, f8, c5, Black));
    assert(board_move_pattern_bishop_is_valid(&b, d8, h4, Black));
}

void
test_board_move_pattern_rook_is_valid()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/1ppppppp/8/8/8/8/PPPPPPP1/RNBQKBNR w KQkq - 0 1");
    assert(board_move_pattern_rook_is_valid(&b, h1, h7, White));
    assert(!board_move_pattern_rook_is_valid(&b, a1, a4, White));
    assert(board_move_pattern_rook_is_valid(&b, a8, a2, Black));
    assert(!board_move_pattern_rook_is_valid(&b, h8, e8, Black));
    assert(board_move_pattern_rook_is_valid(&b, h2, h4, White));
}

void
test_board_move_knight_is_valid()
{
    Board b;
    board_fen_import(&b, FEN_DEFAULT);
    assert(board_move_knight_is_valid(&b, g1, f3, White));
    assert(!board_move_knight_is_valid(&b, f1, g3, White));
    assert(!board_move_knight_is_valid(&b, b8, d7, Black));
    assert(board_move_knight_is_valid(&b, b8, a6, Black));
}

void
test_board_move_bishop_is_valid()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/8/3pP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3");
    assert(!board_move_bishop_is_valid(&b, f1, h3, White));
    assert(board_move_bishop_is_valid(&b, f1, c4, White));
    assert(board_move_bishop_is_valid(&b, f8, c5, Black));
    assert(!board_move_bishop_is_valid(&b, d8, h4, Black));
}

void
test_board_move_rook_is_valid()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/1ppppppp/8/8/8/8/PPPPPPP1/RNBQKBNR w KQkq - 0 1");
    assert(board_move_rook_is_valid(&b, h1, h7, White));
    assert(!board_move_rook_is_valid(&b, a1, a4, White));
    assert(board_move_rook_is_valid(&b, a8, a2, Black));
    assert(!board_move_rook_is_valid(&b, h8, e8, Black));
    assert(!board_move_rook_is_valid(&b, h2, h4, White));
}

void
test_board_move_queen_is_valid()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/8/3pP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3");
    assert(board_move_queen_is_valid(&b, d1, h5, White));
    assert(board_move_queen_is_valid(&b, d1, d4, White));
    assert(!board_move_queen_is_valid(&b, d1, c2, White));
    assert(!board_move_queen_is_valid(&b, e8, e7, Black));
    assert(board_move_queen_is_valid(&b, d8, e7, Black));
}

void
test_board_move_pawn_status()
{
    Board b;
    board_fen_import(&b, "r1bqk1nr/ppp1b1Pp/2n1pp2/3pP3/8/8/PPPP1PP1/RNBQKBNR w KQkq d6 0 7");
    assert(board_move_pawn_status(&b, e5, d6, White) == EnPassant);
    assert(board_move_pawn_status(&b, e5, f6, White) == Valid);
    assert(board_move_pawn_status(&b, g7, h8, White) == Promotion);
    assert(board_move_pawn_status(&b, d2, c3, White) == Invalid);
}

void
test_board_move_king_status()
{
    Board b;
    board_fen_import(&b, "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4");
    assert(board_move_king_status(&b, e1, g1, White) == Castling);
    assert(board_move_king_status(&b, e1, e2, White) == Valid);
    assert(board_move_king_status(&b, e1, d1, White) == Invalid);
}

void
test_board_move_is_promotion()
{
    Board b;
    board_fen_import(&b, "r1bqk1nr/ppp1b1Pp/2n1pp2/3pP3/8/8/PPPP1PP1/RNBQKBNR w KQkq d6 0 7");
    assert(board_move_is_promotion(&b, g7, h8));
    assert(!board_move_is_promotion(&b, b2, b4));
}

void
test_board_move_is_capture()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");
    assert(board_move_is_capture(&b, e4, d5));
    assert(!board_move_is_capture(&b, e4, e5));
}

void
test_board_move_is_check()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");
    assert(board_move_is_check(&b, f1, b5, Empty, Valid, Black));

    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/4p3/3P4/5N2/PPP1PPPP/RNBQKB1R b KQkq - 1 2");
    assert(board_move_is_check(&b, f8, b4, Empty, Valid, White));
}

void
test_board_move_is_checkmate()
{
    Board b;
    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/4p3/6P1/5P2/PPPPP2P/RNBQKBNR b KQkq - 0 2");
    assert(board_move_is_checkmate(&b, d8, h4, Empty, Valid));

    board_fen_import(&b, "rnbqk2r/pppp1ppp/5n2/2b1p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR w KQkq - 4 4");
    assert(board_move_is_checkmate(&b, h5, f7, Empty, Valid));

    board_fen_import(&b, "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2");
    assert(!board_move_is_checkmate(&b, f1, b5, Empty, Valid));
}

void
test_board_move_status()
{
    Board b;
    board_fen_import(&b, "r1bqkbnr/p1p2ppp/1pnpp3/4N2Q/4P3/8/PPPP1PPP/RNB1KB1R w KQkq - 0 5");
    assert(board_move_status(&b, h5, f7, Empty) == Valid);

    board_fen_import(&b, "r4k1r/ppp1q2p/2n3bQ/3p2N1/6p1/8/PPPPBPPP/RNB2RK1 b KQkq - 0 1");
    assert(board_move_status(&b, f8, g8, Empty) == Valid);

    board_fen_import(&b, "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4");
    assert(board_move_status(&b, e1, g1, Empty) == Castling);

    board_fen_import(&b, "rnbqkbnr/ppp2ppp/4p3/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3");
    assert(board_move_status(&b, e5, d6, Empty) == EnPassant);

    board_fen_import(&b, "rnbqkbnr/pppp1ppp/4p3/1B6/4P3/8/PPPP1PPP/RNBQK1NR b KQkq - 1 2");
    assert(board_move_status(&b, d7, d5, Empty) == Invalid);
}

void
test_board_move_which()
{
    Board b;
    char which[SQUARE_LEN];

    board_fen_import(&b, FEN_DEFAULT);
    board_move_which(&b, g1, f3, which);
    assert(!strcmp(which, ""));

    board_fen_import(&b, "r1bqkbnr/pppp1ppp/2n5/8/3pP3/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 4");
    board_move_which(&b, f3, d2, which);
    assert(!strcmp(which, "f"));

    board_fen_import(&b, "4k3/8/8/8/8/Q7/8/3QKQ2 w - - 0 1");
    board_move_which(&b, f1, d3, which);
    assert(!strcmp(which, "f1"));

    board_fen_import(&b, "r1bq1rk1/ppp2ppp/2np1n2/2b1p3/2B1P3/3P1N2/PPP2PPP/R1BQKN1R w KQ - 0 7");
    board_move_which(&b, f1, d2, which);
    assert(!strcmp(which, "1"));
}

void
test_board_move_san_export()
{
    Board b;
    char san[SAN_LEN];
    char comp[SAN_LEN];

    board_fen_import(&b, FEN_DEFAULT);
    board_move_san_export(&b, e2, e4, Empty, san, SAN_LEN, Valid);
    snprintf(comp, SAN_LEN, "%se4", piece_map[WhitePawn]);
    assert(!strcmp(san, comp));

    board_move_san_export(&b, g1, f3, Empty, san, SAN_LEN, Valid);
    snprintf(comp, SAN_LEN, "%sf3", piece_map[WhiteKnight]);
    assert(!strcmp(san, comp));

    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/4p3/4PP2/8/PPPP2PP/RNBQKBNR b KQkq - 0 2");
    board_move_san_export(&b, e5, f4, Empty, san, SAN_LEN, Valid);
    snprintf(comp, SAN_LEN, "%sexf4", piece_map[BlackPawn]);
    assert(!strcmp(san, comp));

    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/4p3/6P1/5P2/PPPPP2P/RNBQKBNR b KQkq - 0 2");
    board_move_san_export(&b, d8, h4, Empty, san, SAN_LEN, Valid);
    snprintf(comp, SAN_LEN, "%sh4#", piece_map[BlackQueen]);
    assert(!strcmp(san, comp));

    board_fen_import(&b, "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
    board_move_san_export(&b, f1, b5, Empty, san, SAN_LEN, Valid);
    snprintf(comp, SAN_LEN, "%sb5+", piece_map[WhiteBishop]);
    assert(!strcmp(san, comp));
}

void
test_board_move_san_status()
{
    Board b;
    Square src, dst;
    Piece prom_piece;
    Status status;
    char san[SAN_LEN];

    board_fen_import(&b, FEN_DEFAULT);
    snprintf(san, SAN_LEN, "e4");
    status = board_move_san_status(&b, san, &src, &dst, &prom_piece);
    assert(status == Valid && src == e2 && dst == e4 && prom_piece == Empty);

    snprintf(san, SAN_LEN, "Nf3");
    status = board_move_san_status(&b, san, &src, &dst, &prom_piece);
    assert(status == Valid && src == g1 && dst == f3 && prom_piece == Empty);

    snprintf(san, SAN_LEN, "Ne2");
    assert(board_move_san_status(&b, san, &src, &dst, &prom_piece) == Invalid);

    board_fen_import(&b, "r1bq1rk1/pp2ppbp/2n2np1/3P4/3N4/2N1B3/PPP1BPPP/R2Q1R1K b - - 0 1");
    snprintf(san, SAN_LEN, "Nbd5");
    assert(board_move_san_status(&b, san, &src, &dst, &prom_piece) == Invalid);

    board_fen_import(&b, "rn1r2k1/ppp2p1p/6p1/3Nb3/1PB1P3/4BP2/P4PnP/2R1K2R w K - 3 15");
    snprintf(san, SAN_LEN, "O-O");
    assert(board_move_san_status(&b, san, &src, &dst, &prom_piece) == Invalid);
}

void
test_board_move_do()
{
    Board b;
    Status status;
    int same;
    char fen[FEN_LEN];

    board_fen_import(&b, "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 1 4");
    status = board_move_status(&b, e1, g1, Empty);
    assert(status == Castling);
    board_move_do(&b, e1, g1, Empty, status);
    board_fen_export(&b, fen);
    same = !strcmp(fen, "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 2 4");
    assert(same);

    board_fen_import(&b, FEN_DEFAULT);
    status = board_move_status(&b, e2, e4, Empty);
    assert(status == Valid);
    board_move_do(&b, e2, e4, Empty, status);
    board_fen_export(&b, fen);
    same = !strcmp(fen, "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    assert(same);

    board_fen_import(&b, "rn1r2k1/ppp2p1p/6p1/3Nb3/1PB1P3/4BP2/P4PnP/2R1K2R w K - 3 15");
    status = board_move_status(&b, e1, g1, Empty);
    assert(status == Invalid);

    board_fen_import(&b, "r1b1kbnr/pppp1Npp/8/8/2BnP3/8/PPPP1PqP/RNBQK2R w KQkq - 0 6");
    status = board_move_status(&b, f7, h8, Empty);
    assert(status == Valid);
    board_move_do(&b, f7, h8, Empty, status);
    board_fen_export(&b, fen);
    same = !strcmp(fen, "r1b1kbnN/pppp2pp/8/8/2BnP3/8/PPPP1PqP/RNBQK2R b KQq - 0 6");
    assert(same);
}

void
test_board_move_uci_status()
{
    Status status;
    Square src;
    Square dst;
    Piece prom_piece;
    Board b;

    board_fen_import(&b, FEN_DEFAULT);
    status = board_move_uci_status(&b, "e2e4", &src, &dst, &prom_piece);
    assert(status == Valid && src == e2 && dst == e4 && prom_piece == Empty);

    status = board_move_uci_status(&b, "g1f3", &src, &dst, &prom_piece);
    assert(status == Valid && src == g1 && dst == f3 && prom_piece == Empty);

    status = board_move_uci_status(&b, "g1g3", &src, &dst, &prom_piece);
    assert(status == Invalid);

    board_fen_import(&b, "rnbqkb1r/pppp2Pp/5n2/4p3/8/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 5");
    status = board_move_uci_status(&b, "g7h8Q", &src, &dst, &prom_piece);
    assert(status == Promotion && src == g7 && dst == h8
            && prom_piece == WhiteQueen);

    board_fen_import(&b, "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4");
    status = board_move_uci_status(&b, "e1g1", &src, &dst, &prom_piece);
    assert(status == Castling && src == e1 && dst == g1 && prom_piece == Empty);
}

void
test_board_fen_import()
{
    Board b;
    const char *input_fen;
    board_fen_import(&b, FEN_DEFAULT);
    char fen[FEN_LEN];
    board_fen_export(&b, fen);
    assert(!strcmp(FEN_DEFAULT, fen));

    input_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
    board_fen_import(&b, input_fen);
    board_fen_export(&b, fen);
    assert(!strcmp(fen, input_fen));

    input_fen = "r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 2 4";
    board_fen_import(&b, input_fen);
    board_fen_export(&b, fen);
    assert(!strcmp(fen, input_fen));

    board_fen_import(&b, "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq -");
    board_fen_export(&b, fen);
    assert(!strcmp(fen, "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"));
}

void
test_move_functions()
{
    Move m;
    move_init(&m);
    move_free(&m);
}

void
test_variation_functions()
{
    Board b;
    board_fen_import(&b, FEN_DEFAULT);
    Variation v;
    variation_init(&v, &b);
    variation_move_add(&v, e2, e4, Empty, &b, "e4");
    assert(v.move_count == 2);
    variation_free(&v);
}

void
test_variation_movenumber_export()
{
    Notation n;
    Variation *v;
    FILE *f;
    char num[MOVENUM_LEN];
    notation_init(&n, NULL);
    f = fopen("files/complex.pgn", "r");
    assert(pgn_read_file(f, &n, 0));
    fclose(f);
    variation_movenumber_export(n.line_main, 1, 0, num, MOVENUM_LEN);
    assert(!strcmp(num, "1."));
    variation_movenumber_export(n.line_main, 81, 0, num, MOVENUM_LEN);
    assert(!strcmp(num, "41."));
    variation_movenumber_export(n.line_main, 82, 0, num, MOVENUM_LEN);
    assert(!strcmp(num, ""));
    v = n.line_main->move_list[81].variation_list[0];
    variation_movenumber_export(v, 1, 81, num, MOVENUM_LEN);
    assert(!strcmp(num, "41..."));
    variation_movenumber_export(v, 2, 81, num, MOVENUM_LEN);
    assert(!strcmp(num, "42."));
    v = n.line_main->move_list[27].variation_list[0]->move_list[3].variation_list[0];
    variation_movenumber_export(v, 1, 27+3, num, MOVENUM_LEN);
    assert(!strcmp("16.", num));
    notation_free(&n);
}

void
test_variation_delete_next_moves()
{
    Notation n;
    FILE *f, *of;

    notation_init(&n, NULL);
    f = fopen("files/delete_next_moves_before.pgn", "r");
    of = fopen("tmp_test_07.pgn", "w");
    pgn_read_file(f, &n, 0);
    notation_move_index_set(&n, 5);
    variation_delete_next_moves(n.line_main);
    pgn_write_file(of, &n);
    fclose(f);
    fclose(of);
    notation_free(&n);
}

void
test_notation_tag_functions()
{
    Tag tag;
    Notation n;
    notation_init(&n, NULL); //notation_tag_init is called here
    notation_tag_set(&n, "White", "Morphy, Paul");
    tag = *notation_tag_get(&n, "White");
    assert(!strcmp(tag.key, "White") && !strcmp(tag.value, "Morphy, Paul"));
    snprintf(tag.key, TAG_LEN, "NewTag");
    snprintf(tag.value, TAG_LEN, "Value");
    notation_tag_add(&n, &tag);
    tag = *notation_tag_get(&n, "NewTag");
    assert(!strcmp(tag.key, "NewTag") && !strcmp(tag.value, "Value"));
    notation_tag_remove(&n, "NewTag");
    assert(notation_tag_get(&n, "NewTag") == NULL && n.tag_count == 7);
    notation_free(&n);
}

void
test_notation_functions()
{
    Notation n;
    char *comment = (char*)malloc(sizeof(char) * (strlen("Test") + 1));
    snprintf(comment, strlen("Test") + 1, "Test");
    notation_init(&n, NULL);
    notation_move_add(&n, e2, e4, Empty, Valid);
    assert(notation_move_index_get(&n) == 1);
    notation_move_get(&n)->comment = comment;
    notation_move_add(&n, e7, e5, Empty, Valid);
    notation_move_add(&n, g1, f3, Empty, Valid);
    notation_move_index_set(&n, 1);
    notation_variation_add(&n, c7, c5, Empty, Valid);
    notation_move_add(&n, g1, f3, Empty, Valid);
    assert(!notation_line_is_main(&n));
    assert(notation_move_is_last(&n));
    notation_variation_promote(&n);
    notation_move_index_set(&n, 1);
    assert(notation_move_is_present(&n, c7, c5, Empty));
    assert(notation_move_is_present(&n, e7, e5, Empty));
    n.line_current = notation_move_get(&n)->variation_list[0];
    notation_variation_delete(&n);
    notation_free(&n);
}

void
test_notation_board_find()
{
    Board b;
    Notation n;
    notation_init(&n, NULL);
    FILE *f = fopen("files/complex.pgn", "r");
    pgn_read_file(f, &n, 0);
    fclose(f);
    board_fen_import(&b, "1r1qr1k1/1p3pbp/B2p1np1/2pP4/P3nB2/1QN1PN1b/1P3PP1/R2R2K1 w - - 0 16");
    notation_board_find(&n, &b);
    assert(!strcmp(notation_move_get(&n)->san, "Bxh3"));
    notation_free(&n);
}

void
test_pgn_read_file()
{
    Notation n;
    FILE *f;
    char fen[FEN_LEN];
    int same;
    int ok;

    notation_init(&n, NULL);
    f = fopen("files/piece_hint.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    notation_move_index_set(&n, 46);
    board_fen_export(&notation_move_get(&n)->board, fen);
    same = !strcmp(fen, "r2q2k1/pp4pb/2pB1p1p/3n3P/P5P1/1B1P2Q1/1P2rP2/4R1K1 w - - 0 24");
    fclose(f);
    assert(ok && same);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/complex.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    fclose(f);
    board_fen_export(&(n.line_main->move_list[n.line_main->move_count-1].board), fen);
    same = !strcmp(fen, "8/7p/4Pkp1/p1b2p2/1p6/1B2P1PP/4KP2/8 w - - 0 51");
    assert(same && ok);
    board_fen_export(&(n.line_main->move_list[0].board), fen);
    same = !strcmp(fen, FEN_DEFAULT);
    assert(same && ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/FEN.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    fclose(f);
    board_fen_export(&(n.line_main->move_list[n.line_main->move_count-1].board), fen);
    same = !strcmp(fen, "r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PP1/RNBQKB1R w KQkq - 2 3");
    assert(same && ok);
    board_fen_export(&(n.line_main->move_list[0].board), fen);
    same = !strcmp(fen, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPP1/RNBQKBNR w KQkq - 0 1");
    assert(same && ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/anglebracket.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    fclose(f);
    notation_free(&n);
    assert(ok);

    //Empty file is valid pgn
    notation_init(&n, NULL);
    f = fopen("files/empty.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    fclose(f);
    notation_free(&n);
    assert(ok);

    notation_init(&n, NULL);
    f = fopen("files/variation.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    assert(ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/result_in_comment.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    assert(ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/large.pgn", "r");
    ok = pgn_read_file(f, &n, 2); //pgn_read_next is called here
    assert(ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/subvariation_at_end.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    assert(ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/percent.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    assert(ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/very_complex.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    assert(ok);
    assert(n.line_main->move_count == 68);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/result_overwrite.pgn", "r");
    ok = pgn_read_file(f, &n, 0);
    assert(ok);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/search_board.pgn", "r");
    ok = pgn_read_file(f, &n, 1);
    fclose(f);
    assert(ok);
    notation_free(&n);
}

void
test_pgn_write_file()
{
    Notation n;
    Notation *clone;
    notation_init(&n, NULL);
    FILE * f = fopen("files/complex.pgn", "r");
    FILE * of = fopen("tmp_test_01.pgn", "w");
    pgn_read_file(f, &n, 0);
    pgn_write_file(of, &n);
    fclose(f);
    fclose(of);
    n.line_current = n.line_current->move_list[27].variation_list[0];
    n.line_current = n.line_current->move_list[3].variation_list[0];
    clone = notation_clone(&n);
    notation_free(&n);
    of = fopen("tmp_test_04.pgn", "w");
    pgn_write_file(of, clone);
    fclose(of);
    notation_variation_delete(clone);
    of = fopen("tmp_test_05.pgn", "w");
    pgn_write_file(of, clone);
    fclose(of);
    notation_free(clone);
    free(clone);

    notation_init(&n, NULL);
    f = fopen("files/equal_variations.pgn", "r");
    of = fopen("tmp_test_02.pgn", "w");
    pgn_read_file(f, &n, 0);
    pgn_write_file(of, &n);
    fclose(f);
    fclose(of);
    notation_free(&n);

    notation_init(&n, NULL);
    f = fopen("files/escaped_doublequote.pgn", "r");
    of = fopen("tmp_test_06.pgn", "w");
    pgn_read_file(f, &n, 0);
    pgn_write_file(of, &n);
    fclose(f);
    fclose(of);
    notation_free(&n);
}

void
test_pgn_replace_game()
{
    Notation n;
    notation_init(&n, NULL);
    FILE *f = fopen("files/equal_variations.pgn", "r");
    pgn_read_file(f, &n, 0);
    fclose(f);
    pgn_replace_game("tmp_test_03.pgn", &n, 1);
    notation_free(&n);
}

void
test_pgn_count_games()
{

    FILE *f;
    int count;

    f = fopen("files/large.pgn", "r");
    count = pgn_count_games(f);
    fclose(f);
    assert(count == 7810);

    f = fopen("files/empty.pgn", "r");
    count = pgn_count_games(f);
    assert(count == 0);

    f = fopen("files/invalid_tags.pgn", "r");
    count = pgn_count_games(f);
    assert(count == -1);
}

void
test_uci_line_parse()
{
    Variation v;
    Board b;
    UciScoreType type;
    int depth, multipv, score;
    const char * line = "info depth 20 seldepth 32 multipv 1 score cp 54 nodes 3442296 nps 1228952 hashfull 939 tbhits 0 time 2801 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 g8f6 c1e3 f8d6 f1d3 e8g8 e1g1 b8c6 b1c3 c6b4 c3b5 c7c6 b5d6 d8d6 c2c3 b4d3 d1d3";
    board_fen_import(&b, FEN_DEFAULT);
    variation_init(&v, &b);
    uci_line_parse(line, 1024, &b, &depth, &multipv, &type, &score, &v);
    assert(depth == 20 && multipv == 1 && type == Centipawn && score == 54
            && !strcmp(v.move_list[1].san, "e4")
            && !strcmp(v.move_list[10].san, "Bd6")
            && !strcmp(v.move_list[23].san, "Qxd3") && v.move_count == 24);
    uci_line_parse(line, 1024, &b, &depth, &multipv, &type, &score, &v);
    assert(depth == 20 && multipv == 1 && type == Centipawn && score == 54
            && !strcmp(v.move_list[1].san, "e4")
            && !strcmp(v.move_list[10].san, "Bd6")
            && !strcmp(v.move_list[23].san, "Qxd3"));
    uci_line_parse(line, 1024, NULL, &depth, &multipv, &type, &score, NULL);
    assert(depth == 20 && multipv == 1 && type == Centipawn && score == 54);

    line = "depth 10 pv de";
    uci_line_parse(line, 1024, &b, &depth, &multipv, &type, &score, &v);
    assert(type == NoType);
    variation_free(&v);

    board_fen_import(&b, "rnbqkbnr/pppp1ppp/8/4p3/6P1/5P2/PPPPP2P/RNBQKBNR b KQkq g3 0 2");
    variation_init(&v, &b);
    line = "info depth 21 seldepth 34 multipv 2 score cp 316 nodes 2412251 nps 504971 hashfull 842 tbhits 0 time 4777 pv h7h5 g4g5 d8g5 d2d3 g5h4 e1d2 d7d5 d1e1 h4e1 d2e1 b8c6 b1c3 g8f6 c3b5 e8d8 g1h3 f6h7 h3f2 a7a6 b5c3 c6d4 e1d1 c7c6";
    uci_line_parse(line, 1024, &b, &depth, &multipv, &type, &score, &v);
    assert(v.move_count == 24);
    line = "info depth 245 seldepth 2 multipv 1 score mate 1 nodes 7351 nps 565461 tbhits 0 time 13 pv d8h4";
    uci_line_parse(line, 1024, &b, &depth, &multipv, &type, &score, &v);
    assert(depth == 245 && multipv == 1 && type == Mate && score == 1
            && !strcmp(v.move_list[1].san, "Qh4#")
            && !strlen(v.move_list[2].san));
    variation_free(&v);
}

void
test_readme_example_01()
{
    Notation n;
    notation_init(&n, NULL); //NULL means default starting position
    notation_tag_set(&n, "White", "New game");

    const char *san = "e4";
    Status status;
    Square src, dst;
    Piece prom_piece;
    status = notation_move_san_status(&n, san, &src, &dst, &prom_piece);
    if(status != Invalid){
        notation_move_add(&n, src, dst, prom_piece, status);
        FILE *f = fopen("new_game.pgn", "w");
        pgn_write_file(f, &n);
        fclose(f);
    }else{
        printf("Invalid move\n");
    }
    notation_free(&n);
}

void
test_readme_example_02()
{
    Notation n;
    notation_init(&n, NULL);
    FILE *f = fopen("files/game_list.pgn", "r");
    pgn_read_file(f, &n, 1); //read second game to notation
    fclose(f);
    notation_free(&n);
}

void
test_game_list_functions()
{
    GameList gl;
    GameList new_gl;
    FILE *f = fopen("files/medium.pgn", "r");
    game_list_read_pgn(&gl, f);
    assert(!strcmp(gl.list[0].title, "Carlsen,M-Utegaliyev,A/World Rapid 2019[1.1]/2019.12.26 (1-0)"));
    assert(!strcmp(gl.list[1].title, "Castellanos Rodriguez,R-Vachier Lagrave,M/World Rapid 2019[1.2]/2019.12.26 (1/2-1/2)"));
    assert(gl.list[1].index == 1);
    game_list_search_str(&gl, &new_gl, "Carlsen");
    assert(new_gl.count == 1);
    game_list_free(&new_gl);
    game_list_search_str(&gl, &new_gl, "world RAPID");
    assert(new_gl.count == 6);
    game_list_free(&new_gl);

    Board b;
    board_fen_import(&b, "rnb1kbnr/pp2pppp/2pq4/8/3P4/2N5/PPP2PPP/R1BQKBNR w KQkq - 0 5");

    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    game_list_free(&new_gl);
    assert(new_gl.count == 1);

    board_fen_import(&b, "r1bqkbnr/pp1npppp/3p4/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 4");
    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    fclose(f);
    game_list_free(&gl);
    assert(new_gl.count == 2);
    game_list_free(&new_gl);

    board_fen_import(&b, "rnbqr1k1/1p3pbp/p2p2p1/2pP4/P3nB2/2N1PN1P/1P2BPP1/R2QK2R w KQ - 3 12");
    f = fopen("files/complex.pgn", "r");
    game_list_read_pgn(&gl, f);
    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    assert(new_gl.count == 1);
    game_list_free(&new_gl);

    board_fen_import(&b, "8/7p/4Pkp1/p1b2p2/1p6/1B2P1PP/4KP2/8 w - - 0 51");
    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    assert(new_gl.count == 1);
    game_list_free(&new_gl);

    board_fen_import(&b, "rnbq2k1/1p3pbp/p2p2p1/2pP4/Pr3B2/4P2P/1P1NBPP1/R2QK2R w KQ - 2 14");
    fseek(f, 0 , SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    assert(new_gl.count == 1);
    game_list_free(&new_gl);
    game_list_free(&gl);
    fclose(f);

    board_fen_import(&b, "7k/4R1p1/1P1B1p1p/7P/3p2r1/3bP3/7K/8 b - - 1 37");
    f = fopen("files/piece_hint.pgn", "r");
    game_list_read_pgn(&gl, f);
    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    assert(new_gl.count == 1);
    game_list_free(&new_gl);
    game_list_free(&gl);
    fclose(f);

    board_fen_import(&b, "r1bqkb1r/pp3p1p/2p3p1/2npP3/5P2/2NB4/PPP3PP/R1BQ1RK1 w kq - 0 10");
    f = fopen("files/search_board.pgn", "r");
    game_list_read_pgn(&gl, f);
    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    game_list_free(&new_gl);
    game_list_free(&gl);
    fclose(f);

    f = fopen("files/escaped_doublequote.pgn", "r");
    game_list_read_pgn(&gl, f);
    assert(!strcmp(gl.list[0].title, "-/Quote \"[]/2020.09.19 (*)"));
    game_list_free(&new_gl);
    game_list_free(&gl);
    fclose(f);

    board_fen_import(&b, "r1b1kb1r/1p1n1ppp/pq1ppn2/6B1/3NP3/1BN5/PPPQ1PPP/R3K2R b KQkq - 1 9");
    f = fopen("files/skip_error.pgn", "r");
    game_list_read_pgn(&gl, f);
    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    game_list_free(&new_gl);
    game_list_free(&gl);
    fclose(f);

    board_fen_import(&b, "4rrk1/1b4b1/1p2q1pp/2p5/4PPpB/2P1Q3/3N2PP/4RRK1 w - - 0 25");
    f = fopen("files/search_board.pgn", "r");
    game_list_read_pgn(&gl, f);
    fseek(f, 0, SEEK_SET);
    game_list_search_board(&gl, &new_gl, f, &b);
    game_list_free(&new_gl);
    game_list_free(&gl);
    fclose(f);
}

int main(){
    //STRING UTILS
    test_strtok_r();
    test_concate();
    test_trimmove();
    test_trimendl();
    test_trimcomment();
    test_charremove();
    test_charcount();
    test_charcount_before();
    test_charcount_after();
    test_str_is_move();
    test_str_is_square();
    test_str_is_fen();
    test_tag_extract();
    test_tag_escape_value();

    //BOARD UTILS
    test_filerank2square();
    test_square2rank();
    test_square2file();
    test_char2rank();
    test_char2file();
    test_char2piece();
    test_rank2char();
    test_file2char();
    test_piece2char();
    test_move_offset_find();
    test_move_uci_export();

    //BOARD FUNCTIONS
    test_board_square_piece_color();
    test_board_square_set();
    test_board_square_is_attacked();
    test_board_is_check();
    test_board_is_checkmate();
    test_board_is_stalemate();
    test_board_is_out_of_moves();
    test_board_is_equal();
    test_board_move_pattern_knight_is_valid();
    test_board_move_pattern_bishop_is_valid();
    test_board_move_pattern_rook_is_valid();
    test_board_move_knight_is_valid();
    test_board_move_bishop_is_valid();
    test_board_move_rook_is_valid();
    test_board_move_queen_is_valid();
    test_board_move_pawn_status();
    test_board_move_king_status();
    test_board_move_is_promotion();
    test_board_move_is_capture();
    test_board_move_is_check();
    test_board_move_is_checkmate();
    test_board_move_status();
    test_board_move_which();
    test_board_move_san_export();
    test_board_move_san_status();
    test_board_move_do();
    test_board_move_uci_status();
    test_board_fen_import();

    //MOVE FUNCTIONS
    test_move_functions();

    //VARIATION FUNCTIONS
    test_variation_functions();
    test_variation_movenumber_export();
    test_variation_delete_next_moves();

    //NOTATION FUNCTIONS
    test_notation_tag_functions();
    test_notation_functions();
    test_notation_board_find();

    //PGN FUNCTIONS
    test_pgn_read_file();
    test_pgn_write_file();
    test_pgn_replace_game();
    test_pgn_count_games();

    //UCI FUNCTIONS
    test_uci_line_parse();

    test_readme_example_01();
    test_readme_example_02();

    test_game_list_functions();
    return 0;
}
