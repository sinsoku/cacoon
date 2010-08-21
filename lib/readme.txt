このフォルダにboost、gtest、tinyxmlをインストールする。

1. boost
 1.1. http://www.boost.org/users/download/からダウンロード
   * バージョンは1.43
 2.1. 解凍して、boost_1_43_0フォルダに入れる。

2. GoogleTest
 2.1. http://code.google.com/p/googletest/downloads/listからダウンロード
   * バージョンは1.5.0
 2.2. 解凍してgtest-1.5.0/msvc/gtest.sln を実行
 2.3. 変換ウィザードが動くので、「完了」を押す
 2.4. ソリューションごとビルド
   * gtest_unittestをスタートアッププロジェクトに設定して、テストする。

3. TinyXml
 3.1. http://sourceforge.net/projects/tinyxml/からダウンロード
   * バージョンは2.6.1
 3.2. 解凍してフォルダ名をtinyxml_2_6_1/tinyxml.slnを実行
 3.3. 変換ウィザードが動くので、「完了」を押す
 3.4. tinyxml_2_6_1/xmltest.cppが文字化けしているので、直す。
     i. TeraPadで開く
    ii. 文字コード指定再読込み でUTF-8Nにする。
   iii. 文字/改行コード指定保存を でSHIFT-JISで保存する。
   （他エディタでも同様の保存を行えば問題ないと思われる。）
 3.5. ソリューションごとビルド

4. Cacoon プロジェクトでビルドする。
