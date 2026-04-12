
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
  TOK_COMMA
} TokenType;

typedef struct {
  TokenType type;
} Token;
