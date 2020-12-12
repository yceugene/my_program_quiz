typedef enum
{
    FALSE,
    TRUE,
} BOOL;

typedef enum
{
	frOK,
  frQuit,
	frError,
	frSyntaxError,
	frFileOpenError,
	frINVALID,
} eFUNCTIONRETURN;

typedef struct tagNODE {
  struct tagNODE* left;
  struct tagNODE* right;
  int data;
} sNODE, *psNODE;
