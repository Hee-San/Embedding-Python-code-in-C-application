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
  char *file = "calculator"; // .pyファイル名(拡張子なし)
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


  // ------  In:2実数, Out:1実数 の場合  ------
  // 関数の読み込み
  char *func = "Add"; // 関数名
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
  PyObject *pArgs, *pValue1, *pValue2;
  pArgs = PyTuple_New(2); // 引数の個数を指定し、引数セットを作成
  // 引数1つ目は2、2つ目は1.5にしてみる。
  int val1 = 2;
  pValue1 = PyLong_FromLong(val1); // C整数からPy整数へ変換
  float val2 = 1.5;
  pValue2 = PyFloat_FromDouble(val2); // C実数からPy実数へ変換

  // 引数の変換に失敗したら
  if (!pValue1 || !pValue2) { // !pValue1は、pValue1==NULLと同じ
    Py_DECREF(pArgs);
    Py_DECREF(pModule);
    fprintf(stderr, "Cannot convert argument\n");
    return 1;
  }

  // 引数セットに引数を入れる
  PyTuple_SetItem(pArgs, 0, pValue1);
  PyTuple_SetItem(pArgs, 1, pValue2);

  // 関数の実行
  PyObject *pAns;
  printf("Call: %s(%d, %f)\n", func, val1, val2);
  pAns = PyObject_CallObject(pFunc, pArgs);

  if (pAns) { // 戻り値があったら
    float ans = PyFloat_AsDouble(pAns); // Py実数からC実数へ変換
    printf("Result of call: %f\n", ans);
    Py_DECREF(pAns);
  }

  // 解放
  Py_DECREF(pValue1);
  Py_DECREF(pValue2);
  Py_DECREF(pArgs);
  Py_XDECREF(pFunc);
  Py_DECREF(pModule);

  return 0;
}