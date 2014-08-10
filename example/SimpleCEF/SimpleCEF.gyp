{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'SimpleCEF',
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
        'SimpleCEF.cpp',
      ],
      'configurations': {
        'Common_Base': {
          'msvs_configuration_attributes': {
            'OutputDirectory': '$(ProjectDir)',
          },
        },
      },
    },
  ],
}

