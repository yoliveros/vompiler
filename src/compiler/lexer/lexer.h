#pragma once

typedef enum {
  KEY_NONE = 0,
  KEY_VOID,
  KEY_RETURN,
  KEY_INT,
  KEY_CHAR,
} keyword_type;

typedef enum {
  OP_NONE = 0,
  OP_PLUS,       // +
  OP_MINUS,      // -
  OP_STAR,       // *
  OP_DIV,        // /
  OP_MOD,        // %
  OP_INC,        // ++
  OP_DEC,        // --
  OP_ADD_ASSIGN, // +=
  OP_SUB_ASSIGN, // -=
  OP_MUL_ASSIGN, // *=
  OP_DIV_ASSIGN, // /=
  OP_MOD_ASSIGN, // %=
  OP_ASSIGN,     // =
  OP_EQ,         // ==
  OP_NOT,        // !
  OP_NEQ,        // !=
  OP_LT,         // <
  OP_GT,         // >
  OP_LEQ,        // <=
  OP_GEQ,        // >=
  OP_AND,        // &
  OP_OR,         // |
  OP_LAND,       // &&
  OP_LOR,        // ||
  OP_DOT,        // .
  OP_ARROW,      // ->
  OP_SHIFT_L,    // <<
  OP_SHIFT_R,    // >>
} op_token;

typedef enum {
  TOK_EOF = 0,
  TOK_ERROR,
  TOK_IDENT,
  TOK_NUMBER,
  TOK_STRING,
  TOK_KEYWORD,
  TOK_OP,
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_LBRACE,
  TOK_RBRACE,
  TOK_SEMI,
  TOK_COLON,
  TOK_COMMA
} token_type;

typedef union {
  keyword_type keyword;
  op_token op;
} ex_token;

typedef struct {
  token_type type;
  ex_token extra;
  string8 lexeme;
  i32 line;
  i32 column;
} token;

typedef struct {
  mem_arena *arena;
  string8 buff;
  u64 position;
  i32 line;
  i32 column;
} lexer;

void lexer_init(mem_arena *arena, lexer *lexer, const string8 buff);
token *lexer_next_token(lexer *lexer);
