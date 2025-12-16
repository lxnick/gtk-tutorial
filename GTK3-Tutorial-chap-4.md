📘 **《GTK3 中文教學書》

# ▶️ 第 4 章：GTK3 Layout（GtkBox / GtkGrid / GtkStack / GtkScrolledWindow）**

# 🟥 4.1 為什麼 Layout 這麼重要？
GTK3 與 Qt、Swing 一樣，使用排版容器（Container Widget）管理 UI 配置。
你不能像 Win32 API 那樣用絕對座標放按鈕：  
```
button.x = 100; 
button.y = 200;  
```
GTK 不允許這樣的 API (GtkFixed 也有，但不建議用)  
GTK 要求你使用：
```
    Box（水平/垂直排列）
    Grid（表格排版）
    Stack（多畫面切換）
    ScrolledWindow（可捲動視窗）
    Notebook（Tab 介面）
```
這些讓你的 UI：
* 自動調整大小
* 在不同螢幕上呈現正確排版
* 在語言不同時也能對齊（中文字 vs 英文字）
* 在 Raspberry Pi 小螢幕也能正常顯示

# 🟥 4.2 GtkBox — GTK 最常用的容器（水平/垂直排版）
✔ Horizontal Box（水平排版）
<object class="GtkBox" id="hbox">
  <property name="orientation">horizontal</property>
  <property name="spacing">8</property>
</object>

✔ Vertical Box（垂直排版）
<object class="GtkBox" id="vbox">
  <property name="orientation">vertical</property>
  <property name="spacing">6</property>
</object>

# 🟩 4.2.1 用 C 建立 GtkBox
```
GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
gtk_container_add(GTK_CONTAINER(win), box);
加入按鈕：
gtk_box_pack_start(GTK_BOX(box), btn1, FALSE, FALSE, 0);
gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 0);
```
# 🟩 4.2.2 用 GtkBuilder（推薦方式）
```
<object class="GtkBox" id="main_box">
  <property name="orientation">vertical</property>
  <property name="spacing">10</property>

  <child>
    <object class="GtkLabel" id="lbl_title">
      <property name="label">Calibration Tool</property>
    </object>
  </child>

  <child>
    <object class="GtkButton" id="btn_start">
      <property name="label">Start Calibration</property>
    </object>
  </child>
</object>
```
# 🟩 4.2.3 GtkBox 的重要屬性
|屬性         | 說明 |
|:-----------|-----|
|spacing     |控制每個子元件間距 |
|margin	     |控制外圍的留白 |
|homogeneous |	所有子元件平均分配空間 |
|expand	     |子元件是否填滿剩餘空間 |
|fill	     |是否填滿自己在 Box 的空間 |

例如：
gtk_box_pack_start(GTK_BOX(box), widget, TRUE, TRUE, 0);
= expand + fill
# 🟥 4.3 GtkGrid — 表格排列（比 Box 更精準）
常用於：
* 設定視窗
* Form 表單
* Label + Entry 搭配排版
* 需要對齊欄位時

# 🟩 4.3.1 建立 GtkGrid
```
<object class="GtkGrid" id="grid">
  <property name="row-spacing">6</property>
  <property name="column-spacing">10</property>
</object>
```
C 程式：
```
GtkWidget *grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
gtk_container_add(GTK_CONTAINER(win), grid);
```
# 🟩 4.3.2 放兩個元件（欄與列）
gtk_grid_attach(GTK_GRID(grid), lbl, 0, 0, 1, 1); // col=0, row=0
gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

很適合表單：
* Label	Entry
* Name	[ Entry ]
* Age	[ Entry ]

