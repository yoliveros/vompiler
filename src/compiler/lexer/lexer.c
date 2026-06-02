
#include "lexer.h"

inline static u8 lexer_peak(lexer *lexer) {
  return lexer->buff.str[lexer->position];
}

inline static token *alloc_token(lexer *lexer) {
  token *t = PUSH_STRUCT(lexer->arena, token);
  t->keyword = KEY_NONE;
  return t;
}

inline static bool lexeme_match(string8 lexeme, char *keyword) {
  return strncmp(keyword, lexeme.str, lexeme.len) == 0;
}

static void skip_whitespace(lexer *lexer) {
  u8 c = lexer_peak(lexer);
  while (c == ' ' || c == '\n' || c == '\t') {
    if (c == '\n') {
      lexer->line++;
      lexer->column = 1;
    } else {
      lexer->column++;
    }

    lexer->position++;
    c = lexer_peak(lexer);
  }
}

static token *read_identifier(lexer *lexer) {
  token *t = alloc_token(lexer);
  t->type = TOK_IDENT;
  u64 start = lexer->position;

  u8 c = lexer_peak(lexer);
  void *curr_buff = &lexer->buff.str[start];
  t->lexeme.str = curr_buff;
  while (isalnum(c) || c == '_') {
    lexer->position++;
    lexer->column++;
    c = lexer_peak(lexer);
  }
  t->lexeme.len = lexer->position - start;

  if (lexeme_match(t->lexeme, "void"))
    t->keyword = KEY_VOID;
  else if (lexeme_match(t->lexeme, "int"))
    t->keyword = KEY_INT;
  else if (lexeme_match(t->lexeme, "char"))
    t->keyword = KEY_CHAR;
  else if (lexeme_match(t->lexeme, "return"))
    t->keyword = KEY_RETURN;

  if (t->keyword != KEY_NONE)
    t->type = TOK_KEYWORD;

  return t;
}

token *read_number(lexer *lexer) {
  token *t = alloc_token(lexer);
  t->type = TOK_NUMBER;
  i64 start = lexer->position;
  u8 c = lexer_peak(lexer);
  t->lexeme.str = &lexer->buff.str[lexer->position];

  while (isdigit(c)) {
    lexer->position++;
    lexer->column++;
    c = lexer_peak(lexer);
  }

  t->lexeme.len = lexer->position - start;

  return t;
}

static token *read_string(lexer *lexer) {
  token *t = alloc_token(lexer);
  t->type = TOK_STRING;
  t->lexeme.str = &lexer->buff.str[lexer->position];
  lexer->position++; // Skipping the first doulbe quote
  lexer->column++;
  i64 start = lexer->position;
  u8 c = lexer_peak(lexer);

  while (c != '\"') {
    lexer->position++;
    lexer->column++;
    c = lexer_peak(lexer);
  }
  t->lexeme.len = lexer->position - start;

  lexer->position++;
  lexer->column++;

  return t;
}

static token *read_operator(lexer *lexer) {
  token *t = alloc_token(lexer);

  return t;
}

static token *make_token(lexer *lexer, token_type type) {
  token *t = alloc_token(lexer);

  t->type = type;
  t->line = lexer->line;
  t->column = lexer->column;

  if (type == TOK_EOF) {
    t->lexeme = (string8){0};
  } else {
    t->lexeme.str = &lexer->buff.str[lexer->position];
    t->lexeme.len = 1;
    lexer->position++;
    lexer->column++;
  }

  return t;
}

static token_type char_to_token_type(u8 c) {
  switch (c) {
  case '(':
    return TOK_LPAREN;
  case ')':
    return TOK_RPAREN;
  case '{':
    return TOK_LBRACE;
  case '}':
    return TOK_RBRACE;
  case ';':
    return TOK_SEMI;
  case ',':
    return TOK_COMMA;
  default:
    return TOK_ERROR;
  }
}

token *lexer_next_token(lexer *lexer) {
  skip_whitespace(lexer);

  u8 c = lexer_peak(lexer);

  switch (c) {
  case '\0':
    return make_token(lexer, TOK_EOF);
  case 'a' ... 'z':
  case 'A' ... 'Z':
  case '_':
    return read_identifier(lexer);
  case '0' ... '9':
    return read_number(lexer);
  case '"':
  case '\'':
    return read_string(lexer);
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case '=':
  case '!':
  case '<':
  case '>':
  case '&':
  case '|':
  case ':':
  case '.':
    return read_operator(lexer);
  case '(':
  case ')':
  case '{':
  case '}':
  case ';':
  case ',':
    return make_token(lexer, char_to_token_type(c));
  default:
    return make_token(lexer, TOK_ERROR);
  }
}

void lexer_init(mem_arena *arena, lexer *lexer, string8 buff) {
  lexer->arena = arena;
  lexer->buff = buff;
  lexer->position = 0;
  lexer->column = 1;
  lexer->line = 1;
}
