# 窗口最大尺寸的控制 #
DuiLib中是提供了一个参数的，maxinfo用于控制窗口的最大尺寸，比如
   `<Window size="800,600" mininfo="600,400" maxinfo="800, 800" caption="0,0,0,32" sizebox="4,4,4,4">`
窗口的最大尺寸包括，用户点击最大化按钮时的窗口尺寸和用户拖动窗口边框时可以达到的最大尺寸，在Win32中这两部分信息分别使用LPMINMAXINFO.ptMaxSize和LPMINMAXINFO.ptMaxTrackSize表示。
