# Embedding Python code in C application

C言語のコードからPythonを呼び出すサンプル

参考: [[Python公式ドキュメント] 他のアプリケーションへの Python の埋め込み](https://docs.python.org/ja/3/extending/embedding.html)

Cythonを使った方法ではなく、Cで`#include <Python.h>`してPythonを呼ぶ方法を試します。