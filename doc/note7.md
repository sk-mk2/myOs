## FIFOとマウス制御
int.cでやってることがよくわからんぞ
キーボードから何が打たれているかがわかるようになった。
割り込み処理は本来の仕事に割り込んで実行されるので、すぐに終わらせなきゃいけない
文字表示はかなり時間のかかる処理。
なんでかというとVRAMに８＊１６回画素を書くかどうかi文で調べ、さらにメモリへの書き込みも
ある。
ではどうするか
割り込み処理ではキーデータを変数に保存するだけで、HariMainの方でその変数をたまにチェックして、データが入って入れば表示するようにする。

できたけど、表示されるものがおかしいぞ右ctrl押した時の挙動が期待通りでない
FIFOを使ってたくさんデータを覚えられるように

HariMainでFIFOの実装があるが、データを詰める作業が無駄
なので改善
読みnextと書きnextを追加
無限に書き続ける

マウスは結構新しいデバイス
マウスの割り込み番号はIRQ12

やっとこさマウス割り込み
