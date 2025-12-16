📘 **《GTK3 中文教學書》

# ▶️第 6 章：Dialog（訊息、檔案、確認、設定視窗）**

🎯 本章目標
* 正確使用 GtkDialog 家族
* 顯示 訊息 / 警告 / 錯誤 / 確認 對話框
* 使用 檔案選擇視窗（Open / Save）
* 建立 設定（Preferences）視窗
* 把 Dialog 正確整合進 GtkApplication + GtkBuilder 架構
* 為你的 Gamepad Calibration Tool 做出專業互動流程

# 🟥 6.1 什麼是 Dialog？
* Dialog（對話框）是：
* 暫時性的視窗
* 用來 詢問使用者 / 顯示結果 / 取得輸入
* 通常是 Modal（模式化） → 使用者必須先處理它

GTK3 的 Dialog 都繼承自：
```
GtkDialog → GtkWindow → GtkWidget → GObject
```
# 🟥 6.2 GtkDialog 的基本概念
✔ Dialog 的三個組成部分
* Title bar（標題）
* Content area（內容區）
* Action area（按鈕列）

✔ Dialog 的回傳值（Response ID）
* Dialog 不是靠 callback 回傳結果，而是：
```
int response = gtk_dialog_run(GTK_DIALOG(dialog));
```
回傳值常見為：
|回傳值	|意義|
|--------------------|--------|
|GTK_RESPONSE_OK	|使用者確認|
|GTK_RESPONSE_CANCEL |	取消 |
|GTK_RESPONSE_YES	|是 |
|GTK_RESPONSE_NO	|否 |
|GTK_RESPONSE_ACCEPT |	接受 |
|GTK_RESPONSE_REJECT |	拒絕 |

# 🟥 6.3 最基本的 GtkDialog 範例
C:
```
GtkWidget *dialog;

dialog = gtk_dialog_new_with_buttons(
    "Confirm",
    GTK_WINDOW(parent),
    GTK_DIALOG_MODAL,
    "_OK", GTK_RESPONSE_OK,
    "_Cancel", GTK_RESPONSE_CANCEL,
    NULL
);

gtk_widget_show_all(dialog);

int res = gtk_dialog_run(GTK_DIALOG(dialog));

if (res == GTK_RESPONSE_OK) {
    g_print("User pressed OK\n");
}

gtk_widget_destroy(dialog);
```
# 🟥 6.4 GtkMessageDialog（最常用！）
🟦 用途
* 提示訊息
* 顯示錯誤
* 警告使用者
* 確認操作

可用 message type：
|類型	|說明|
|------|------|
|GTK_MESSAGE_INFO	|資訊|
|GTK_MESSAGE_WARNING	|警告|
|GTK_MESSAGE_ERROR	|錯誤|
|GTK_MESSAGE_QUESTION	|問題|

##  🟩 6.4.1 資訊對話框（Info）
```
GtkWidget *dlg = gtk_message_dialog_new(
    GTK_WINDOW(parent),
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_INFO,
    GTK_BUTTONS_OK,
    "Calibration finished successfully!"
);

gtk_dialog_run(GTK_DIALOG(dlg));
gtk_widget_destroy(dlg);

```
## 🟩 6.4.2 警告 / 錯誤對話框
```
GtkWidget *dlg = gtk_message_dialog_new(
    GTK_WINDOW(parent),
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_ERROR,
    GTK_BUTTONS_OK,
    "Device not found!"
);
```
## 🟩 6.4.3 確認對話框（Yes / No）
```
GtkWidget *dlg = gtk_message_dialog_new(
    GTK_WINDOW(parent),
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_QUESTION,
    GTK_BUTTONS_YES_NO,
    "Start calibration now?"
);

int res = gtk_dialog_run(GTK_DIALOG(dlg));
gtk_widget_destroy(dlg);

if (res == GTK_RESPONSE_YES) {
    start_calibration();
}
```
# 🟥 6.5 GtkFileChooserDialog（開啟 / 儲存檔案）
## 🟩 6.5.1 開啟檔案
```
GtkWidget *dlg = gtk_file_chooser_dialog_new(
    "Open File",
    GTK_WINDOW(parent),
    GTK_FILE_CHOOSER_ACTION_OPEN,
    "_Cancel", GTK_RESPONSE_CANCEL,
    "_Open", GTK_RESPONSE_ACCEPT,
    NULL
);

if (gtk_dialog_run(GTK_DIALOG(dlg)) == GTK_RESPONSE_ACCEPT) {
    char *filename;
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dlg));
    g_print("Selected file: %s\n", filename);
    g_free(filename);
}

gtk_widget_destroy(dlg);
```
## 🟩 6.5.2 儲存檔案

