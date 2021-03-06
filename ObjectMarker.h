/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//
// Copyright (C) 2014 Takuya MINAGAWA, 2006 Gunawan Herman, 2003 Florian Adolf.
// Third party copyrights are property of their respective owners.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//M*/
#ifndef __OBJECT_MARKER__
#define __OBJECT_MARKER__

#include <opencv2/core/core.hpp>
#include "MarkerViewer.h"


class ObjectMarker
{
public:
	ObjectMarker();
	~ObjectMarker();

	//! プログラム起動
	int run(const std::string& conf_file);

	bool begin(){ return jump(0); };
	bool next(){ return jump(_image_idx + 1); };
	bool prev(){ return jump(_image_idx - 1); };
	bool reload(){ return jump(_image_idx); };
	bool jump(int idx);

	//! ヘルプを表示
	static void printHelp();

	//! ステータス表示
	void printStatus() const;

	//! 設定ファイルの保存
	/*!
	\param[in] config_name 設定ファイル名
	\param[in] input_dir 画像格納フォルダ名
	\param[in] outputname 出力テキストファイル名
	\param[in] display_scale 画像の表示スケール
	\return ファイル書き込みの成否
	*/
	static bool saveConfiguration(const std::string& config_name,
		const std::string& input_dir, const std::string& outputname,
		const MarkerViewer& marker_viewer
		);


	//! 設定ファイルの読み込み
	/*!
	\param[in] config_name 設定ファイル名
	\param[out] input_dir 画像格納フォルダ名
	\param[out] outputname 出力テキストファイル名
	\param[out] display_scale 画像の表示スケール
	\return ファイル読み込みの成否
	*/
	static bool loadConfiguration(const std::string& config_name,
		std::string& input_dir, std::string& outputname,
		MarkerViewer& marker_viewer
		);

	bool Load(const std::string& image_dir, const std::string& anno_file);
	bool LoadAnnotationFile(const std::string& anno_file);

	//! 前のフレームのマーカーを現フレームにコピー
	void CopyFormerMarkers();

	//! アノテーションで画像を切り取って保存
	void CropAndSaveImages(const std::string& dir_name);

	//! アノテーションファイルを整形して出力
	bool ExportAnnotationFile(const std::string& filename);

private:
	std::string _input_dir;	// 入力フォルダ
	std::string _annotation_file;	// 出力ファイル

	std::vector<std::string> _file_list;	// 画像ファイルへのパス
	std::vector<std::vector<cv::Rect>>	_rectlist;	// 各画像のアノテーション
	MarkerViewer _marker_viewer;	// Viewerクラス

	int _image_idx;		// 現在参照している画像ID


	//! アノテーションの並び替え
	/*!
	ロードされたアノテーションに対応する画像ファイル名が、参照画像ファイル名と対応するように並び替え
	\param[in] loaded_img_list 入力画像リスト
	\param[in] loaded_annotation 読み込まれたアノテーション
	\param[in] ref_img_list 参照アノテーション
	\return 整理されたアノテーション
	*/
	static std::vector<std::vector<cv::Rect>> reorderAnnotation(const std::vector<std::string>& loaded_img_list,
		const std::vector<std::vector<cv::Rect>>& loaded_annotation,
		const std::vector<std::string>& ref_img_list);


};

#endif