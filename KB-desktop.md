# Collect informations
## .desktop   
🟦 1. .desktop 檔案是什麼？  
它是 Linux 桌面環境（GNOME / KDE / XFCE / LXDE / RPi PIXEL）用來：  
    - 定義應用程式  
    - 告訴桌面怎樣啟動 App  
    - 顯示 App 的名稱、圖示、分類  
    - 提供搜尋索引（GNOME Shell、KDE KRunner）  
    - 放到 Launcher、Start Menu、Dock（如 GNOME Favorites）  
🟦 2. .desktop 正規安裝位置    
系統級（所有使用者）   
```
/usr/share/applications/
```
單一使用者（不需 root ）  
```
~/.local/share/applications/
```  
🟦 3. 完整 .desktop 檔案範例
```
[Desktop Entry]
Type=Application
Name=Example Application
Comment=An example GTK3 application
Exec=/home/user/myapp/run.sh
Icon=/home/user/myapp/icon.png
Terminal=false
Categories=Utility;Development;
StartupNotify=true
Keywords=example;test;demo;
MimeType=text/plain;
```
🟧 4. 每個欄位逐行解釋（重點）
[Desktop Entry]
固定這樣寫，代表這是一個 desktop 設定檔。

Type=Application
其他可能值：Application, Link, Directory  

Name=Example Application
```
Name[zh_TW]=範例應用程式
Name[en_US]=Example Application
```
⭐ Exec=... 最重要欄位（啟動你的 app）
```
Exec=myapp %f
```
⭐ Icon=example.png
```
/usr/share/icons/hicolor/48x48/apps/
~/.local/share/icons/hicolor/48x48/apps/
```
🟦 5. 高級功能：App Actions（右鍵選單）