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
  char *file = "arr"; // .pyファイル名(拡張子なし)
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


  // ------  In:配列(リスト), Out:配列(リスト) の場合  ------
  // 関数の読み込み
  char *func = "ArrSort"; // 関数名
  pFunc = PyObject_GetAttrString(pModule, func);

  // 関数の読み込みに失敗したら
  if (pFunc == NULL || !PyCallable_Check(pFunc)) {
    if (PyErr_Occurred()) PyErr_Print();
    fprintf(stderr, "Cannot find function \"%s\"\n", func);
    Py_XDECREF(pFunc); // 解放
    Py_DECREF(pModule);
    return 1;
  }

  // 引数の準備
  PyObject *pArgs, *pValue;
  pArgs = PyTuple_New(1); // 引数の個数を指定し、引数セットを作成
  // 引数は実数の配列
  int a[] = {1, 4, 1, 4, 2, 1, 3, 5, 6};
  pValue = PyList_New(9); // 長さ9のPyListを用意
  for (int i = 0; i < 9; i++) {
    PyList_SET_ITEM(pValue, i, PyLong_FromLong(a[i])); // 1つずつ変換・格納
  }

  // 引数の変換に失敗したら
  if (!pValue) {
    Py_DECREF(pArgs);
    Py_DECREF(pModule);
    fprintf(stderr, "Cannot convert argument\n");
    return 1;
  }

  // 引数セットに引数を入れる
  PyTuple_SetItem(pArgs, 0, pValue);

  // 関数の実行
  PyObject *pAns;
  printf("Call: %s([", func);
  for (int i = 0; i < 9; i++) printf("%d, ", a[i]);
  printf("]\n");
  pAns = PyObject_CallObject(pFunc, pArgs);

  if (pAns) { // 戻り値があったら
    if (!PyList_Check(pAns)) { // 戻り値がPyListと解釈できないとき
      fprintf(stderr, "Cannot convert list\n");
      Py_DECREF(pAns);
      return 1;
    }

    printf("Result of call: [");
    int n = PyList_Size(pAns); // 配列の長さ
    for (int i = 0; i < n; i++){
        PyObject *item = PyList_GetItem(pAns, i); // 値の取得
        int v = PyLong_AsLong(item); // 値の変換
        printf("%d, ", v);
        Py_DECREF(item);
    }
    printf("]\n");

    Py_DECREF(pAns);
  }

  // 解放
  Py_DECREF(pValue);
  Py_DECREF(pArgs);
  Py_XDECREF(pFunc);
  Py_DECREF(pModule);

  return 0;
}