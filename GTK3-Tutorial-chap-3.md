📘 **《GTK3 中文教學書》

# ▶️ 第 3 章：GtkBuilder（UI XML）與 Glade：現代 GTK GUI 的核心
GtkBuilder 是 GTK 的靈魂功能之一，你將學會：
* 如何使用 UI XML 設計視窗
* 如何使用 Glade 編輯 UI
* 如何從 C 程式載入 UI
* 如何取得 UI 元件
* 如何讓 UI 與程式碼完全分離（專業架構）

## 🟥 3.1 GtkBuilder 是什麼？為什麼它重要？
GtkBuilder 是 GTK 提供的 UI XML 載入系統 :
* 用 XML 檔描述 UI
* 用 C 程式載入 XML
* 用 gtk_builder_get_object() 取得 widget
* 用 Glade 工具可視化設計 GUI
* UI 與邏輯完全分離（類似 Qt Designer）

### 沒有 GtkBuilder：
```
GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
GtkWidget *btn = gtk_button_new_with_label("OK");
gtk_container_add(GTK_CONTAINER(win), box);
gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 0);
```
### 有 GtkBuilder：
```
xml:
<object class="GtkButton" id="btn_ok">
  <property name="label">OK</property>
</object>

c:
builder = gtk_builder_new_from_file("ui/main.ui");
btn_ok = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ok"));
```
## 🟥 3.2 建立一個最小 GtkBuilder UI 檔
example-03-1/ui/main.ui：
```
<?xml version="1.0" encoding="UTF-8"?>
<interface>
  <object class="GtkWindow" id="main_window">
    <property name="title">Hello GTK3 UI</property>
    <property name="default-width">300</property>
    <property name="default-height">200</property>

    <child>
      <object class="GtkButton" id="btn_ok">
        <property name="label">Press Me</property>
      </object>
    </child>

  </object>
</interface>
```
## 🟥 3.3 在 C 程式載入 GtkBuilder UI
example-03-1/main.c
```
#include <gtk/gtk.h>

static void on_ok_clicked(GtkButton *btn, gpointer user_data) {
    g_print("Button clicked!\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *button;

    builder = gtk_builder_new_from_file("ui/main.ui");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ok"));

    g_signal_connect(button, "clicked", G_CALLBACK(on_ok_clicked), NULL);

    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.example.builder", 0);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}
```
編譯:
```
gcc main.c -o ui_app $(pkg-config --cflags --libs gtk+-3.0)
```
## 🟥 3.4 gtk_builder_get_object() 的重要性
從 UI XML 取得 widget：
```
GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ok"));
```
只要在 XML 中設定了 id="btn_ok"：
```
<object class="GtkButton" id="btn_ok">
```
就能在 C 取出它。

## 🟥 3.5 使用 Glade 建立 UI（最實用的方式）
GTK3 的 UI 設計工具是 Glade
⚠️（GTK4 無法用 Glade → 只能用 GTK3）
安裝：
```
$ sudo apt install glade
```
啟動：
```
glade
```
你可以：
* 拖曳 widget（Button / Label / Box / Grid / Stack…）
* 設定屬性（label, spacing, margin）
* 設定 id（供程式取得）
* 設定 signals（自動呼叫 C 函式）
* 存成 XML（GtkBuilder 使用）
* 產出的 XML 就是 GtkBuilder 可讀取的格式。
## 🟥 3.6 建立更複雜的 UI（Box + Entry + Button）
example-03-2/ui/main.ui：
```
<object class="GtkWindow" id="main_window">

  <child>
    <object class="GtkBox" id="main_box">
      <property name="orientation">vertical</property>
      <property name="spacing">6</property>

      <child>
        <object class="GtkEntry" id="txt_input">
          <property name="placeholder-text">Enter text...</property>
        </object>
      </child>

      <child>
        <object class="GtkButton" id="btn_show">
          <property name="label">Show Text</property>
        </object>  
      </child>

    </object>
  </child>

</object>
```
example-03-2/main.c:
```
GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(b, "txt_input"));
GtkWidget *btn = GTK_WIDGET(gtk_builder_get_object(b, "btn_show"));

g_signal_connect(btn, "clicked", G_CALLBACK(on_show_clicked), entry);
```
callback:
```
static void on_show_clicked(GtkButton *btn, gpointer entry_ptr) {
    GtkEntry *entry = GTK_ENTRY(entry_ptr);
    const gchar *text = gtk_entry_get_text(entry);
    g_print("You typed: %s\n", text);
}
```
你現在已經能做：
* 基本 UI
* 容器
* 事件
* 步驟正確的 GtkBuilder 程式架構
## 🟥 3.7 GtkBuilder 的 signal 連接方式（進階用法）
你可以直接在 XML 裡設定 signal：
```
<signal name="clicked" handler="on_ok_clicked"/>
```
然後在 C 程式：
```
gtk_builder_connect_signals(builder, NULL);
```
必須使用：
```
G_MODULE_EXPORT void on_ok_clicked(GtkButton *btn, gpointer data);
```
這種寫法在大型應用（例如 ExampleApp）比較常用。
## 🟥 3.8 UI 與程式分離（專案架構）
典型 GTK 專案：
```
project/
 ├ src/
 │   ├ main.c
 │   ├ main_window.c
 │   └ main_window.h
 ├ ui/
 │   ├ main.ui
 │   ├ dialog.ui
 │   └ preferences.ui
 ├ data/
 │   ├ icons/
 │   └ desktop file
 ├ meson.build
 └ Makefile

```
程式碼只處理：
* 初始化
* signal callback
* 資料處理
* controller logic

而 UI 完全在 .ui 檔案。
## 🟥 3.9 GtkBuilder 的最佳實務
| 實務              | 說明 |
|:-----------------------------|------|
| UI 內部使用 id	| C 程式用 id 取得 widget |
| 避免在 C 裡大量建立 widget	| 使用 GtkBuilder 建 UI |
| 用 Box / Grid 結構化 UI |	方便修改與維護 |
| 複雜視窗拆成多個 UI 檔  | 例如 main.ui / prefs.ui / dialog.ui |
| 所有 widget 名稱清楚命名	| btn_ok、entry_name、lbl_status |
##  🟥 3.10 本章小結
* 使用 GtkBuilder UI XML  
* 使用 Glade 編輯 UI  
* 用 C 程式載入 UI  
* 用 gtk_builder_get_object 取得 widget  
* 使用 signals（XML 與 C）  
* UI 與邏輯分離  