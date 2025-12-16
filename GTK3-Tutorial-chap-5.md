📘 **《GTK3 中文教學書》

# ▶️第 5 章：GTK 常用 Widget（Button、Label、Entry、ComboBox…）**
🎯 本章目標
* 正確選擇合適的 widget
* 用 GtkBuilder（UI XML） 建立 UI
* 在 C 程式中取得 widget、設定屬性、處理 signal
* 寫出完整的工具型 GUI（設定頁、校正頁、控制頁）

# 🟥 5.1 GtkButton — 按鈕（最常用）
🟦 用途
* 觸發動作
* 確認 / 取消
* 開始 / 停止
* 套用設定

XML:
```
<object class="GtkButton" id="btn_start">
  <property name="label">Start</property>
</object>

```
C:
```
static void on_start_clicked(GtkButton *btn, gpointer user_data) {
    g_print("Start pressed\n");
}
...
GtkWidget *btn =
  GTK_WIDGET(gtk_builder_get_object(builder, "btn_start"));

g_signal_connect(btn, "clicked",
                 G_CALLBACK(on_start_clicked), NULL);
```
🟨 常用屬性
|Property | 說明 |
|:---------------|:---------|
|label	|按鈕文字|
|sensitive	|是否可點擊 |
|relief	|外框樣式 |
|always-show-image	|顯示 icon |

# 🟥 5.2 GtkLabel — 文字顯示
🟦 用途
* 顯示標題
* 顯示狀態
* 顯示數值（Axis、狀態文字）  

XML:
```
<object class="GtkLabel" id="lbl_status">
  <property name="label">Idle</property>
</object>
```
C:
```
GtkWidget *lbl =
  GTK_WIDGET(gtk_builder_get_object(builder, "lbl_status"));

gtk_label_set_text(GTK_LABEL(lbl), "Running");
```
🟨 常用屬性
|Property | 說明 |
|:---------------|:---------|
|label	|顯示文字|
|selectable	|是否可選取 |
|xalign / yalign	|對齊方式 |
|wrap	|自動換行 |
# 🟥 5.3 GtkEntry — 單行文字輸入
🟦 用途
* 輸入數值
* 輸入名稱
* 輸入參數

XML:
```
<object class="GtkEntry" id="entry_name">
  <property name="placeholder-text">Enter name</property>
</object>
```
C:
```
g_signal_connect(entry, "changed",
                 G_CALLBACK(on_entry_changed), NULL);
...
static void on_entry_changed(GtkEntry *entry, gpointer data) {
    g_print("Text: %s\n", gtk_entry_get_text(entry));
}
...
GtkEntry *entry =
  GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));

const gchar *text = gtk_entry_get_text(entry);
```
🟨 常用屬性
|Property | 說明 |
|:---------------|:---------|
|placeholder-text	|提示文字|
|visibility	|密碼欄位 |
|max-length	|最長長度 |
|editable	|是否可輸入|
# 🟥 5.4 GtkCheckButton — 勾選框（Boolean 設定）
🟦 用途
* Enable / Disable
* 開關設定

XML:
```
<object class="GtkCheckButton" id="chk_enable">
  <property name="label">Enable feature</property>
</object>
```
C:
```
GtkToggleButton *chk =
  GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "chk_enable"));

gboolean enabled = gtk_toggle_button_get_active(chk);
...
g_signal_connect(chk, "toggled",
                 G_CALLBACK(on_enable_toggled), NULL);
```

# 🟥 5.5 GtkComboBoxText — 下拉選單（選項選擇）
🟦 用途
* 模式選擇
* 裝置選擇
* 設定值選擇

XML:
```
<object class="GtkComboBoxText" id="combo_mode">
  <items>
    <item id="0">Mode A</item>
    <item id="1">Mode B</item>
    <item id="2">Mode C</item>
  </items>
</object>
```
C:
```
GtkComboBoxText *combo =
  GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_mode"));

int index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
const gchar *text = gtk_combo_box_text_get_active_text(combo);
...
g_signal_connect(combo, "changed",
                 G_CALLBACK(on_mode_changed), NULL);
```
# 🟥 5.6 GtkSpinButton — 數值輸入（非常適合校正工具）
🟦 用途
* 數值輸入
* 校正參數
* 範圍限制

XML:
```
<object class="GtkSpinButton" id="spin_threshold">
  <property name="adjustment">
    <object class="GtkAdjustment">
      <property name="lower">0</property>
      <property name="upper">100</property>
      <property name="step-increment">1</property>
    </object>
  </property>
</object>
```
C:
```
GtkSpinButton *spin =
  GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_threshold"));

int value = gtk_spin_button_get_value_as_int(spin);
```
# 🟥 5.7 GtkScale — 滑桿（即時調整數值）
🟦 用途
* 音量
* 靈敏度
* 閥值  

XML:
```
<object class="GtkScale" id="scale_gain">
  <property name="orientation">horizontal</property>
  <property name="adjustment">
    <object class="GtkAdjustment">
      <property name="lower">0</property>
      <property name="upper">100</property>
    </object>
  </property>
</object>
```
C:
```
GtkRange *scale =
  GTK_RANGE(gtk_builder_get_object(builder, "scale_gain"));

double value = gtk_range_get_value(scale);
```
# 🟥 5.8 GtkImage — 圖示顯示
🟦 用途
* Icon
* 狀態顯示
* Logo

XML:
```
<object class="GtkImage" id="img_icon">
  <property name="icon-name">media-playback-start</property>
  <property name="pixel-size">32</property>
</object>
```
# 🟥 5.9 Widget 組合實戰（校正工具範例）
```
<object class="GtkGrid">
  <property name="row-spacing">6</property>

  <child>
    <object class="GtkLabel">
      <property name="label">Deadzone</property>
    </object>
  </child>

  <child>
    <object class="GtkSpinButton" id="spin_deadzone"/>
  </child>

  <child>
    <object class="GtkCheckButton" id="chk_invert">
      <property name="label">Invert Axis</property>
    </object>
  </child>
</object>
```
# 🟥 5.10 Widget 選擇指南（很重要）
|需求	   |Widget|
|:--------|:-------|
|按下觸發	|GtkButton|
|顯示文字	|GtkLabel|
|輸入文字	|GtkEntry|
|On/Off	|GtkCheckButton|
|選擇項目	|GtkComboBoxText|
|輸入數字	|GtkSpinButton|
|即時調整	|GtkScale|
|顯示圖片	|GtkImage|

# 🟥 5.11 本章小結
✔ GTK3 最常用 widget
✔ GtkBuilder + C 的正確用法
✔ Signal 處理方式
✔ 實作設定 UI 的能力
✔ 寫出完整工具型 GUI 的能力