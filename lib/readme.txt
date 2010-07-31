このフォルダにboost、gtestをインストールする。

1. boost
解凍して、boost_1_43_0フォルダに入れる。

2. GoogleTest
 2.1. http://code.google.com/p/googletest/downloads/listからダウンロード
   * バージョンは1.5.0
 2.2. 解凍してmsvc/gtest.sln を実行
 2.3. 変換ウィザードが動くので、「完了」を押す
 2.4. ソリューションごとビルド
   * gtest_unittestをスタートアッププロジェクトに設定して、テストする。

ビルドが終わったら、gtest-1.5.0フォルダに入れる。

3. Cacoon プロジェクトでビルドする。
