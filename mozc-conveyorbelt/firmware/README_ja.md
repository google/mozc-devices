# ファームウェア開発ガイド

キーボードの組み立て全体については[ビルドガイド](../buildguide_ja.md)を参照してください。

## ファイル一覧

-   `prebuilt/` : 事前にビルドしたファームウェア
-   `keymap.h` : キーマップ定義
-   `main.c` : メインチップ用のソースファイル
-   `makefile` : ビルド設定
-   `switches.h` / `switches.c` : キースイッチおよびシフトレジスタ制御用ソースファイル
-   `chlib/` : 共通ライブラリ（ビルド時に自動取得）

## 事前にビルドしたファームウェア

`prebuilt/` 以下に事前にビルドしたファームウェア（`mozc.bin`）を収めていますので、変更が不要の場合はこれをそのまま用いることができます。

基板上の `SW4`（BOOT スイッチ）を押しながら USB
ケーブルを接続してブートローダーモードに入り、[ch559flasher](https://github.com/toyoshim/ch559flasher)
を用いて書き込みます。

```sh
ch559flasher -w prebuilt/mozc.bin
ch559flasher -b
```

書き込みがうまくいかない場合（デバイスが認識されない、USB ドライバの設定が必要な場合など）やツールの導入が難しい場合は、WCH
公式の開発ツール（[WCHISPTool](http://www.wch.cn/downloads/WCHISPTool_Setup_exe.html)）を使用して書き込んでください。

## 独自のファームウェア開発の手引き

### ビルド環境の準備

ファームウェアのコンパイルには [SDCC](https://sdcc.sourceforge.net/) を、書き込みには
[ch559flasher](https://github.com/toyoshim/ch559flasher) を使用します。

-   **Debian / Ubuntu**:

    ```sh
    sudo apt install sdcc binutils
    ```
-   **Windows**:

    ```powershell
    winget install sdcc
    ```

ch559flasher の手動インストール（要 Rust / Cargo）：

```sh
cargo install --git https://github.com/toyoshim/ch559flasher.git
```

※ 未インストールの場合は `make program` 実行時にも自動取得を試みます。

### ビルドと書き込み

`make` を実行すると、必要なライブラリ（`chlib`）が自動的にクローンされ、ビルドが行われます。`ch559flasher` が未インストールの場合は
`make program` 実行時に自動取得を試みます。

```sh
# ビルド
make

# 書き込み（SW4 を押しながら USB を接続した状態で実行）
make program

# 書き込みと実行
make run
```

### 標準出力について

CH559L の UART0（TXD: P0.3）から、速度 115200bps でデバッグ用の標準出力が出力されています。基板上の `TXD`
ランドにシリアル変換器を接続することでログを確認できます。

### キーマップの変更について

キーマップを変更したい場合は、`keymap.h` 内の `keymap` 配列を編集してください。各キーには HID Usage ID と Shift
フラグが割り当てられています。
