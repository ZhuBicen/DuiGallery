{
  'includes': [
    'common.gypi',
  ],
  'targets': [
    {
      'target_name': 'all',
      'type':'none',
      'dependencies': [
        '<(DEPTH)/example/01_HelloWorld/01_HelloWorld.gyp:*',
        '<(DEPTH)/example/maxinfo/maxinfo.gyp:*',
		'<(DEPTH)/example/02_TitleBar/02_TitleBar.gyp:*',
		'<(DEPTH)/example/ListTextElement/ListTextElement.gyp:*',
      ],
    },
  ],
}

