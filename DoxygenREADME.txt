2026年度SPIKE-RTのC++リファレンスをDoxygenで生成する

0) DoxygenをWSLにインストールする
   sudo apt install doxygen graphviz

1) GitHubのリポジトリ「git@github.com:jecsugawara.github.io.git」をホームディレクトリにcloneする
   cd ~
   git clone git@github.com:jecsugawara.github.io.git

   ~/jecsugawara.github.io ディレクトリが作成される。

2) SPIKE-RTのヘッダファイルをGitのローカルリポジトリにコピーする
   (本家の内容が変更された場合は変更部分のみをコピーすること。そうしないと変更内容がすべて上書きされてしまう！)
   cp -r ~/etrobo/spike-rt/drivers/include/libcpp/spike/ ~/jecsugawara.github.io/

   **注意** GitHub Pagesにアップロードするファイルにリンク切れのシンボリックリンクがあるとデプロイ時にエラーとなる。 

3) C++のヘッダファイルにDoxygen形式のコメントを追加する
   ~/etrobo/spike-rt/drivers/include/libcpp/spike/の下の IMU.h や ColorSensor.h を編集する。

  (ちなみにC++のコードは ~/etrobo/spike-rt/drivers/libcpp/spike/の下に IMU.cpp や Clock.h が存在するがコメントはなし)

4) Doxyfileを生成して必要に応じて内容を編集する
   cd ~/jecsugawara.github.io/spike/
   doxygen -g 
   
   ~/jecsugawara.github.io/spike/Doxyfileが生成される。
   Doxyfileを必要に応じて編集する。前回のファイルを再使用する場合はコピーする。

5) HTMLファイルを生成する
   cd ~/jecsugawara.github.io/spike/
   doxygen Doxyfile

   html形式とlatex形式が生成される。

6) HTMLをGitHubのリモートリポジトリにプッシュする
   cd ~/jecsugawara.github.io/spike/
   git add .
   git commit -m "コミットメッセージ"
   git push

