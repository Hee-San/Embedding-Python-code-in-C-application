#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main(int argc, char *argv[]) {
  wchar_t *program = Py_DecodeLocale("pyProgramName", NULL);
  Py_SetProgramName(program);
  Py_Initialize();
  PyRun_SimpleString("print('Hello world from Python!')\n");
  PyMem_RawFree(program);
  return 0;
}