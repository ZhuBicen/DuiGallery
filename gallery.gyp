{
  'includes': [
    'common.gypi',
  ],
  'targets': [
    {
      'target_name': 'all',
      'type':'none',
      'dependencies': [
        '<(DEPTH)/CEF/cefclient.gyp:*',
        '<(DEPTH)/example/01_HelloWorld/01_HelloWorld.gyp:*',
        '<(DEPTH)/example/02_TitleBar/02_TitleBar.gyp:*',
        '<(DEPTH)/example/03_ListTextElement/03_ListTextElement.gyp:*',
        '<(DEPTH)/example/04_maxinfo/04_maxinfo.gyp:*',
        '<(DEPTH)/example/05_NativeButton/05_NativeButton.gyp:*',
        '<(DEPTH)/example/06_SimpleCEF/06_SimpleCEF.gyp:*',
        '<(DEPTH)/example/07_CefDialog/07_CefDialog.gyp:*',

      ],
    },
  ],
}

