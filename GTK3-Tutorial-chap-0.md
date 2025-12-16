# Chapter 0 Introduction to GTK
# 🟦 0.1 GTK 是什麼？
GTK 全名 GIMP Toolkit，原本用於影像處理軟體 GIMP  
之後成為：  
* GNOME 桌面環境的官方 GUI Toolkit
* Linux 世界最常見的 GUI Library 之一（另一個是 Qt）
* 跨平台：支援 Linux / Windows / macOS（macOS 支援較弱）    

GTK 提供：  
✔ 視窗（GtkWindow）  
✔ 按鈕（GtkButton）  
✔ 排版容器（GtkBox, GtkGrid）  
✔ 輸入框（GtkEntry）  
✔ 對話框（GtkDialog）  
✔ 表格（GtkTreeView, GtkListBox）  
✔ 多畫面切換（GtkStack）  
✔ CSS 樣式（可自訂 UI）  
✔ Menu / Action / Shortcuts  
✔ UI Builder（XML 介面檔）  

GTK 是 C 語言開發，但其實是：
* 面向物件（GObject）  
* 信號/事件導向模型（Signals）  
* 可綁定其他語言（Python、Rust、C++、Vala、JavaScript）  

🟦 0.2 GTK3 vs GTK4：你該選哪一個？  
| 特性	        |       GTK3|        GTK4|  
|:--------------|-----------:|--------------:| 
|成熟度	         |  ★★★★★|     ★★★★ |
|文件/範例       |	★★★★★|	   ★★★ |
|嵌入式支援      |	★★★★★|     ★★★ |
|Framebuffer/GUI| 很適合	|       不適合 |
|效能需求	     | 低	     |高，需要 GPU |
|未來方向	     |穩定維護   | 	主要開發方向| 

🟦 0.3 GNOME 與 GTK 的關係（理解次序很重要）
GNOME = Linux 的桌面環境

包含：
* GNOME Shell
* 設定
* 檔案管理器（Nautilus）
* 控制中心
* GNOME Terminal  

GTK = 被 GNOME 用來寫 GUI 的工具箱
但 你可以完全不使用 GNOME，只用 GTK。
例如：
* Raspberry Pi OS（LXDE） → 可以跑 GTK3
* Ubuntu XFCE → 可以跑 GTK3
* Embedded Linux（無桌面） → 用 GTK3 + framebuffer

GTK3 ≠ GNOME
GTK3 = 一個 GUI 庫（像 Qt）。

🟦 0.4 GTK3 的架構（理解這個很重要）
GTK3 程式由三大核心組成：
🟩 1. GObject（物件系統）
GTK3 是用 C 寫的，但提供完整 OO 模型：
* 類別（class）
* 實例（instance）
* 屬性（property）
* 訊號（signal）

例如：按鈕的 clicked，是一種 signal。
你會看到常見 API：
```
g_signal_connect(button, "clicked", G_CALLBACK(on_click), NULL);
```
🟩 2. Widgets（視窗元件）  
GTK3 的 UI 全都是 widget：
* GtkWindow
* GtkButton
* GtkLabel
* GtkBox
* GtkGrid
* GtkDialog
* GtkStack
* GtkNotebook
* GtkTreeView

每個 widget 都：
* 是一個 GObject
* 有屬性
* 有 signal
* 可被 GtkBuilder 建立

🟩 3. GtkBuilder（UI XML 系統）  
GTK 支援將 UI 寫成 XML（你可以用 Glade 製作）  
```
<object class="GtkButton" id="btn_start">
  <property name="label">Start</property>
</object>
```
然後 C 程式載入：
```
GtkBuilder *b = gtk_builder_new_from_file("ui/main.ui");
GtkWidget *btn = GTK_WIDGET(gtk_builder_get_object(b, "btn_start"));
```
🟦 0.5 GTK3 的應用程式架構（GtkApplication）  
GTK 建議你用 GtkApplication 來寫程式
```
int main() {
    GtkApplication *app = gtk_application_new("org.example.app", 0);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), 0, NULL);
}
```
activate callback 負責建立 UI：
```
void on_activate(GtkApplication *app) {
    GtkWidget *win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Hello");
    gtk_widget_show_all(win);
}
```

🟦 0.6 GTK3 是事件迴圈 GUI（Event-driven GUI）
GTK 使用主事件迴圈：
```
    gtk_main();
```
它會：
* 處理滑鼠事件
* 處理按鍵事件
* 更新畫面
* 呼叫 signal handlers
* 當視窗被關閉時，你會呼叫：
```
    gtk_main_quit();
```

🟦 0.7 GTK3 需要哪些工具？（開發環境）  
常見開發工具：  
✔ pkg-config
查詢編譯參數
```
    pkg-config --cflags --libs gtk+-3.0
```
✔ Glade（GTK UI Builder 編輯器）  
可視化製作 UI XML。  
✔ Meson / Makefile  
建置系統。
✔ gtk3-demo  
GTK3 Widget 範例瀏覽器。

🟦 0.8 第一個 GTK3 程式應該怎麼寫？
```
#include <gtk/gtk.h>

static void activate(GtkApplication *app) {
    GtkWidget *win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Hello GTK3");
    gtk_widget_show_all(win);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.example.hello", 0);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
```
編譯
```
gcc main.c -o hello $(pkg-config --cflags --libs gtk+-3.0)
```
🟦 0.9 GTK3 學習地圖（重要！）
本教材將帶你依照以下順序學習：
1. GTK 核心架構（GObject / Widget / Signals）
2. GtkApplication → ExampleApp（官方架構）
3. GtkBuilder（UI XML）
4. Layout（Box, Grid, Stack）
5. Widgets
6. Dialog
7. Menu + Action
8. CSS（美化 UI）
9. ListView（資料呈現 UI）
10. 專案建置（Makefile、Meson）
11. 嵌入式 Linux / Raspberry Pi 開發
12. 完整實作（Gamepad Calibration Tool）

學完，你會能：
* 為嵌入式 Linux 製作完整 GUI
* 寫出標準 GNOME 風格 GTK UI
* 使用 GtkBuilder 分離 UI/邏輯
* 用 Meson 建構大型專案
* 開發工具型應用（如校正程式）

🟦 0.10 第 0 章小結  
你現在已經理解 GTK3 的：
✔ 定位
✔ 架構
✔ 工具
✔ 程式流程
✔ 使用方式
✔ 與 GNOME 的關係