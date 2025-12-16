📘 **《GTK3 中文教學書》

# 第 2 章：GTK 物件系統（Widget、Signal、Property）深入解析**

# 🟥 2.1 GTK → GObject 物件系統簡介
GTK3 是用 C 編寫，但它不是一般的 C 程式架構。
它採用完整的物件導向模型（Object-Oriented System）：
* 類別（Class）
* 物件（Instance）
* 屬性（Property）
* 訊號（Signal）
* 繼承（Inheritance）
* 方法（Virtual functions）
這整套稱為 GObject 系統。

你在 GTK 看到的所有 widget：
* GtkWindow
* GtkButton
* GtkLabel
* GtkBox
* GtkStack
* GtkDialog

全部都是 GObject。

# 🟥 2.2 GTK 物件的繼承關係（很關鍵！）
```
GObject
  └── GInitiallyUnowned
        └── GtkWidget
              └── GtkContainer
                    └── GtkBin
                          └── GtkWindow
```
Button
```
GObject
  └── GInitiallyUnowned
        └── GtkWidget
              └── GtkContainer
                    └── GtkBin
                          └── GtkButton

```
這代表：
* GtkButton 是 GtkWidget
* GtkWindow 是 GtkWidget
* 所有 widget 都能呼叫 gtk_widget_show()
* GtkButton 繼承 GtkWidget 的 signal 與 property
* GtkContainer 可以包含其他 widget（Button 就不行 → 所以繼承 GtkContainer 的才可以）

# 🟦 2.3 Widget 是什麼？
Widget = 視窗元件
每個 widget 是 GObject 的 instance。
```
GtkWidget *btn = gtk_button_new_with_label("OK");
```
這行會：
* 建立 GtkButton instance
* 設定它的 label property
* 回傳一個 GtkWidget*（因為繼承 GtkWidget）
* 你看到的所有 widget 都是 instance：

# 🟦 2.4 Signals（訊號）是 GTK 的事件機制
Signal = 事件，例如：
* Button clicked
* Window destroy
* Key pressed
* Mouse event
* Value changed

語法：
```
g_signal_connect(btn, "clicked", G_CALLBACK(on_clicked), NULL);
```
等同於：

「當按鈕被點擊，呼叫 on_clicked()」

⭐ Signals 的完整構造
Signal 有三項：
* emitter → widgets emit signals
* signal name → string 形式，如 "clicked"
* callback function
例如 Button：
```
void on_clicked(GtkButton *btn, gpointer user_data) {
    printf("clicked!\n");
}
```
連接：
```
g_signal_connect(btn, "clicked", G_CALLBACK(on_clicked), NULL);
```
⭐ Signal 與事件迴圈整合
GTK 事件迴圈（gtk_main）會：
* 等待 X11/Wayland event
* 轉換成 GTK signal
* 呼叫 callback

所以 GUI 是 event-driven（事件驅動式），不是 while loop 。

# 🟦 2.5 Properties（屬性）是 GTK 物件參數
每個 widget 都有屬性，可以用：
✔ setter
```
gtk_window_set_title(window, "Hello");
```
✔ getter
```
gtk_window_get_title(window);
```
✔ 通用方法
設定 property：
```
g_object_set(window, "title", "Hello", NULL);
```
取得 property：
```
char *title;
g_object_get(window, "title", &title, NULL);
```
常用 properties：
| Widget      | Property |
|:------------|:-----------------------------|
|GtkWindow| title, default-width, resizable |
|GtkLabel | label, selectable |
|GtkButton | label, relief |
|GtkImage | icon-name, pixel-size |
|GtkStack | visible-child |

# 🟦 2.6 Widgets + Signals + Properties 如何一起工作？
以 Button 為例：
```
GtkWidget *btn = gtk_button_new_with_label("Press");

// 設定屬性
g_object_set(btn, "relief", GTK_RELIEF_NONE, NULL);

// 設定 signal handler
g_signal_connect(btn, "clicked", G_CALLBACK(on_click), NULL);
```
# 🟦 2.7 Container（容器）是布局的基礎
Container 是可以包含其他 widget 的 widget。
例子：
* GtkBox（水平/垂直排列）
* GtkGrid（表格排列）
* GtkStack（多畫面）
* GtkScrolledWindow（捲軸）
```
gtk_container_add(GTK_CONTAINER(window), button);
```
# 🟦 2.8 訊號參數與 callback 格式
每個 signal 有固定格式：
Button clicked:
```
void on_clicked(GtkButton *btn, gpointer user_data)
```
Window destroy:
```
void on_destroy(GtkWidget *window, gpointer user_data)
```
Key press:
```
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
```
# 🟦 2.9 Reference Counting（GTK 的記憶體管理）
GTK 不是用 free()，也不是用 new/delete，而是：
✔ 增加引用計數：
```
g_object_ref(obj);
```
✔ 減少引用計數：
```
g_object_unref(obj);
```
當計數 = 0 → GTK 自動 free。
自訂類別（GObject subclass）需要理解生命週期。

# 🟦 2.10 自訂 Widget（ExampleAppWindow）如何產生？
```
G_DEFINE_TYPE_WITH_PRIVATE(ExampleAppWindow, example_app_window, GTK_TYPE_APPLICATION_WINDOW);
```
這行會：
* 建立一個 ExampleAppWindow class
* 讓它繼承 GtkApplicationWindow
* 自動加入 private struct
* 產生 type id（類別識別碼）
instance 初始化：
```
static void example_app_window_init(ExampleAppWindow *win) {
    // 初始化 private data
}
```
class 初始化：
```
static void example_app_window_class_init(ExampleAppWindowClass *klass) {
    // override functions, signals, properties
}
```
# 🟥 2.11 本章小結
你現在理解：
✔ GTK = 以 GObject 為核心的 OOP 系統
✔ Widget 是 GObject instance
✔ Container 排版
✔ Signal = 事件 callback
✔ Properties = 可設定/查詢的屬性
✔ GTK 使用 reference counting
✔ ExampleAppWindow 是 GObject subclass