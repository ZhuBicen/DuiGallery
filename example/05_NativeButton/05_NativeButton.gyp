{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': '05_NativeButton',
      'type': 'executable',
      'include_dirs':[
        '<(DEPTH)/DuiLib'
      ],
      'dependencies': [
        '<(DEPTH)/DuiLib/DuiLib.gyp:DuiLib',
      ],
      'defines':[ 
        'UNICODE',
        '_UNICODE',	
      ],
      'sources': [
        'NativeButton.cpp',
      ],
      'copies': [
        {
            'destination': '$(OutDir)',
            'files': [
                'sysBtn/',
                '05_NativeButton.xml',
            ],
        },
      ],
    },
  ],
}