只要改成：

GTK_FILE_CHOOSER_ACTION_SAVE


並加上：

gtk_file_chooser_set_do_overwrite_confirmation(
    GTK_FILE_CHOOSER(dlg), TRUE);

# 🟥 6.6 GtkAboutDialog（關於視窗）    
```
GtkWidget *dlg = gtk_about_dialog_new();

gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dlg), "Gamepad Tool");
gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dlg), "1.0");
gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dlg),
    "Joystick Calibration Utility");

gtk_dialog_run(GTK_DIALOG(dlg));
gtk_widget_destroy(dlg);
```

# 🟥 6.7 使用 GtkBuilder 建立 Dialog（專業作法）
## 🟩 6.7.1 Dialog UI XML
```
<object class="GtkDialog" id="prefs_dialog">
  <property name="title">Preferences</property>

  <child internal-child="content_area">
    <object class="GtkBox">
      <property name="orientation">vertical</property>
      <property name="spacing">6</property>

      <child>
        <object class="GtkCheckButton" id="chk_auto_start">
          <property name="label">Auto start calibration</property>
        </object>
      </child>

      <child>
        <object class="GtkSpinButton" id="spin_deadzone"/>
      </child>

    </object>
  </child>

  <child internal-child="action_area">
    <object class="GtkButton">
      <property name="label">Close</property>
      <signal name="clicked" handler="on_prefs_close"/>
    </object>
  </child>
</object>
```
## 🟩 6.7.2 C 程式載入 Dialog
```
GtkBuilder *builder = gtk_builder_new_from_file("ui/preferences.ui");

GtkWidget *dlg =
  GTK_WIDGET(gtk_builder_get_object(builder, "prefs_dialog"));

gtk_window_set_transient_for(GTK_WINDOW(dlg), GTK_WINDOW(parent));
gtk_window_set_modal(GTK_WINDOW(dlg), TRUE);

gtk_builder_connect_signals(builder, NULL);

gtk_widget_show_all(dlg);
```
# 🟥 6.8 Modal vs Non-modal Dialog
|類型|	說明|
|----------|----------|
|Modal|	使用者必須先處理|
|Non-modal|	可同時操作主視窗|

設定方式：
```
gtk_window_set_modal(GTK_WINDOW(dlg), TRUE);
```
# 🟥 6.9 Dialog 的最佳實務（非常重要）
|建議|	說明|
|---------|----------|
|Dialog 一定要有 parent|	避免視窗跑到背景|
|用 MessageDialog 顯示錯誤|	快速又一致|
|複雜 Dialog 用 GtkBuilder|	可維護性高|
|Dialog 結束後 destroy|	避免記憶體累積|
|校正流程用 Question Dialog|	避免誤操作|

# 🟥 6.10 校正工具實戰流程（Dialog 設計）
# 🟥 6.11 本章小結
你現在已經掌握：  
✔ GtkDialog 核心模型  
✔ GtkMessageDialog（最重要）  
✔ 檔案選擇視窗  
✔ About Dialog  
✔ GtkBuilder Dialog  
✔ Modal / Parent / Response 概念  

