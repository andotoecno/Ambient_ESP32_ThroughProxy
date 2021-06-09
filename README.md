# Ambient_ESP32_ThroughProxy
作成者:中島 優作
作成日:	2020年1月22日

学校などでプロキシがあってAmbientにデータを送れない！人向けの送信専用ライブラリです。
ESP32、M5Stackで使うことを前提としています。

## 使い方
最初に初期化関数を呼び(普通はsetup()関数内)、送信時に送信関数を呼ぶ。
チャンネルIDやライトキーを変更するときは初期化関数を再び呼ぶ。(setup関数でなくても構わない。)

- 初期化関数
AmbientのチャンネルID、ライトキー、及びプロキシサーバーのホスト名を設定する。
void AmbientInitialize(String ID, String key, String proxy);
	ID	AmbientのチャンネルID
	key	Ambientのライトキー
	proxy	プロキシサーバーのホスト名
	(学校のは「proxy.asahikawa-nct.ac.jp」。「http://」はいらない。)
	(設定しない場合は空文字「""」を書いておく。)

- 送信関数
Ambientにデータを送信する。
プロキシを通す場合と通さない場合で関数が異なる。

  - プロキシを通さな*い場合
  int AmbientUpload(int dNum, float dValue);
  	dNum	Ambientの「データー1～8」の番号		
  	dValue	送信する値
  	返り値	100以上の値はレスポンスコード(200番台なら成功)
  		-1はサーバーへの接続失敗
  		0はタイムアウト
  - プロキシを通す場合
  int AmbientUploadProxy(int dNum, float dValue);
  	dNum	Ambientの「データー1～8」の番号		
  	dValue	送信する値
  	返り値	100以上の値はレスポンスコード(200番台なら成功)
  		-1はサーバーへの接続失敗
  		0はタイムアウト

--------------------------
バージョンログ

2020年1月22 ： 	Ambient_ESP32_ThroughProxy作成

2020年1月22 ： 	Ambient_ESP32_ThroughProxy(ver1.2)作成
		・送信データを整数のみから小数にも対応できるようにした


--------------------------
参考文献
- http://mochikun.hatenablog.com/entry/2015/10/19/esp-wroom-02%25e3%2581%25a7%25e6%25b8%25a9%25e6%25b9%25bf%25e5%25ba%25a6%25e3%2582%25bb%25e3%2583%25b3%25e3%2582%25b5%25e3%2583%25bc%25e6%2583%2585%25e5%25a0%25b1%25e3%2582%2592att-Ambient%25e3%2581%25ab
- https://techtutorialsx.com/2019/01/30/esp8266-arduino-http-put-request/
- https://garretlab.web.fc2.com/arduino/esp32/reference/libraries/HTTPClient/HTTPClient_begin.html
- http://miha.jugem.cc/?eid=158
- https://gist.github.com/kudarisenmon/6ca17c9182b3c9281e102df2483a225c