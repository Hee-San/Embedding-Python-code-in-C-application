# Embedding Python code in C application

C言語のコードからPythonを呼び出すサンプル

参考: [[Python公式ドキュメント] 他のアプリケーションへの Python の埋め込み](https://docs.python.org/ja/3/extending/embedding.html)

Cythonを使った方法ではなく、Cで`#include <Python.h>`してPythonを呼ぶ方法を試します。

※ VS CodeのRemote Containerでコンテナを作れるようにしてあります。
わからない人は無視してください。

## 目次

**簡単な例から順を追って理解できるよう目指した構成なので、ぜひ1度は前から順に目を通してみてください。**

1. 文字列でPyコードを直接埋め込み
    Cプログラム内で、Pythonのコードを文字列として定義し、それを実行します。
    CでPyを実行するために必要なモジュールのインポートなどを確認してください。
    またMakefileを見て、コンパイルオプション・リンクオプションを確認してください。

2. .pyファイルの呼び出し
    Cプログラム内で、Pythonのプログラムファイルを呼び出し、実行します。
    引数や戻り値のないシンプルな例です。
    ファイルや関数の指定の仕方を確認してください。

3. 引数や戻り値のある関数の呼び出し
    引数や戻り値のあるPythonのプログラムファイルを呼び出し、実行します。
    CとPy間での型変換や、値の受け渡し方を確認してください。

4. 配列を受け渡す関数の呼び出し
    引数や戻り値に、配列(リスト)のある関数を実行します。
    CとPy間でのデータ構造の変換を確認してください。

## 参考

[[公式ドキュメント] Python インタプリタの拡張と埋め込み](https://docs.python.org/ja/3/extending/index.html)
[[公式ドキュメント] Python/C API リファレンスマニュアル¶
](https://docs.python.org/ja/3/c-api/index.html)

### それらのうち、特に参考にしたもの

- コンパイラ・リンカオプションについて
    [1.6. Unix 系システムにおけるコンパイルとリンク](https://docs.python.org/ja/3/c-api/index.html#python-c-api-reference-manual)

- Pythonのコード文字列をCで実行
    [1.1. 高水準の埋め込み](https://docs.python.org/ja/3/extending/embedding.html#very-high-level-embedding)

- 引数のあるPy関数を別ファイルのCから実行
    [1.3. 純粋な埋め込み](https://docs.python.org/ja/3/extending/embedding.html#pure-embedding)

- C-Py間の型変換
    [具象オブジェクト (concrete object) レイヤ](https://docs.python.org/ja/3/c-api/concrete.html)

- 配列(リスト)の構成
    [リストオブジェクト](https://docs.python.org/ja/3/c-api/list.html)
