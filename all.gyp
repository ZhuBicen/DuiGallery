{
  'includes': [
    'common.gypi',
  ],
  'targets': [
    {
      'target_name': 'all',
      'type':'none',
      'dependencies': [
        '<(DEPTH)/example/maxinfo/maxinfo.gyp:*',
      ],
    },
  ],
}

