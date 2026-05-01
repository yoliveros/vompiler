
typedef enum {
  KEY_VOID,
  KEY_RETURN,
  KEY_INT,
  KEY_CHAR,
} keyword_type;

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
} token_type;

typedef enum {
  START = 0,
  IN_ID,
  IN_NUM,
  IN_OPERATOR,
  IN_STR,
} state_machine;

typedef struct {
  token_type type;
  keyword_type keyword;
  string8 lexeme;
  i32 line;
  i32 column;
} token;

typedef struct {
  string8 buff;
  u64 position;
  i32 line;
  i32 column;
} lexer;

void lexer_init(lexer *lexer, const string8 buff);
token *lexer_next_token(lexer *lexer);
