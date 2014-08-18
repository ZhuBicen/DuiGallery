{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': '04_maxinfo',
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
        'maxinfo.cpp',
        '04_maxinfo.xml',
      ],
      'copies': [
        {
            'destination': '$(OutDir)',
            'files': [
                'sysBtn/',
                '04_maxinfo.xml',
            ],
        },
      ],
    },
  ],
}

