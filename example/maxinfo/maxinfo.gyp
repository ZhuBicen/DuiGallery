{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'maxinfo',
      'type': 'executable',
      'include_dirs':[
        '<(DEPTH)/'
      ],
      'dependencies': [
        '<(DEPTH)/DuiLib.gyp:DuiLib',
      ],
      'defines':[ 
        'UNICODE',
        '_UNICODE',	
      ],
      'sources': [
        'maxinfo.cpp',
      ],
    },
  ],
}

