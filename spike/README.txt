Doxygenについて

1) Doxyfileを生成する
  doxygen. exe -g

2) Doxyfileを編集する
  OUTPUT_LANGUAGE = Japanese
  GENERATE_LATEX = NO

3) ファイル名へのコメントを付ける例
  ヘッダファイルやCPPファイルにコメントをつける際の例。
  @fileと@briefがあればドキュメントに反映される。

	/**
	* @file ファイル名.h
	* @brief 簡単な説明
	* @author 作成者
	* @date 作成日
	* @details 詳細な説明
	* @param 引数の説明
	* @return 返却値の説明
	*/

    /**
    *  - 番号なしリスト1
    *  - 番号なしリスト2
    *
    *  -# 番号ありリスト1
    *  -# 番号ありリスト2
    */

4) ドキュメント生成する
 doxygen
