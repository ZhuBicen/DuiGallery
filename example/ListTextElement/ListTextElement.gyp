{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'ListTextElement',
      'type': 'executable',
      'include_dirs':[
        '<(DEPTH)/DuiLib/'
      ],
      'dependencies': [
        '<(DEPTH)/DuiLib/DuiLib.gyp:DuiLib',
      ],
      'defines':[ 
        'UNICODE',
        '_UNICODE',	
      ],
      'sources': [
        'Main.cpp',
        'MenuWnd.h',
      ],
      'copies': [
        {
            'destination': '$(OutDir)',
            'files': [
                'skin/',
            ],
        },
      ],
    },
  ],
}

