
#include "compiler/lexer/lexer.h"
#include "base/base_arena.h"
#include "base/base_defs.h"
static u8 lexer_peak(lexer *lexer) { return lexer->buff.str[lexer->position]; }

static void skip_whitespace(lexer *lexer) { lexer->position++; }

static token *make_token(lexer *lexer, token_type token_type) {
  token *new_token = PUSH_STRUCT(lexer->arena, token);
  new_token->type = token_type;
  new_token->line = lexer->line;
  new_token->column = lexer->column;
  switch (token_type) {
  case TOK_EOF:
  case TOK_OP:
  case TOK_LPAREN:
  case TOK_RPAREN:
  case TOK_LBRACE:
  case TOK_RBRACE:
  case TOK_SEMI:
  case TOK_COMMA:
    new_token->lexeme.str = &lexer->buff.str[lexer->position];
    new_token->lexeme.len = 1;
    goto tok;
  case TOK_ERROR:
  case TOK_IDENT:
  case TOK_NUMBER:
  case TOK_STRING:
  case TOK_KEYWORD:
    u64 start = lexer->position;
    new_token->lexeme.str = &lexer->buff.str[start];
    new_token->lexeme.len = lexer->position - start;
    goto tok;
  default:
    return nullptr;
  }

tok:
  return new_token;
}

static token *read_identifier(lexer *lexer) {}

token *read_number(lexer *lexer) {}

static token *read_string(lexer *lexer) {}

static token *read_operator(lexer *lexer) {}

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
