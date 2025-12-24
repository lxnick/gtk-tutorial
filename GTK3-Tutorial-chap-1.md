# Chapter 1 First GTK application
## 🟥 1.1 準備你的 GTK3 開發環境
Ubuntu / Debian / Raspberry Pi OS：
```
# Install
$ sudo apt install libgtk-3-dev
$ sudo snap  install gtk-3-examples
# Verify  installation
$ pkg-config --modversion gtk+-3.0
3.24.x
$ pkg-config --cflags --libs gtk+-3.0
```
## 🟥 1.2 你的第一個 GTK3 程式（Hello GTK3）
[Example 01/01 Hello GTK](./example-01/example-1-1-hello.c)
```
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello GTK3");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.example.hello", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
```
## 🟥 1.3 編譯與執行
```
gcc example-1-1-hello.c -o hello $(pkg-config --cflags --libs gtk+-3.0)
./hello
```
## 🟥 1.4 理解 GtkApplication
GTK3 提供兩種方式建立應用程式：
 A. 舊方法：gtk_init()
 B. 現代方法：GtkApplication

## 🟥 1.5 GtkApplication 架構詳解
```
GtkApplication *app = gtk_application_new("app.id", 0);
g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
return g_application_run(G_APPLICATION(app), argc, argv);
```
### activate was called when 
- 程式啟動時
- 使用者從系統啟動應用程式時
- 使用者呼叫已有執行中 instance（Single Instance 功能）
### activate callback responsibble for 
- 建立主視窗
- 設定 UI
- 顯示視窗
## 🟥 1.6 完成一個 GTK3 程式所需的三大工作
1. 建立 Application（主物件）
```
app = gtk_application_new("org.example.app", 0);
```
2. 建立 Application Window（視窗）
```
GtkWidget *win = gtk_application_window_new(app);
```
3. 顯示 UI
```
gtk_widget_show_all(win);
```
## 🟥 1.7 更多簡單範例：按鈕、訊號（signal）、callback
[Example 01/02 Simple App](./example-01/example-1-2-simple.c)
```
static void on_button_clicked(GtkButton *btn, gpointer data) {
    g_print("Button pressed!\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Simple App");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    button = gtk_button_new_with_label("Press Me");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);
}
```
## 🟥 1.8 第 1 章小結
本章你已經學會：
* 如何安裝 GTK3 development package
* 如何用 pkg-config 編譯
* GtkApplication 的結構
* 如何寫第一個 GTK3 程式
* 如何建立按鈕並使用 signal callback  

這個基礎非常重要，因為：  
👉 你之後會使用 GtkBuilder（UI XML）  
👉 你會寫自己的視窗類別 ExampleAppWindow  
👉 你會做多畫面（stack）與 dialog  
👉 最後你會做完整的 Calibration Tool GUI  