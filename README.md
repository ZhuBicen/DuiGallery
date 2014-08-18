# Prerequisite software
2. GYP
```
svn co http://gyp.googlecode.com/svn/trunk/ gyp-read-only
set PATH=%PATH%;gyp-read-only
set GYP_GENERATORS=msvs
```

1. Vistual Studio

Only tested on VS2013

# Build Step
1. 下载cef_binary_3.2078.1780_windows32.7z，然后把Debug和Release目录中文件拷贝到，CEF目录中的Debug和Release中
1. `gyp --depth=. duilibgallery.gyp`
2. open duilibgallery.sln