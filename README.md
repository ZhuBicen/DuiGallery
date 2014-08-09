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
1. `gyp --depth=. duilibgallery.gyp`
2. open duilibgallery.sln