# 🟥 4.4 GtkStack — 多畫面（頁面切換）
GtkStack 是：
* 可以放多個畫面
* 每次顯示其中之一
* 搭配 GtkStackSwitcher 可做頁面切換（像 Chrome tab）  
非常適合：
* 設定頁（General / Advanced）
* 校正工具（Step1 / Step2 / Step3）
* Wizard（引導式 UI）
# 🟩 4.4.1 GtkBuilder 設定 Stack# 
```
<object class="GtkStack" id="stack">
  <property name="transition-type">slide-left-right</property>

  <child>
    <object class="GtkLabel" id="page1">
      <property name="label">Page One</property>
    </object>
    <attributes>
      <attribute name="title">Page1</attribute>
    </attributes>
  </child>

  <child>
    <object class="GtkLabel" id="page2">
      <property name="label">Page Two</property>
    </object>
    <attributes>
      <attribute name="title">Page2</attribute>
    </attributes>
  </child>
</object>
```
# 🟩 4.4.2 用程式切換頁面
gtk_stack_set_visible_child_name(GTK_STACK(stack), "page2");

# 🟩 4.4.3 使用 StackSwitcher（常見於 GNOME app）

GtkBuilder：

<object class="GtkStackSwitcher" id="switcher">
  <property name="stack">stack</property>
</object>

效果：
* 左側或上方出現 tab-like UI
* 自動切換 stack 的 page

# 🟥 4.5 GtkScrolledWindow — 可捲動視窗

若 UI 過大，就放入一個 ScrolledWindow。

XML：
```
<object class="GtkScrolledWindow" id="scroll">
  <child>
    <object class="GtkBox" id="content_box">
      <property name="orientation">vertical</property>
    </object>
  </child>
</object>
```
程式會自動加 scrollbar。
非常適合：
* 長設定頁面
* 多行文字輸入
* 表格（TreeView/ListBox）
# 🟥 4.6 Layout 實戰：製作校正工具的主畫面
你會需要：  
✔ 上方：標題（GtkLabel）  
✔ 中間：感測軸數值（Grid）  
✔ 右側：按鈕（Box）  
✔ 下方：切換不同模式（Stack + StackSwitcher）  

典型 GtkBuilder：
```
<object class="GtkGrid" id="root">
  <property name="row-spacing">6</property>
  <property name="column-spacing">6</property>

  <!-- StackSwitcher -->
  <child>
    <object class="GtkStackSwitcher" id="switcher">
      <property name="stack">stack</property>
    </object>
    <packing>
      <property name="left-attach">0</property>
      <property name="top-attach">0</property>
      <property name="width">2</property>
    </packing>
  </child>

  <!-- 左側 page content -->
  <child>
    <object class="GtkStack" id="stack">
      <child>
        <object class="GtkBox" id="page_live">
          <property name="orientation">vertical</property>
        </object>
        <attributes>
          <attribute name="title">Live Axis</attribute>
        </attributes>
      </child>

      <child>
        <object class="GtkBox" id="page_settings">
          <property name="orientation">vertical</property>
        </object>
        <attributes>
          <attribute name="title">Settings</attribute>
        </attributes>
      </child>
    </object>

    <packing>
      <property name="left-attach">0</property>
      <property name="top-attach">1</property>
    </packing>
  </child>

  <!-- 右側按鈕列 -->
  <child>
    <object class="GtkBox" id="button_box">
      <property name="orientation">vertical</property>
      <property name="spacing">6</property>
    </object>

    <packing>
      <property name="left-attach">1</property>
      <property name="top-attach">1</property>
    </packing>
  </child>

</object>
```
# 🟥 4.7 Layout 設計原則（重要）
|原則 | 說明 |
|:-----|:-----|
|避免絕對座標 |	不要使用 GtkFixed |
|大型介面用 Grid |	讓元件對齊自然、清楚 |
|工具按鈕放在垂直 Box |	常見於設定工具 |
|多畫面用 Stack |	最乾淨的架構 |
|捲動區域用 ScrolledWindow | 避免 UI 塞不下 |
|每個大區塊都用 margin | UI 更美觀 |

🟥 4.8 本章小結
本章你已經學會：
✔ GtkBox 水平/垂直排版  
✔ GtkGrid 表格排版  
✔ GtkStack 多畫面切換  
✔ GtkScrolledWindow 捲軸容器  
✔ 如何利用 GtkBuilder 建立複雜 UI  
✔ 校正工具主畫面應如何排版  

