#define PY_SSIZE_T_CLEAN
#include <Python.h>

// カレントディレクトリをパスに追加
void set_path() {
    PyObject *sys      = PyImport_ImportModule("sys");
    PyObject *sys_path = PyObject_GetAttrString(sys, "path");
    PyList_Append(sys_path, PyUnicode_DecodeFSDefault("."));
}

int main(int argc, char *argv[]) {
  PyObject *pName, *pModule, *pFunc;
  Py_Initialize();

  // .pyファイルのあるカレントディレクトリをパスに追加
  set_path();


  // .pyファイルの読み込み
  char *file = "hello"; // .pyファイル名(拡張子なし)
  pName = PyUnicode_DecodeFSDefault(file);
  pModule = PyImport_ImportModule(file);
  Py_DECREF(pName); // 使い終わったpNameを解放

  // .pyファイルの読み込みに失敗したら
  if (pModule == NULL) {
    if (PyErr_Occurred()) PyErr_Print();
    fprintf(stderr, "Cannot find function \"%s\"\n", file);
    Py_DECREF(pModule); // 解放
    return 1;
  }


  // 関数の読み込み
  char *func = "hello"; // 関数名
  pFunc = PyObject_GetAttrString(pModule, func);

  // 関数の読み込みに失敗したら
  if (pFunc == NULL) {
    if (PyErr_Occurred()) PyErr_Print();
    fprintf(stderr, "Cannot find function \"%s\"\n", func);
    Py_XDECREF(pFunc); // 解放
    Py_DECREF(pModule);
    return 1;
  }


  // 関数の実行
  PyObject_CallObject(pFunc, NULL);


  // 解放
  Py_XDECREF(pFunc);
  Py_DECREF(pModule);

  return 0;
}